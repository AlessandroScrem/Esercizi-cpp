/******************************************************************************

23.9 Matching with regular expressions
    We can now proceed to verify the data in that table.
    We keep a sum of the number of pupils in the boys (“drenge”) and girls (“piger”) columns.
    For each row, we check that last field (“ELEVER IALT”) really is the sum of the first two fields.
    The last row (“Alle klasser”) purports to be the sum of the columns above.
    To check that, we modify row to make the text field a submatch so that we can recognize “Alle klasser”:
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

        ifstream in {"table.txt"};        // input file
        if (!in) error("no input file\n");

        string line;                // input buffer
        int lineno = 0;
        regex header {R"(^[\w ]+(\t[\w ]+)*$)"};          // header line
        regex row {R"(^([\w ]+)(\t\d+)(\t\d+)(\t\d+)$)"};   // data line

        if (getline(in,line)) {                  // check header line
          smatch matches;
                if (!regex_match(line, matches, header))
                    error("no header");
        }

        // column totals:
        int boys = 0;
        int girls = 0;

        while (getline(in,line)) {         // check data line
          ++lineno;
          smatch matches;
          if (!regex_match(line, matches, row))
              error("bad line",to_string(lineno));

          if(in.eof()) cout << "at eof\n";

          // check row
/*          for (int i = 0; i<matches.size(); ++i)
               cout << "\tmatches[" << i << "]: "
                   <<  matches[i] << '\n';
*/
          int curr_boy = from_string<int>(matches[2]);
          int curr_girl= from_string<int>(matches[3]);
          int curr_sum = from_string<int>(matches[4]);
          if(curr_sum!= (curr_boy+curr_girl)) error("bad row sum", to_string(lineno));

          if(matches[1]== "Alle klasser"){  // last line
              if(curr_boy!=boys) error("bad boys total\n");
              if(curr_girl!=girls) error("bad girls total\n");
              if(!(in>>ws).eof()) error("character after total line\n");
              return 0;

          }

          // update totals
          boys += curr_boy ;
          girls += curr_girl;

        }
        error("didn't find total line");

    }
    catch ( std::exception& e) {
    std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
    std::cerr << "exception\n";
    }
}
