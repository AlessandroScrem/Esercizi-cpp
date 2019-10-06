/******************************************************************************

Chapter 20: 
7. Find the lexicographical last string in an unsorted vector<string>.

*******************************************************************************/
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>


using namespace std;

struct Range_error : out_of_range {	
// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};

template<typename T>
void print( T& d)
// print out the text
{
    cout <<"{";
    for (auto p : d) cout << p << "\n";
    cout <<"}\n";
}
string last(vector<string>& vs)
// Find the lexicographical last string
{
    string last{""};
    if(vs.size() ==0)return last; // nothing to find
    for(auto s: vs){
        if(s>last)last = s;
    }
    return last;
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
    const string fname{"textfile.txt"};
    vector<string> vs;
    fstream ifs{fname};

    if(!ifs) cout << "can't open :" << fname << endl;

    for(string s; ifs >> s;)
        if(isalpha(static_cast<int>(s[0])))vs.push_back(s); // skip newlines

    //cout << vs.size() <<endl;
    //print(vs);

    cout << "Last string is: " << last(vs) << endl;


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

