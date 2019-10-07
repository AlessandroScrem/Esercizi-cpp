/******************************************************************************

Chapter 20: 
Ex 4. Find and fix the errors in the Jack-and-Jill example from §20.3.1 
      by using STL techniques throughout.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <list>
#include <string>
#include <memory>
using namespace std;

struct Range_error : out_of_range {	
// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};

double* get_from_jack(int* count)
// Jack puts doubles into an array                                                                       
// returns the number of elements in *count
{
    string fname = "double1.txt";
    vector<double> vec;
    double val = 0;

    ifstream ifs(fname.c_str());
    if(!ifs)
        std::cerr << "can't open " << fname;

    while (ifs >> val){
        vec.push_back(val);
     }
    *count = vec.size();
    double* result = new double[*count];
    double* pt = result;
    for(auto i : vec)
        *pt++ = i;
    return result;

}

vector<double>* get_from_jill()
// Jill puts doubles into a vector
{
    string fname = "double2.txt";
    vector<double>*  vec = new vector<double>;
    double val = 0;

    ifstream ifs(fname.c_str());
    if(!ifs)
        std::cerr << "can't open " << fname;
    while (ifs >> val){
        vec->push_back(val);
     }
    return vec;
}


/**/

template <typename Iter>
Iter high(const Iter first, const Iter last)
// return a Iterator to the element in [first,last) that has the highest value
{

    if (first==last) cerr << "No highest value in empty sequence\n";
    Iter high = first;
    for (Iter p = first; p!=last; ++p)
        if (*high<*p) high = p;
    return high;

}

template <typename Iter>
void out(const Iter b, const Iter e, string s)
// print out the iterator's value from begin to end-1
{
    std::cout  << s << " {";
    for (Iter i = b; i!= e; ++i) {
        std::cout << *i << " ";
    }
    std::cout  << "}\n";
}



void fct()
{
    int jack_count = 0;
    double* jack_data = get_from_jack(&jack_count);
    vector<double>* jill_data = get_from_jill();
    
    double* jack_high = high(jack_data,jack_data+jack_count);
    vector<double>& v = *jill_data;


    double* jill_high = high(&v[0],&v[0]+v.size());
    cout << "Jill's high " << *jill_high << "; Jack's high " << *jack_high;
    // . . .
    delete[] jack_data;
    delete jill_data;
}


int main()
{
try {
    
    fct();

   
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
