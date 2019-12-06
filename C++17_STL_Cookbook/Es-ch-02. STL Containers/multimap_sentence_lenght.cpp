/******************************************************************************

Implement a writing style helper tool for finding very long sentences in text with std::multimap

We will read all user input from standard input,
we tokenize by whole sentences, and not words.
Then we will collect all sentences in an std::multimap paired
with a variable carrying their length.
Afterward, we output all sentences, sorted by their length, back to the user.

*******************************************************************************/

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// helper function for filter  spaces, new line, tabs
string filter_ws(const string &s) {
    const char *ws {" \r\n\t"};
    const auto a (s.find_first_not_of(ws));
    const auto b (s.find_last_not_of(ws));
    if (a == string::npos) {
        return {};          }
    return s.substr(a, b+1);
}

// function sentence length counting
// take a giant string containing all the text,
// return  std::multimap,
// which maps sorted sentence lengths to the sentences
multimap<size_t, string> get_sentence_stats(const string &content) {
// we use two iterators in order to point to consecutive dots within the text.
// Everything between is a text sentence.
    multimap<size_t, string> ret;

    if(content.back()!='.') {
        std::cout << "Sentence must end with '.'" << std::endl;
        return ret;
    }

    const auto end_it (end(content));
    auto it1 (begin(content));
    auto it2 (find(it1, end_it, '.'));
    // The it2 will be always one dot further than it1.
    // As long as it1 did not reach the end of the text, we are fine.
    // The second condition checks whetherÂ it2 is really at least some characters further.
    // If that was not the case, there would be no characters left to read between them.
    while (it2!= end_it && distance(it1, it2) > 0) {
         string s {filter_ws({it1, it2})}; // the pure sentence
         if (s.length() > 0) {
             const auto words (count(begin(s), end(s), ' ') + 1);  // count  how many words there are
             ret.emplace(make_pair(words, move(s)));  // save word and sentence in the multimap
         }
         it1 = next(it2, 1);    // iterator it1 on the next sentence's dot character
         it2 = find(it1, end_it, '.');
    }
    return ret;
}

int main()
{
     //cin.unsetf(ios::skipws);
     //string content {istream_iterator<char>{cin}, {}};
    //string content  {"alfa beta gamma, delta. alfa beta. uno due tre.uno due tre"};
    string content  {"uno due. tre."};

     for ( const auto & [word_count, sentence] : get_sentence_stats(content)) {
         cout << word_count << " words: " << sentence << ".\n";
      }

    return 0;
}

