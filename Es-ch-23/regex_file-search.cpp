/******************************************************************************
23.7 Searching with regular expressions

*******************************************************************************/

#include <iostream>
#include <fstream>
#include<string>
#include <regex>

using namespace std;

// error() simply disguises throws:
[[noreturn]] inline  void error(const string& s)
{
    throw runtime_error(s);
}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

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



