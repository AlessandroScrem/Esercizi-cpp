/******************************************************************************

2. Write a template function that takes a vector<T> vt and a vector<U> vu 
   as arguments and returns the sum of all vt[i]*vu[i]s.

*******************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

template<typename T,typename U>
double f(const vector<T>& t, const vector<U>& u)
//returns the sum of all vt[i]*vu[i]
{
    double res{0};
    for(int i=0; i<t.size() && i<u.size(); ++i){
        res += t.at(i) * u.at(i);
    }
    return res;
}


int main()
{
    vector<int>t{0,1,2,3};
    vector<double>a{2,4,2};
    cout << f(t,a);
 
    return 0;
}

