/******************************************************************************

Implementing a search input suggestion generator with tries

*******************************************************************************/

#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <list>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template <typename T>
class trie
{
    map<T, trie> tries;
    int count{1};
public:

    // insert item loop recursively in the trie
    // If any of those subtries did not exist before,
    // they are implicitly added by the [] operator of std::map
    template <typename It>
    void insert(It it, It end_it) {
        if(it == end_it) { return; }
        tries[*it].insert(next(it), end_it);
    }

    // enable the user to just provide a container of items
    // are then automatically queried for iterators
    template <typename C>
    void insert(C &container){
        insert(begin(container), end(container));
    }

    // overloads the insert interface with an initializer_list parameter
    void insert(const initializer_list<T> &il) {
        insert(begin(il), end(il));
    }

    // print, going depth-first-search through the trie
    // reached a leaf when tries.empty() is true
    // After the recursive print call, we pop off the last added payload item again
    void print(list<T> &l) const {
            if(tries.empty()) {
                copy(begin(l), end(l), ostream_iterator<T>{cout, " "});
                cout << '\n';
            }
            for(const auto &p : tries) {
                l.push_back(p.first);
                p.second.print(l);
                l.pop_back();
            }
    }

    //  parameterless print function
    void print() const {
        list<T> l;
        print(l);
    }

    //  search for subtries.
    // The idea is that if the trie contains sequences such as {a, b,c} and {a, b, d, e},
    // and we give it a sequence, {a, b}, for search,
    // it would return us the subtrie that contains the {c} and {d, e}
    // The std::optional is a nice helper because we can return an empty optional object if there is no match
    template <typename It>
    optional<reference_wrapper<const trie>>
    subtrie(It it, It end_it) const {
        if(it == end_it) { return ref(*this); }
        auto found (tries.find(*it));
        if(found == end(tries)) {return {}; }

        return found->second.subtrie(next(it), end_it);
    }

    // one-parameter version of the subtrie method, which
    // automatically takes iterators from the input container
    template <typename C>
    auto subtrie(const C &c) {
        return subtrie(begin(c), end(c));
    }
};

static void prompt(){ cout << "Next input please:\n > "; }

int main()
{
    trie<string> t;

    fstream infile {"db.txt"};
    for(string line; getline(infile, line);){
        istringstream iss{line};
        t.insert(istream_iterator<string>{iss}, {});
    }

    prompt();
    for(string line; getline(cin, line);){
        istringstream iss{line};

        if(auto st (t.subtrie(istream_iterator<string>{iss}, {})); st){
            cout << "Suggestions:\n";
            st->get().print();
        } else  {
            cout << "No suggestions found.\n";
        }
        cout << "--------------------\n";
        prompt();
    }

    return 0;
}
