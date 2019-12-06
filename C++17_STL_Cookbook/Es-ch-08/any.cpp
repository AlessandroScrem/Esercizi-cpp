/******************************************************************************

Replacing void* with std::any for more type safety

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <any>
#include <list>
#include <string>
#include <iterator>

using namespace std;

using int_list = list<int>;

void print_anyting(const std::any &a)
{
    if(!a.has_value()) {
        cout << "Nothing.\n";
    } else if(a.type() == typeid (string)) {
        cout << "It's a string: "
             << quoted(any_cast<const string&>(a)) << '\n';
    } else if (a.type() == typeid (int)) {
        cout << "It's a integer: "
             << any_cast<int>(a) << '\n';
    } else if (a.type() == typeid (int_list)) {
        const auto &l (any_cast<int_list>(a));

        cout << "It's a list: ";
        copy(begin(l), end(l), ostream_iterator<int>{cout, ", "});
        cout << '\n';
    } else {
        cout << "Can't handle this item.\n";
    }
}

int main()
{

    print_anyting({}); //empty any variable using {}
    print_anyting("abc"s);
    print_anyting(123);
    print_anyting(int_list{1, 2, 3});

    // an in-place construction, avoid unnecessary copies or moves
    print_anyting(any(in_place_type_t<int_list>{}, {1, 2, 3})); //

    return 0;
}
