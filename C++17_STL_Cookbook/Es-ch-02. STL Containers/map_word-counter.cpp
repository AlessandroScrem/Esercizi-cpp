/******************************************************************************

Implementing a word frequency counter with std::map

*******************************************************************************/

#include <string>
#include <map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <sstream>


using namespace std;

// We will use one helper function in order to crop
// possibly appended commas, dots,or colons from words.
string filter_punctuation(const string &s){
    const char *forbidden {".,:; "};
    const auto  idx_start (s.find_first_not_of(forbidden));
    const auto  idx_end   (s.find_last_not_of(forbidden));
    return s.substr(idx_start, idx_end - idx_start + 1);
}

int main()
{
    map<string, size_t> words;
    int max_word_len {0};

    string s;
    stringstream str {"alfa beta gamma ;alfa ,beta"};
    while (str >> s) {
        auto filtered (filter_punctuation(s));
        max_word_len = max<int>(max_word_len, filtered.length());
        ++words[filtered];        // increment the counter value
    }

    vector<pair<string, size_t>> word_counts;
    word_counts.reserve(words.size());
    move(begin(words), end(words), back_inserter(word_counts));
    sort(begin(word_counts), end(word_counts),
         [](const auto &a, const auto &b) { return a.second > b.second;});

    cout << "# " << setw(max_word_len) << "<WORD>" << " #<COUNT>\n";
    for (const auto & [word, count] : word_counts) {
        cout << setw(max_word_len + 2)
             << word << " #"
             << count << '\n';
    }

    return 0;
}

