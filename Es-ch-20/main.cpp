#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Range_error : out_of_range {	// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};

double* get_from_jack(int& count)
// Jack puts doubles into an array                                                                       // returns the number of elements in *count
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
    count = vec.size();
    double* result = new double[count];
    double* pt = result;
    for(auto i : vec)
        *pt++ = i;
    return result;

}

vector<double>* get_from_jill();
// Jill puts doubles into a vector
{
    string fname = "double2.txt";
    vector<double> vec;
    double val = 0;

    ifstream ifs(fname.c_str());
    if(!ifs)
        std::cerr << "can't open " << fname;


}


template <typename Iter>
Iter high(const Iter b, const Iter e)
// return a Iterator to the element in [first,last) that has the highest value
{

    double h = numeric_limits<double>::min();
    Iter high = nullptr;
    for (Iter i = b; i!= e; ++i) {
        if(h<*i) { high = i; h = *i; }
    }
    return high;
}

template <typename Iter>
void out(const Iter b, const Iter e, string s)
{
    std::cout  << s << " {";
    for (Iter i = b; i!= e; ++i) {
        std::cout << *i << " ";
    }
    std::cout  << "}\n";
}


int main()
{
try {

    int jack_count{0};
    double *jack_data = get_from_jack(jack_count);
    vector<double>* jill_data = get_from_jill();

    out(jack_data, jack_data+jack_count, "jackdata");

    double* jack_high = high(jack_data,jack_data+jack_count);
    std::cout  << *jack_high <<  " is the higher value\n";

    //vector<double>& v = *jill_data;
    //double* jill_high = high(&v[0],&v[0]+v.size());

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
