#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <math.h>
#include "key.h"

using namespace std;

//Hashfunktionen
class hash_func{
public:
  size_t operator()(const Key& password) const{
    size_t hash = 0; //heltal som hashvärde
    for(int i{0}; i <= N; i++){ //Går igenom hela binära "lösenordet"
      hash += password.bit(i) * pow(2.0, i); //Gör om binära "lösenordet" till ett size_t heltal
    }
    return hash;
  }
};


int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage:" << endl;
        cout << argv[0] << " <hashed password> < rand8.txt" << endl;
        return 1;
    }

    // Hashed password.
    Key hashed{argv[1]};

    // Table.
    Key table[N];

    // Read table.
    for (int i{0}; i < N; i++) {
        string buffer;
        if (!(cin >> buffer)) {
            cerr << "Too short table!" << endl;
            return 1;
        }
        table[i] = Key{buffer.c_str()};
    }

    auto begin = chrono::high_resolution_clock::now();


    //Noll key (aaaaa = 0000000000000000000000000) för senare jämförelse:
    Key zero{};

    //Hashtabell som kommer innehåller alla möjliga least_significant
    unordered_map<Key, vector<Key>, hash_func> hash_tbl;

    Key least_significant{};
    Key most_significant{};


    //Sätter half_key till rätt värde (punkten där mitten biten är 1) t.ex. 00000100000
    //Key med endast mittersta biten (t.ex. 0001000) som översta gräns för least_significant
    //och för att öka most_significant med "1":
    Key half_key{};
    bool is_half{false};

    while(!is_half){ //lösa med typ .bit(N/2) = 1
      ++half_key;
      if(half_key.bit(N/2)){
        is_half = true;
      }
    }

    //Går över alla kombinationer med den minst signifikanta halvan
    //Drar bort least_significant från hashade lösenordet, stämmer de överens får
    //man t.ex. xxxx00000, annars blir det t.ex. xxxx01101
    while(least_significant <= half_key){
      hash_tbl[hashed-subset_sum(least_significant, table)].push_back(least_significant);
      least_significant++;
    }

// ########################### Hashtabell ###########################
// Hashvärde            krypterad least_significant            least_significant
//  size_t        Key=subset_sum(least_significant, table)    vector<Key>=least_sinificant
//


    //Kollar om något i hash-tabellen från tidigare loop stämmer överens med
    //någon most_significant, om så skrivs den ut i terminalen
    //loopar tills man har gått igenom alla kombinationer
    do{
      auto iterator = hash_tbl.find(subset_sum(most_significant, table)); // Letar efter most_significant i hashtabellen
      if(iterator != hash_tbl.end()){ //Om en key i hashtebellen stämmer överens om vår nuvarande most_significant
        for(Key fitting_least : iterator->second){ //Gå igenom alla least_significant som finns i vectorn som hittades
          std::cout << fitting_least + most_significant << '\n';
        }
      }
      most_significant = most_significant + half_key; //ökar most_significant med "1"
    }while(most_significant != zero); //Loopar igenom alla kombinationer av most_significant och slår om igen





    auto end = chrono::high_resolution_clock::now();
    cout << "Decryption took "
         << std::chrono::duration_cast<chrono::seconds>(end - begin).count()
         << " seconds." << endl;

    return 0;
}
