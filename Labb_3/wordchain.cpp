#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using namespace std;
// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef vector<string> Dictionary;


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

int get_index(Dictionary dict, string a)
{
    return distance(dict.begin(), find(dict.begin(),dict.end(), a));
}

vector<vector<string>> build_graph(const Dictionary &dict)
{
    vector<vector<string>> graph(dict.size());
    size_t dict_size{dict.size()};
    for (int i{}; i < dict_size; i++)
    {
        for(string word : dict)
        {
            if(is_neighbor(dict[i], word))
            {
                graph[i].push_back(word);
            }
        }
    }
    return graph;
}

vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to, const vector<vector<string>> &graph) {
    vector<string> result;

    size_t dict_size{dict.size()};

    queue<string> q;
    q.push(from);
    
    vector<bool> visited(dict_size);
    visited[get_index(dict,from)] = true;

    vector<string> prev(dict_size);

    

    while(!q.empty())
    {
        
        string node = q.front();
        q.pop();
        vector<string> neighbors = graph[get_index(dict,node)];
        for(string next : neighbors)
        {
            auto start = std::chrono::high_resolution_clock::now();
            int index{get_index(dict,next)};
            // ################################################ hitta alternativ till ovan!!!!!!!
            if(!visited[index])
            {
                q.push(next);
                visited[index] = true;
                prev[index] = node;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>( end - start ).count();
            std::cout << "TIME: " << duration << endl;
        }
        
    }

    //prev
    vector<string> path(dict_size);

    for(string curr{to}; curr != ""; curr = prev[get_index(dict,curr)])
    {
        path.push_back(curr);
    }

    reverse(path.begin(), path.end());
    auto it = find(path.begin(), path.end(), "");
    path.resize(distance(path.begin(), find(path.begin(),path.end(), "")));

    if(path.size() <= 1)
    {
        path.clear();
    }
    
    result = path;
    return result;
}

/**
 * Hitta den längsta kortaste ordkedjan som slutar i 'word' i ordlistan 'dict'. Returvärdet är den
 * ordkedja som hittats. Det sista elementet ska vara 'word'.
 */
vector<string> find_longest(const Dictionary &dict, const string &word, const vector<vector<string>> &graph) {
    vector<string> result(1, word);

    int size_biggest{}, size_curr{};

    for(string start : dict)
    {
        vector<string> curr_path{find_shortest(dict,start, word, graph)};
        if(curr_path.size() > size_biggest)
        {
            result = curr_path;
            size_biggest = curr_path.size();
        }
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
    vector<vector<string>> graph = build_graph(dict);
    while (std::getline(std::cin, line)) {
        size_t space = line.find(' ');
        if (space != string::npos) {
            string first = line.substr(0, space);
            string second = line.substr(space + 1);
            vector<string> chain = find_shortest(dict, first, second, graph);

            cout << first << " " << second << ": ";
            if (chain.empty()) {
                cout << "ingen lösning" << endl;
            } else {
                cout << chain.size() << " ord" << endl;
                print_chain(chain);
            }
        } else {
            vector<string> chain = find_longest(dict, line, graph);

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
