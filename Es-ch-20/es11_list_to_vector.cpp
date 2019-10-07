/******************************************************************************

Chapter 20: 
11. Given a list<int> as a (by-reference) parameter, make a vector<double>
    and copy the elements of the list into it. Verify that the copy was complete and correct.
    Then print the elements sorted in order of increasing value.

*******************************************************************************/
#include <stdio.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>


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

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

    list<int> li;

    for(int i=0; i<100; ++i)
        li.push_back(rand()%100); // numbers from 0 to 99

    vector<double> vd{li.begin(), li.end()};

    list<int>::iterator il = li.begin();
    vector<double>::iterator iv = vd.begin();
/*
    //check list & vector
    for (int i=0; i<1000; ++i) {
        cout << *il << " " << *iv << endl;
        ++il; ++iv;
    }
*/

     // using default comparison (operator <):
     sort(vd.begin(), vd.end());

    print(vd);


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

