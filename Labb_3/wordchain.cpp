#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <utility>
#include <map>
#include <list>
#include <set>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using namespace std;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef set<string> Dictionary;


bool is_neighbor(const string &a, const string &b)
{
    int diff{};
    for(int i{}; i < a.size(); i++)
    {
        if(a[i] != b[i])
        {
            diff++;
        }
    }
    return diff == 1;
}

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */


vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    
    vector<string> result;
    size_t dict_size{dict.size()};

    queue<string> q;
    q.push(from);
    
    map<string,string> parents;

    map<string,bool> visited;
    
    visited[from] = true;

    while(!q.empty())
    {
        string node = q.front();
        q.pop();
    
        for(string next : dict)
        {
            if(is_neighbor(node,next))
            {
                if(visited[next] == false)
                {
                    q.push(next);
                    visited[next] = true;
                    parents[next] = node;
                }
            }
        }
        
        
    }

    for(string curr{to}; curr != ""; curr = parents[curr])
    {
        result.push_back(curr);
    }

    reverse(result.begin(), result.end());

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
    auto start = chrono::high_resolution_clock::now();
    vector<string> result;
    size_t dict_size{dict.size()};

    queue<string> q;
    q.push(word);
    
    map<string,string> parents;
    
    vector<string> prev(dict_size);
    map<string,bool> visited;
    for(string s : dict)
    {
        visited[s] = false;
    }

    visited[word] = true;
    while(!q.empty())
    {
        string node = q.front();
        q.pop();
    
        for(pair<string,bool> p : visited)  //nåt sätt för att inte gå igenom alla? Bara gå igenom de som inte är visited?
        {
            if(!p.second && is_neighbor(node,p.first))
            {
                string next{p.first};
                //if(visited[next] == false)
                //{
                    q.push(next);
                    visited[next] = true;
                    parents[next] = node;
                    
                //}
            }
        }
        
    }
    
    for(string s : dict)
    {
        int size_check{};
        Dictionary test_path;
        for(string curr{s}; curr != ""; curr = parents[curr])
        {
            size_check++;
            //test_path.push_back(curr);
        }
        if(size_check > result.size())
        {
            for(string curr{s}; curr != ""; curr = parents[curr])
            {
            result.push_back(curr);
            }
        }
    }


    if(result.size() <= 1)
    {
        result.clear();
    }

    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "elapsed time: " << time << endl;
    
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
