/******************************************************************************

Chapter 20: 
10. Define a version of the word-counting program where the user can
    specify the set of whitespace characters.

*******************************************************************************/
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>


using namespace std;

struct Range_error : out_of_range {	
// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};

using Line = vector<char>; // a line is a vector of characters

class Text_iterator {
// keep track of line and character position within a line
    list<Line>::iterator ln;
    Line::iterator pos;
public:
    // start the iterator at line ll’s character position pp:
    Text_iterator(list<Line>::iterator ll, Line::iterator pp)
            :ln{ll}, pos{pp} { }
    char& operator*() { return *pos; }
    Text_iterator& operator++();
    bool operator==(const Text_iterator& other) const
            { return ln==other.ln && pos==other.pos; }
    bool operator!=(const Text_iterator& other) const
            { return !(*this==other); }
};

Text_iterator& Text_iterator::operator++()
{
    ++pos;                      // proceed to next character
    if (pos==(*ln).end()) {
        ++ln;                   // proceed to next line
        pos = (*ln).begin();    // bad if ln==line.end(); so make sure it isn’t
    }
    return *this;
}

struct Document {

    list<Line> line; // a document is a list of lines
    Document() { line.push_back(Line{}); }

    Text_iterator begin()               // first character of first line
    { return Text_iterator(line.begin(), (*line.begin()).begin()); }

    Text_iterator end()                 // one beyond the last character of the last line
    {
        auto last = line.end();
        --last;          // we know that the document is not empty
        return Text_iterator(last, (*last).end());
    }
    Text_iterator insert(Text_iterator p, const char& ch);  // insert character before p return iterator in p
    Text_iterator erase(Text_iterator p);                   // erase p element return next iterator

    int find(const string& find)const; // find word in document
    int replace(const string& find, const string& replace);// find & replace word in document
    Line::iterator r_search(const Line &ln, Line::iterator it,
                           const string &w1 , string::const_iterator s_it)const;
    void w_replace(Line &ln, Line::iterator it,
                           const string &w1 , const string &w2); // replace w1 to w2

};

istream& operator>>(istream& is, Document& d)
{
    for (char ch; is.get(ch); )
    {
        d.line.back().push_back(ch);      // add the character
        if (ch=='\n')
            d.line.push_back(Line{});     // add another line
    }
    if (d.line.back().size())
        d.line.push_back(Line{});        // add final empty line
    return is;
}


void print( Document& d)
// print out the text
{
    for (auto p : d) cout << p;
}

void erase_line(Document& d, int n)
//  delete line n:
{
    if (n<0 || d.line.size()-1 <= n) return;

    auto  p = d.line.begin();
    advance(p,n);
    d.line.erase(p);
}

template<typename Iter>     // requires Forward_iterator<Iter>
void advance(Iter& p, int n)
//  moves an iterator p n elements forward
{
    while (0<n) { ++p; --n; }
}
/**/
template<typename Iter>
bool match(const Iter& p, const Iter& last, const string& s)
// compares two sequences of characters
{
    auto pos = p;
    for (auto q = s.begin(); q != s.end(); ++q) {
            if (*q != *pos || pos == last) return false;
            ++pos;
        }
        return true;
}

template<typename Iter>
Iter find(const Iter first, const Iter last,  const char& c)
//  look for a character in the sequence of characters
{
    Iter pos = first;
    while(pos != last){
        if (*pos == c) return pos; // found
    ++pos;
    }
    return pos; // not found
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
// find an occurrence of our string in the document,  return an iterator to its first character
{
    if (s.size()==0) return last;      // can’t find an empty string
    char first_char = s[0];
    while (true) {
        auto p = find(first,last,first_char);
        if (p==last || match(p,last,s)) return p;
        first = ++p;                     // look at the next character
    }
}


int Document::find(const string &w1)const
// find and replace a word in the document return true or false
{
    if (w1.size()==0)return 0; // nothing to find

    int count{0};
    for (auto ln : line) {
         if (ln.end()!= r_search(ln, ln.begin(), w1, w1.begin() )){ //search word
             ++count;
        }
    }
    return count;
}

int Document::replace(const string &w1, const string &w2)
// replace w2 with w1 in document return count of replaced words
{
    if (w1.size()==0)return 0; // nothing to find
    int count{0};

    for (Line& ln : line) {
        auto pos = r_search(ln, ln.begin(), w1, w1.begin() ); // search
        if (pos != ln.end()){   // found word?
            w_replace(ln, pos, w1,  w2); // replace w1 to w2 in Line ln at pos
            ++count;
        }
    }
    return count;
}

Line::iterator Document::r_search(const Line &ln, Line::iterator it,
                                 const string &w1 , string::const_iterator s_it)const
// recursively search w1 il line : return position iterator or end()
{

    if (it == ln.end()) return it; //not found
    if (s_it == w1.end())return it-w1.size(); // found w1
    if(*it==*s_it) ++s_it;  // if match character search next character in w1
    else s_it = w1.begin(); // search from the begin of w1
    return r_search(ln, ++it, w1, s_it);
 }

void Document::w_replace(Line &ln, Line::iterator it,
                                 const string &w1 , const string &w2)
// replace w1 to w2
{
    long long index = it-ln.begin();  // w1 position in line
    ln.erase(it, it+w1.size());       // remove old word
    it = ln.begin()+index;            // get iterator at w1 position
    ln.insert(it, w2.begin(), w2.end()); //insert new word

}

template<typename T>
void print( T& d)
// print out the text
{
    cout <<"{";
    for (auto p : d) cout << p << "\n";
    cout <<"}\n";
}

template<typename Iter>
int charcount(Iter first, Iter last)
{
    int count{0};
    for(auto i = first; i!=last; ++i)
        if(isalpha(static_cast<int>(*i))) ++count;
    return count;
}


int wcount(Document& d)
// count word as “a whitespace-separated sequence of characters”
{
    int count{0};
    bool word = false;
    for(auto c : d){
        if (!word && isalpha(c))
            word = true;    // new char
        else if(word && isspace(c)){
            word = false;   // new word
            ++count;
        }
    }
    return count;
}


int alpha_wcount(Document& d)
// count word as “a sequence of consecutive alphabetic characters"
{
    int count = 0;
     bool word = false;
     for (auto a : d) {
         if (!word && isalpha(a))
             word = true;
         else if (word && !isalpha(a)) {
             word = false;
             ++count;
         }
     }
     return count;
}

int custom_wcount(Document& d, string& pat)
// count word separated by custom char pattern
{
    int count = 0;
     bool word = false;
     for (auto a : d) {
         if (!word && isalpha(a)) //is  new char
             word = true;
         else if (word)
             for(auto p : pat)
                 if(a==p || a=='\n'){
                     word = false;
                     ++count;
                     break;
                 }
     }
     return count;
}
int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
        const string fname{"textfile.txt"};
        fstream ifs{fname};

        if(!ifs) cerr << "can't open input file " << fname <<endl;

        Document doc;
        while(ifs >> doc);
        //print(doc);

        int nword = wcount(doc);
        cerr << "Num of space separated word: " << nword <<endl;

        int naword = alpha_wcount(doc);
        cerr << "Num of alphanum separated word: " << naword <<endl;

        string p{';','"'};
        int ncword = custom_wcount(doc, p);
        cerr << "Num of custom separated word: " << ncword <<endl;



    }
    catch (Range_error& re) {
        cerr << "bad index: " << re.index << "\n";
    }
    catch (exception& e) {
        cerr << "exception: " << e.what() << endl;
    }
    catch (...) {
        cerr << "exception\n";
    }


}

