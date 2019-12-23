/******************************************************************************

Implementing a grep-like text search tool

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <string>
#include <filesystem>

using namespace std;
using namespace filesystem;

// helper function first.
// It accepts a file path and a regular expression object that describes the pattern we are looking for
// return a vector that contain pairs of matching line numbers and their content
vector<pair<size_t, string>>
matches(const path &p, const regex &re)
{
    vector<pair<size_t, string>> d;
    ifstream is {p.c_str()};

    // We traverse the file line by line using the getline function.
    // regex_search returns true if the string contains our pattern.
    // If this is the case, then we put the line number and the string into the vector.
    // Finally, we return all collected matches
    string s;
    for (size_t line{1}; getline(is, s); ++line) {
        if(regex_search(begin(s), end(s), re)) {
            d.emplace_back(line, move(s));
        }
    }
    return d;
}

int main(int argc, char *argv[])
{

    if(argc != 2) {
        cout << "Usage: " << argc << " <pattern>\n";
        return 1;
    }

    regex pattern;
    try {pattern = regex{argv[1]}; }
    catch (const regex_error &e) {
        cout << "Invalid regular expresssion provided.\n";
        return 1;
    }

    for(const auto &entry : recursive_directory_iterator{current_path()}) {
        auto ms (matches(entry.path(), pattern));
        for(const auto &[number, content] : ms) {
            cout << entry.path().string() << ":" << number
                 << " - " << content << '\n';
        }
    }

    return 0;
}
