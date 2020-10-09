#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>

using namespace std;
using std::vector;
using std::string;
using std::cout;
using std::endl;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef set<string> Dictionary;

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(const Dictionary &dict, const string &start, const string &target) {
    vector<string> result;
    set<string> D{dict};


    // If the target string is not 
    // present in the dictionary 
    if (D.find(target) == D.end()) 
        return result; 

    // To store the current chain length 
    // and the length of the words 
    int level = 0, wordlength = start.size();

    // Push the starting word into the queue 
    queue<string> Q; 
    Q.push(start); 
    vector<string> prev(dict.size());

    // While the queue is non-empty 
    while (!Q.empty()) { 
  
        // Increment the chain length 
        ++level; 
  
        // Current size of the queue 
        int sizeofQ = Q.size(); 
  
        // Since the queue is being updated while 
        // it is being traversed so only the 
        // elements which were already present 
        // in the queue before the start of this 
        // loop will be traversed for now 
        for (int i = 0; i < sizeofQ; ++i) { 
  
            // Remove the first word from the queue 
            string word = Q.front(); 
            Q.pop(); 
  
            // For every character of the word 
            for (int pos = 0; pos < wordlength; ++pos) { 
  
                // Retain the original character 
                // at the current position 
                char orig_char = word[pos]; 
  
                // Replace the current character with 
                // every possible lowercase alphabet 
                for (char c = 'a'; c <= 'z'; ++c) { 
                    word[pos] = c; 
  
                    // If the new word is equal 
                    // to the target word 
                    if (word == target) 
                    { 
                        cout << "RETURN: " << level + 1 << endl;
                        return result; 
                    }
                    // Remove the word from the set 
                    // if it is found in it 
                    // And push the newly generated word 
                    // which will be a part of the chain 
                    if (D.find(word) != D.end()) 
                    {
                        D.erase(word);
                        Q.push(word);
                        
                    } 
                } 
  
                // Restore the original character 
                // at the current position 
                word[pos] = orig_char; 
            } 
        } 
    } 

    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    vector<string> result(1, word);
    cout << "TODO: Implement me!" << endl;
    return result;
}


/**
 * Läs in ordlistan och returnera den som en vector av orden. Funktionen läser även bort raden med
 * #-tecknet så att resterande kod inte behöver hantera det.
 */
Dictionary read_dictionary() {
    string line;
    vector<string> result;
    while (std::getline(std::cin, line)) {
        if (line == "#")
            break;

        result.push_back(line);
    }

    return Dictionary(result.begin(), result.end());
}

/**
 * Skriv ut en ordkedja på en rad.
 */
void print_chain(const vector<string> &chain) {
    if (chain.empty())
        return;

    vector<string>::const_iterator i = chain.begin();
    cout << *i;

    for (++i; i != chain.end(); ++i)
        cout << " -> " << *i;

    cout << endl;
}


/**
 * Läs in alla frågor. Anropar funktionerna "find_shortest" eller "find_longest" ovan när en fråga hittas.
 */
void read_questions(const Dictionary &dict) {
    string line;
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second);

            cout << first << " " << second << ": ";
            if (chain.empty()) {
                cout << "ingen lösning" << endl;
            } else {
                cout << chain.size() << " ord" << endl;
                print_chain(chain);
            }
        } else {
            vector<string> chain = find_longest(dict, line);

            cout << line << ": " << chain.size() << " ord" << endl;
            print_chain(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    read_questions(dict);

    return 0;
}
