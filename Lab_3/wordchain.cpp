#include <iostream>
#include <string>
#include <vector> 
#include <queue> //kö över noderna som ska besökas 
#include <unordered_map> //används för att spara besökta ord och kunna spåra kortaste vägen 
#include <unordered_set> //används för att representera dictionary

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::queue;
using std::unordered_map;
using std::unordered_set;


// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef unordered_set<string> Dictionary;


/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    //variabel för att spara slutliga vägen
    vector<string> result;
    
    //variabel för att spara alla ord man ska besöka
    queue<string> to_visit;
    to_visit.push(to);
    
    //variabel för att spara vilka ord man har gått igenom och spara ordets 
    //"parent" dvs vilket ord som ledde till nuvarande (andra strängen är 
    //föräldrarn till första strängen) krävs för att kunna spåra kortaste vägen 
    //efter att ha gått igenom allt
    unordered_map<string,string> parents;
    parents[to] = "";

    //Gå igenom alla ord enligt en graf tills man har hittat "from"-ordet
    //Man börjar från ordet "to" och lägger till alla barnen i kön 
    //och går igenom den en och en osv. VI går alltså igenom grafen "baklänges"
    //detta för att inte behöva vända på hela vägen på slutet efter att ha spårat
    //vägen tillbaka. 
    while(!to_visit.empty())
    {        
        string node = to_visit.front();
        to_visit.pop();
        if(node == from)
            break;

        //skapa en ny sträng baserat på nuvarande
        string ev_neighbor{node};
        //Gå igenom varje bokstav i ordet
        for(size_t pos{}; pos < node.length(); pos++)
        {
            //Gå igenom alla möjliga grannar till ordet genom att byta ut bokstaven 
            //på nuvarande position till alla möjliga bokstäver
            for (char c = 'a'; c <= 'z'; c++)
            {
                ev_neighbor.at(pos) = c;
                //Kolla om ordet finns med i ordlistan, eftersom vi använder en 
                //unordered_map är det konstant tid för find.
                if(dict.find(ev_neighbor)!=dict.end())
                {
                    //Om vi inte har besökt det ordet än 
                    if(parents.find(ev_neighbor) == parents.end())
                    {
                        //lägg till det i to_visit för att hitta dess grannar sen
                        //och i parents för att spara ordets förra ord/föräldrar
                        to_visit.push(ev_neighbor);
                        parents[ev_neighbor] = node;
                    } 
                }
            }
            //återställ ev_neighbor för att fortsätta med nästa bokstav
            ev_neighbor = node;
        }        
    }

    //Spåra kortaste pathen tillbaka genom partens
    for(string curr{from}; curr != ""; curr = parents[curr])
    {
        result.push_back(curr);
    }

    //skicka en tom vector om storleken bara är ett, då finns ingen väg.
    if(result.size() <= 1)
    {
        result.clear();
    }

    return result;
}



/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word) {
    //variabel för att spara slutliga vägen
    vector<string> result;

    //variabel för att spara alla ord man ska besöka
    queue<string> to_visit;
    to_visit.push(word);
    
    //variabel för att spara vilka ord man har gått igenom och spara ordets 
    //"parent" dvs vilket ord som ledde till nuvarande (andra strängen är 
    //föräldrarn till första strängen) krävs för att kunna spåra kortaste vägen 
    //efter att ha gått igenom allt
    unordered_map<string,string> parents;
    parents[word] = "";

    //Gå igenom alla ord enligt en graf
    //Man börjar från ordet "word" och går alltså baklänges 
    //och lägger till alla barnen i kön och går igenom de en och en osv
    while(!to_visit.empty())
    {        
        string node = to_visit.front();
        to_visit.pop();
        
        //skapa en ny sträng baserat på nuvarande
        string ev_neighbor{node};

        //Gå igenom varje bokstav i ordet
        for(int i{}; i < 4; i++)
        {
            //Gå igenom alla möjliga grannar till ordet genom att byta ut bokstaven 
            //på nuvarande position till alla möjliga bokstäver
            for (char c = 'a'; c <= 'z'; c++)
            {
                ev_neighbor.at(i) = c;
                //Kolla om ordet finns med i ordlistan, eftersom vi använder en 
                //unordered_map är det konstant tid för find.
                if(dict.find(ev_neighbor)!=dict.end())
                {
                    //Om vi inte har besökt det ordet än 
                    if(parents.find(ev_neighbor) == parents.end())
                    {
                        //lägg till det i to_visit för att hitta dess grannar sen
                        //och i parents för att spara ordets förra ord/föräldrar
                        to_visit.push(ev_neighbor);
                        parents[ev_neighbor] = node;
                    } 
                }
            }
            //återställ ev_neighbor för att fortsätta med nästa bokstav
            ev_neighbor = node;
        }        
    }

    //Kolla vad kortaste vägen är för alla ord i ordlistan och spara den längsta
    for(string s : dict)
    {
        vector<string> test_path;
        //Spåra kortaste pathen tillbaka genom partens
        for(string curr{s}; curr != ""; curr = parents[curr])
        {
            test_path.push_back(curr);
        }
        if(test_path.size() > result.size())
        {
            result = test_path;
        }
    }
    
    //skicka en tom vector om storleken bara är ett, då finns ingen väg.
    if(result.size() <= 1)
    {
        result.clear();
    }

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
    int quest_num {};
    while (std::getline(std::cin, line)) {
        quest_num++;
        cout << quest_num << endl;
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
