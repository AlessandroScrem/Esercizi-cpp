/******************************************************************************

Iterating the other way around using reverse iterator adapters

*******************************************************************************/

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

int main()
{
    list<int> l{1, 2, 3, 4, 5};

    copy(l.rbegin(), l.rend(), ostream_iterator<int>{cout, ", "});
    cout << '\n';

    // If a container does not provide handy rbegin and rend functions
    // but at least provides bidirectional iterators,
    // the std::make_reverse_iterator function helps out.
    // It accepts normal iterators and converts them to reverse iterators:
    copy(make_reverse_iterator(end(l)),
         make_reverse_iterator(begin(l)),
         ostream_iterator<int>{cout, ", "});
    cout << '\n';

    return 0;
}

