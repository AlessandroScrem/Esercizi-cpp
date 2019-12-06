/******************************************************************************

Using iterator adapters to fill generic data structures

*******************************************************************************/
#include <iostream>
#include <string>
#include <iterator>
#include <sstream>
#include <deque>

using namespace std;

int main()
{


    deque<int> v;

    // just copy over all the integers from the standard input into the deque
/*
    istream_iterator<int> it_cin {cin};
    istream_iterator<int> end_cin;
    copy(it_cin, end_cin, back_inserter(v));
*/
    // change std input to istringstream
    istringstream instr{"1 2 3 4 5" };
    copy(istream_iterator<int>{instr}, {}, back_inserter(v));

    // copy items into the middle of the deque
    istringstream sstr {"123 456 789"};
    auto deque_middle (next(begin(v),  static_cast<int>(v.size()) /2 ));
    copy(istream_iterator<int>{sstr},{}, inserter(v, deque_middle));


    // insert some items at the front of the deque
    initializer_list<int> il2 {-1, -2, -3};
    copy(begin(il2), end(il2), front_inserter(v));

    // print the whole content of the deque out to the user shell
    copy(begin(v), end(v), ostream_iterator<int>{cout, ", "});
    cout << '\n';




    return 0;
}

