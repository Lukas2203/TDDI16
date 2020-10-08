#include <iostream>
#include <string>
#include <vector>
#include <queue>
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
typedef vector<string> Dictionary;


 bool is_neighbor(Word a, Word b)
 {
    int diff{};
    for(int i{}; i < a.w.size(); i++)
    {
        if(a.w[i] != b.w[i])
        {
            diff++;
        }
    }
    return diff == 1;
 }


struct Word
{
    string w;
    vector<Word> neighbors;
    Word(string s, Dictionary dict) :
        w{s}, neighbors{} {}
};

bool is_path(Word w1, Word w2)
{
    queue<Word> next_words;
    set<Word> prev;

    next_words.push(w1);
    prev.insert(w1);

    while(!next_words.empty())
    {
        Word next = next_words.front();
        next_words.pop();

        if(next == w2)
        {
            return true;
        }

        prev.insert(next);

        for(Word neighbor : next.neighbors)
        {
            if(prev.count(neighbor) == 0)
            {
                next_words.push(neighbor);
            }
        }
    }

    return false;
}

//Skapa Word av alla ord
//Lägga in allas neighbors. 

/**
 * Hitta den kortaste ordkedjan från 'first' till 'second' givet de ord som finns i
 * 'dict'. Returvärdet är den ordkedja som hittats, första elementet ska vara 'from' och sista
 * 'to'. Om ingen ordkedja hittas kan en tom vector returneras.
 */
vector<string> find_shortest(const Dictionary &dict, const string &from, const string &to) {
    vector<string> result;

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
