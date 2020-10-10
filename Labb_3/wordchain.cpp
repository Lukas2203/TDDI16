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
#include <unordered_map>
#include <unordered_set>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using namespace std;

// Typ som används för ordlistan. Den definieras med en typedef här så att du enkelt kan ändra
// representationen av en ordlista utefter vad din implementation behöver. Funktionen
// "read_questions" skickar ordlistan till "find_shortest" och "find_longest" med hjälp av denna
// typen.
typedef list<string> Dictionary;


bool is_neighbor(const string &a, const string &b)
{
    int diff{};
    for(size_t i{}; i < a.size(); i++)
    {
        if(a[i] != b[i])
        {
            diff++;
        }
    }
    return diff == 1;
}


unordered_map<string, vector<string>> create_graph(const unordered_set<string>& new_dict)
{
    unordered_map<string, vector<string>> graph;
    for(string node : new_dict)
    {
        string orig_word{node};
        for(int i{}; i < 4; i++)
        {
            for (char c = 'a'; c <= 'z'; c++)
            {
                node.at(i) = c;
                cout << "new node: " << node << endl;
                if(is_neighbor(node, orig_word) && new_dict.find(node)!=new_dict.end())
                    graph[orig_word].push_back(node);
                else if(new_dict.find(node)!=new_dict.end())
                    graph[orig_word];
            }
            node = orig_word;
        }
    }
    /*for(pair<string, vector<string>> s : graph)
    {
        cout << s.first << " -> ";
        for(string b : s.second)
        {
            cout << b << " ";
        }
    cout << endl;
    }*/
    return graph;
}

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */


vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    
    vector<string> result;

    queue<string> q;
    q.push(from);
    
    unordered_map<string,string> parents;
    parents[from] = "";

    while(!q.empty())
    {
        string node = q.front();
        q.pop();
    
        for(string next : dict)
        {
            if(is_neighbor(node,next))
            {                
                if(  parents.find(next) == parents.end())
                {
                    q.push(next);
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
vector<string> find_longest(const Dictionary &dict, const string &word, /* const unordered_map<string, vector<string>>& adj_list, */ const unordered_set<string>& new_dict) {
    auto start = chrono::high_resolution_clock::now();
    cout << "find_longest started" << endl;
    vector<string> result;

    vector<string> new_visited;

    queue<string> q;
    q.push(word);
    
    unordered_map<string,string> parents;
    parents[word] = "";

    while(!q.empty())
    {        
        string node = q.front();
        q.pop();
        
        string orig_word{node};
        //for(string next : /* new_dict */ adj_list.at(node))
        for(int i{}; i < 4; i++)
        {
            for (char c = 'a'; c <= 'z'; c++)
            {
                node.at(i) = c;
                if(is_neighbor(orig_word, node) && new_dict.find(node)!=new_dict.end())
                {
                   if(parents.find(node) == parents.end())
                   {
                        q.push(node);
                        parents[node] = orig_word;
                        new_visited.push_back(node);
                        //new_dict.erase(next);
                   } 
                }
            }
            node = orig_word;
            // if(is_neighbor(node,next))
            // {
            //     if(parents.find(next) == parents.end())
            //     {
            //         q.push(next);
            //         parents[next] = node;
            //         new_visited.push_back(next);
            //         //new_dict.erase(next);
            //     }
            // }
        }
        
        for(string s : new_visited)
        {
            //new_dict.erase(s);
        }
        new_visited.clear();
        
    }

    for(string s : dict)
    {
        vector<string> test_path;
        for(string curr{s}; curr != ""; curr = parents[curr])
        {
            test_path.push_back(curr);
        }
        if(test_path.size() > result.size())
        {
            result = test_path;
        }
    }


    if(result.size() <= 1)
    {
        result.clear();
    }

    auto end = chrono::high_resolution_clock::now();
    auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "TIME: " << time << endl;
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
void read_questions(const Dictionary &dict, /* const unordered_map<string,vector<string>>& adj_list, */ const unordered_set<string>& new_dict) {
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
            vector<string> chain = find_longest(dict, line, /* adj_list, */ new_dict);

            cout << line << ": " << chain.size() << " ord" << endl;
            print_chain(chain);
        }
    }
}

int main() {
    Dictionary dict = read_dictionary();
    unordered_set<string> new_dict;
    for(string w : dict)
    {
        new_dict.insert(w);
    }
    //unordered_map<string, vector<string>> adj_list {create_graph(new_dict)};
    cout << "graph created" << endl;
    read_questions(dict, /* adj_list, */ new_dict);



    return 0;
}
