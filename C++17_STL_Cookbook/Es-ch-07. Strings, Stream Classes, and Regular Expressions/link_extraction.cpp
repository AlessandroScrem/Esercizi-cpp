/******************************************************************************

Tokenizing input with the regular expression library

    // runas: <curl -s "https://isocpp.org/blog" | exename>

*******************************************************************************/

#include <iostream>
#include <iterator>
#include <regex>
#include <algorithm>
#include <iomanip>

using namespace std;

template <typename Input_it>
void print(Input_it it, Input_it end_it)
{
    while(it != end_it) {
        const string link {*it++};
        if(it == end_it)  { break; }
        const string desc {*it++};

        cout << left << setw(28) << desc << " : " << link << '\n';
    }
}

int main()
{

    cin >> noskipws; // deactivates whitespace skipping and tokenizing
    const std::string in {istream_iterator<char>{cin}, {} };

    const regex link_re {"<a href=\"([^\"]*)\"[^<]*>([^<]*)</a>"};

    sregex_token_iterator it {begin(in), end(in), link_re, {1, 2}};
    print(it, {});

    return 0;
}
