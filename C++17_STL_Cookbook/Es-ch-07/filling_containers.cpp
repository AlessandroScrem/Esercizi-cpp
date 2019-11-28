/******************************************************************************

Filling containers from std::istream iterators

Not compile MSVC2017
*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>
#include <numeric>

using namespace std;

struct meme{
    string description;
    size_t year;
};

istream& operator>>(istream &is, meme &m){
    return is >> quoted(m.description) >> m.year;
}

istream& operator>>(istream &is, pair<string, meme> &p){
    return is >> quoted(p.first) >> p.second;
}

int main()
{

    map<string, meme> m;

    copy(istream_iterator<pair<string, meme>>{cin}, {}, inserter(m, end(m)));

    // find out what's the longest meme name in the map
    auto max_func ([](size_t old_max, const auto &b) {
        return max(old_max, b.first.length());
    });
    size_t width {accumulate(begin(m), end(m), 0u, max_func)};

    for ( const auto &[meme_name, meme_desc] : m) {
         const auto &[desc, year] = meme_desc;
         cout << left << setw(width) << meme_name
              << " : " << desc
              << " : " << year << '\n';
    }

    return 0;
}
