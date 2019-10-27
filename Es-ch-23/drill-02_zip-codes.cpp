/******************************************************************************

Ch 23:
Drill 2. Get the little program from §23.7 to work;
        that may involve figuring out how to set the project and/or command-line options
        to link to the regex library and use the regex headers.
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

        setlocale(LC_ALL, "en_US.UTF-8");

        ifstream in {"file.txt"}; // input file
        if (!in) cerr << "no file\n";

        regex pat {R"(\w{2}\s*\d{5}(–\d{4})?)"};    // postal code pattern
        int lineno = 0;

        for (string line; getline(in,line); ) {
          ++lineno;
          smatch matches;
          if (regex_search(line, matches, pat)) {
              cout << lineno << ": " << matches[0] << '\n';       // whole match
              if (1<matches.size() && matches[1].matched)
                  cout  << "\t: " << matches[1] << '\n';            // sub-match
          }
        }
    }
    catch ( std::exception& e) {
    std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
    std::cerr << "exception\n";
    }
}
