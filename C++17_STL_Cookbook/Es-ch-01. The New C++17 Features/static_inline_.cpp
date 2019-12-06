/******************************************************************************

Enabling header-only libraries with inline variables

*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

//  before C++17
// foo_lib.hpp
class foo {
public:
    static std::string& standard_string() {
        static std::string s {"some standard string"};
        return s;
    }
};

// C++17 code
/* After declaring both the symbols inline,
 * it will just accept the first occurrence of each symbol and drop all the others.
*/
// foo_lib.hpp
class process_monitor {

public:
    static const inline std::string standard_string{"some static globally available string"};
};

inline process_monitor global_process_monitor;

int main()
{



    return 0;
}
