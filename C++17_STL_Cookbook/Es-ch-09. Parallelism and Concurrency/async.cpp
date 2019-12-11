/******************************************************************************

Pushing the execution of tasks into the background using std::async

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>
#include <strstream>

using namespace std;

static map<char, size_t> histogram(const string &s)
{
    map<char, size_t> m;

    for ( char c : s) { m[c] += 1; }

    return m;
}

static string sorted(string s)
{
    sort(begin(s), end(s));
    return  s;
}

static bool is_vowel(char c)
{
    char vowel[] {"aeiou"};
    return end(vowel) != find(begin(vowel), end(vowel), c);
}

static size_t vowels(const string &s)
{
    return count_if(begin(s), end(s), is_vowel);
}

int main()
{

//    cin.unsetf(ios::skipws);
//    string input{istream_iterator<char>{cin}, {}};
//    input.pop_back(); // remove last character if input from cin

    istrstream iss{"foo bar baz foobazinga"};
    iss.unsetf(ios::skipws);

    string input{istream_iterator<char>{iss}, {}};

    auto hist        (async(launch::async, histogram, input));
    auto sorted_str  (async(launch::async, sorted, input));
    auto vowel_count (async(launch::async, vowels, input));

    for (const auto &[c, count] : hist.get()) {
        cout << c << ": " << count << '\n';
    }

    cout << "Sorted string: "
         << quoted(sorted_str.get()) << '\n'
         << "Total vowels: "
         << vowel_count.get()        << '\n';

    return 0;
}
