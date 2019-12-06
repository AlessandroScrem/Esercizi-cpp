/******************************************************************************

Implementing a dictionary merging tool

*******************************************************************************/

#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <deque>
#include <tuple>
#include <fstream>
#include <strstream>

using namespace std;

using dict_entry = pair<string, string>;

namespace std {
ostream& operator<<(ostream &os, const dict_entry p)
{
    return os << p.first << " " << p.second;
}

istream& operator>>(istream &is, dict_entry &p)
{
    return is >> p.first >> p.second;
}
}

template <typename IS>
deque<dict_entry> from_instream(IS &&is){
    deque<dict_entry> d {istream_iterator<dict_entry>{is}, {}};
    sort(begin(d), end(d));
    return d;
}

int main()
{
    istrstream istr{"table tisch fish fisch dog hund"};

    const auto dict1 (from_instream(ifstream{"dict.txt"}));
    const auto dict2 (from_instream(istr));

    merge(begin(dict1), end(dict1),
          begin(dict2), end(dict2),
          ostream_iterator<dict_entry>{cout, "\n"});

    return 0;
}
