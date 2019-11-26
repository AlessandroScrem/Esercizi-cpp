/******************************************************************************

Creating, concatenating, and transforming strings

*******************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <string_view>

using namespace std;


int main()
{
    string a{  "a"  };
    auto   b{  "b"s }; //literal operator

    string_view c { "c"   };
    auto        d { "d"sv };  // literal operator

    cout << a << "," << b << '\n';
    cout << c << "," << d << '\n';

    cout << a + b << '\n';
    cout << a + string{c} << '\n';

    ostringstream o;

    o << a << " " << b << " " << c << " " << d;
    auto concatenated (o.str());
    cout << concatenated << '\n';

    transform(begin(concatenated), end(concatenated),
              begin(concatenated), ::toupper);
    cout << concatenated << '\n';

    return 0;
}
