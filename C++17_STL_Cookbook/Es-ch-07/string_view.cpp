/******************************************************************************

Getting the comfort of std::string without the cost of constructing std::string objects

*******************************************************************************/

#include <iostream>
#include <string_view>
#include <string>
#include <algorithm>

using namespace std;

void print(string_view v)
{
    const auto words_begin (v.find_first_not_of(" \t\n"));
    v.remove_prefix(min(words_begin, v.size()));

    const auto words_end (v.find_last_not_of(" \t\n"));
    if(words_end != string_view::npos) {
        v.remove_suffix(v.size() - words_end -1);
    }

    cout << "lenght: " << v.length()
         << " [" << v << "]\n";
}

int main(int argc, char *argv[])
{

    print(argv[0]); // runtime char* string from the argv pointer
    print({});      // empty string_view instance
    print("a const char * array"); // C-style static character string
    print("an std::string_view literal"sv);
    print("an std::string instance"s);
    print("  \t\n foobar \n \t "); // a string that has a lot of leading and trailing whitespace

    char cstr[]{'a','b','c'};   // construct a string, such as "abc", without a trailing zero
    print(string_view(cstr,sizeof (cstr)));


    return 0;
}
