/******************************************************************************

Filtering duplicates from user input and printing them in alphabetical order with std::set

*******************************************************************************/

#include <iostream>
#include <set>
#include <string>
#include <iterator>
#include<sstream>

using namespace std;

int main()
{
/*    set<string> s;

    istream_iterator<string> it {cin};

    istream_iterator<string> end;
    copy(it, end, inserter(s, s.end()));

    for (const auto word : s) {
        cout << word << ", ";
    }
    cout << '\n';

    // Let's compile and run our program with the following input.
    // We get the following output for the preceding input, where all duplicates are stripped out,
    // and the words which were unique, are sorted alphabetically.
    // $ echo "a a a b c foo bar foobar foo bar bar" | ./program      a, b, bar, c, foo, foobar,
*/
    // interactive  version
    string command;
    getline(cin,command);    // read the line
    stringstream ss {command};
    set<string> words;
    for (string s; ss>>s; )
        words.insert(s);     // extract the individual words

    for (const auto word : words) {
        cout << word << ", ";
    }
    cout << '\n';

    return 0;
}

