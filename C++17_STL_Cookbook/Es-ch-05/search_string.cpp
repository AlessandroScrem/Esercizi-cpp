/******************************************************************************

Locating patterns in strings with std::search and choosing the optimal implementation

*******************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <functional>
#include <iterator>

using namespace std;

template <typename Itr>
static void print(Itr it, size_t chars) {
    copy_n(it, chars, ostream_iterator<char>{cout});
    cout << '\n';
}


int main()
{

    const string long_string{"Lorem ipsum dolor sit amet, consetetur"
                             " sadipscing elitr, sed diam nonumy eirmod"};
    const string needle {"elitr"};

    // old std::search
    {
        auto match (search(begin(long_string), end(long_string),
                           begin(needle), end(needle)));
        print(match, 5);
    }

    // C++17 version of std::search
    {
        auto match (search(begin(long_string), end(long_string),
                           default_searcher(begin(needle), end(needle))));
        print(match, 5);
    }

    // Boyer-Moore search algorithm for a faster search
    {
        auto match (search(begin(long_string), end(long_string),
                           boyer_moore_searcher(begin(needle), end(needle))));
        print(match, 5);
    }

    // Boyer-Moore-Horspool search algorithm
    {
        auto match (search(begin(long_string), end(long_string),
                           boyer_moore_horspool_searcher(begin(needle), end(needle))));
        print(match, 5);
    }


    return 0;
}
