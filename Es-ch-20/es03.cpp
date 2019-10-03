/******************************************************************************

Chapter 20: 
Ex 3. Look at the palindrome examples (§18.7); redo the Jack-and-Jill example from §20.1.2 
      using that variety of techniques

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <list>
#include <string>
using namespace std;

struct Range_error : out_of_range {	
// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};

double* get_from_jack(int& count)
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
    count = vec.size();
    double* result = new double[count];
    double* pt = result;
    for(auto i : vec)
        *pt++ = i;
    return result;

}

vector<double> get_from_jill()
// Jill puts doubles into a vector
{
    string fname = "double2.txt";
    vector<double> vec;
    double val = 0;

    ifstream ifs(fname.c_str());
    if(!ifs)
        std::cerr << "can't open " << fname;
    while (ifs >> val){
        vec.push_back(val);
     }
    return vec;
}

// get the max uging array
double* arr_high(double a[], int count)
// return a ptr to the max value
{
    double h = numeric_limits<double>::min();
    double* high = nullptr;
    for(int i=0; i<count; ++i)
        if(a[i]>h) { h=a[i] ; high = &a[i];}
    return high;
}

// get the max uging pointers
double* ptr_high(double* p, int count)
// return a ptr to the max value
{
    double h = numeric_limits<double>::min();
    double* high = nullptr;
    for(int i=0; i<count; ++i){
        if((*p)>h) { h=(*p) ; high = p;}
    ++p;
    }

    return high;
}

/**/

template <typename Iter>
Iter high(const Iter b, const Iter e)
// return a Iterator to the element in [first,last) that has the highest value
{

    double h = numeric_limits<double>::min();
    Iter high = b;
    for (Iter i = b; i!= e; ++i) {
        if(h<*i) { high = i; h = *i; }
    }
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

vector<double> prt2vec(double* p, double count)
{
    vector<double> result{};
    for (int i=0; i<count; ++i)
        result.push_back(*p++);
    return result;   
}

int main()
{
try {

    int jack_count{0};

    double *jack_data_array = get_from_jack(jack_count);
    vector<double> jill_data = get_from_jill();
   
    // find high
    // using vectors
    
    // put jack_data to vector
    vector<double> jack_data{prt2vec(jack_data_array, jack_count)};
    // get the high
    vector<double>::iterator jack_high = high(jack_data.begin(), jack_data.end());
    vector<double>::iterator jill_high = high(jill_data.begin(), jill_data.end());
    
    std::cout  << "Using vector\n";
    std::cout  << *jack_high <<  " is the jack's higher value\n";
    std::cout  << *jill_high <<  " is the jill's  higher value\n";

    // find high
    // using array
    
    // we already have the jack data as array
    // put jill data to array
    double jill_data_array[jill_data.size()];
    for( int i = 0; i< jill_data.size(); ++i)
        jill_data_array[i] = jill_data[i];
    
    std::cout  << "Using array\n";
    std::cout  << *arr_high(jack_data_array, jack_data.size()) <<  " is the jack's higher value\n";
    std::cout  << *arr_high(jill_data_array, jill_data.size()) <<  " is the jill's higher value\n";
    
    // find high
    // using pointers
    int jill_count = jill_data.size();
    std::cout  << "Using Pointers\n";
    std::cout  << *ptr_high(jack_data_array, jack_count) <<  " is the jack's higher value\n";
    std::cout  << *ptr_high(jill_data_array, jill_count) <<  " is the jill's higher value\n";
        
        
    delete [] jack_data_array;

   
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