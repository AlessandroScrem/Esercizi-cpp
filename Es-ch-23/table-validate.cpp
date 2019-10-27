/******************************************************************************

23.9 Matching with regular expressions
Now all we have to do is to use those patterns. First we will just validate the table layout:

*******************************************************************************/

#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include<sstream>

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

int main() {
    try{

        ifstream in {"table.txt"};        // input file
        if (!in) error("no input file\n");

        string line;                // input buffer
        int lineno = 0;
        regex header {R"(^[\w ]+(\t[\w ]+)*$)"};          // header line
        regex row {R"(^[\w ]+(\t\d+)(\t\d+)(\t\d+)$)"};   // data line

        if (getline(in,line)) {                  // check header line
          smatch matches;
                if (!regex_match(line, matches, header))
                    error("no header");
                else
                    cout <<  matches[0] << '\n';
        }
        while (getline(in,line)) {         // check data line
          ++lineno;
          smatch matches;
          if (!regex_match(line, matches, row))
              error("bad line",to_string(lineno));
          else
              cout <<  matches[0] << '\n';
        }

    }
    catch ( std::exception& e) {
    std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
    std::cerr << "exception\n";
    }
}
