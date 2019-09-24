/******************************************************************************

1. Write a template function f() that adds the elements of one vector<T> to the elements of another; for example, f(v1,v2)
should do v1[i]+=v2[i] for each element of v1.

*******************************************************************************/
#include <iostream>
#include <vector>

using namespace std;

template<typename T,typename A>
void f(vector<T>& t, const vector<A>& a)
// do vt[i]+=va[i] for each element of vt
{
    for(int i=0; i<t.size()&& i<a.size(); ++i){
        t.at(i) += a.at(i);
        //cout << t.at(i);
    }
}


int main()
{
    vector<int>t{0,1,2,3};
    vector<double>a{2,4};
    f(t,a);
    for(int i: t)
        cout << i;
    
   
    return 0;
}
