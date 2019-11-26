/******************************************************************************

Generating permutations of input sequences

*******************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <strstream>

using namespace std;

int main()
{
    istrstream istr{"a b c"};

    vector<string> v { istream_iterator<string>{istr}, {}};
    sort(begin(v), end(v));

    do {
        copy(begin(v), end(v), ostream_iterator<string>{cout, ", "});
        cout << '\n';
    } while (next_permutation(begin(v), end(v)));

    return 0;
}
