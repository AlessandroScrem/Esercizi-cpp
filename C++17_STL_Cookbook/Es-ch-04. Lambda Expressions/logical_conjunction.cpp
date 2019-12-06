/******************************************************************************

Creating complex predicates with logical conjunction

*******************************************************************************/

#include <iostream>
#include <functional>
#include <string>
#include <iterator>
#include <algorithm>
#include <strstream>

static bool begin_with_a (const std::string &s){
    return s.find("a") == 0;
}

static bool end_with_b (const std::string &s){
    return s.rfind("b") == s.length() -1;
}

template <typename A, typename B, typename F>
auto combine(F binary_func, A a, B b){
    return [=] (auto param) {
        return binary_func(a(param), b(param));
    };
}

using namespace std;

int main()
{
    auto a_xxx_b (combine(logical_and<>{}, begin_with_a, end_with_b));

    istrstream iss{"ac cb ab axxxb"};
    copy_if(istream_iterator<string>{iss}, {},
            ostream_iterator<string>{cout, ", "},
            a_xxx_b);
    cout << '\n';

    return 0;
}

