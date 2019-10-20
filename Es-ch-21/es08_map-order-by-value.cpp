/******************************************************************************

Chapter 21:
8. Take the word-frequency example from §21.6.1 and modify it to output its lines
    in order of frequency (rather than in lexicographical order).
    An example line would be 3: C++ rather than C++: 3.

*******************************************************************************/

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;



ostream& operator<<(ostream& out, pair<string,int>& p){
    out << p.first << ": " << p.second << '\n';
    return out;
}

template<typename Iter>
void out(Iter first, Iter last){
    while (first!=last){
        cout << *first;
        ++first;
    }
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
        const string fname{"text2.txt"};
        fstream ifs{fname};

        if(!ifs) cerr << "Can't open " << fname << endl;

        map<string,int> words;         // keep (word,frequency) pairs
        for (string s; ifs>>s; )
            ++words[s];                   // note: words is subscripted by a string

//        for (const auto& p : words)
//            cout << p.first << ": " << p.second << '\n';


        vector<pair<string,int>>vp(words.size());
        copy(words.begin(),words.end(),vp.begin());
        sort(vp.begin(),vp.end(),[](pair<string,int>p1, pair<string,int>p2){return p1.second<p2.second;});

        out(vp.begin(),vp.end());





    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



