/******************************************************************************

Chapter 20: 
5. Define an input and an output operator (>> and <<) for vector.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Range_error : out_of_range {	
// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};



template <typename T>
ostream& operator<<(ostream& out, const vector<T>& t)
{
    out << "{" ;
    for(auto i : t)
        out << i <<" ";
    out << "}\n";
    return out;
}

template <typename T>
istream& operator>>(istream& in, vector<T>& t)
{

    cout << "Enter " << typeid(T).name() << " :";
    T val;
    while(in >> val)
        t.push_back(val);
    return in;

}


int main()
{
try {

        vector<int> vi = {10,20,30,40,50};
        vector<string> vs = {"pippo","pluto","paperino", "minnie"};
        cout << vi << vs;

        cin >> vi;
        cout << vi;

   
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
