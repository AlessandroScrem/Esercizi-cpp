/******************************************************************************

Chapter 20: 
6. Write a find-and-replace operation for Documents based on §20.6.2.

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

using Line = vector<char>;
// a line is a vector of characters

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
{
    for (auto p : d) cout << p;
}


int main()
{
try {

    Document doc;

    const string fname{"textfile.txt"};
    fstream ifs{fname};

    if(!ifs)
        cerr << "can't open input file " << fname <<endl;

    while(ifs >> doc);
    print(doc);






   
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
