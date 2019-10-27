/******************************************************************************

Ch 23:
Drill 1. Find out if regex is shipped as part of your standard library.
        Hint: Try std::regex and tr1::regex.

*******************************************************************************/

#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//#define NDEBUG
#include <cassert>

using namespace std;

// error() simply disguises throws:
[[noreturn]] inline void error(const string& s)
{
    throw runtime_error(s);
}

[[noreturn]] inline void error(const string& s, const string& s2)
{
    error(s+s2);
}
struct bad_from_string : std::bad_cast {      // class for reporting string cast errors
    const char* what() const override
    {
        return "bad cast from string";
    }
};

template<typename T>
T from_string(const string& s)
{
    istringstream is {s};
    T t;
    if (!(is >> t)) throw bad_from_string{};
    return t;
}
template<typename T>
string to_string(const T& t)
{
    ostringstream os;
    os << t;
    return os.str();
}

int main() {
    try{

    string str = "Hello world";
    regex rx("ello");
    assert( regex_search(str.begin(), str.end(), rx) );

    }
    catch ( std::exception& e) {
    std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
    std::cerr << "exception\n";
    }
}
