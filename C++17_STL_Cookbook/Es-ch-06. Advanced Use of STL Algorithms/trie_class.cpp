/******************************************************************************

Implementing a trie class using STL algorithms

*******************************************************************************/

#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <strstream>

using namespace std;

template <typename T>
class trie
{
    map<T, trie> tries;
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
    void print(vector<T> &v) const {
            if(tries.empty()) {
                copy(begin(v), end(v), ostream_iterator<T>{cout, " "});
                cout << '\n';
            }
            for(const auto &p : tries) {
                v.push_back(p.first);
                p.second.print(v);
                v.pop_back();
            }
    }

    //  parameterless print function
    void print() const {
        vector<T> v;
        print(v);
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

int main()
{
    trie<string> t;

    t.insert({"hi", "how", "are", "you"});
    t.insert({"hi", "i", "am", "great", "thanks"});
    t.insert({"what", "are", "you", "doing"});
    t.insert({"i", "am", "watching", "a", "movie"});

    cout << "recorded sentences:\n";
    t.print();

    cout << "\npossible suggestions after \"hi\":\n";

    if (auto st (t.subtrie(initializer_list<string>{"hi"})); st )
        { st->get().print(); }

    return 0;
}
