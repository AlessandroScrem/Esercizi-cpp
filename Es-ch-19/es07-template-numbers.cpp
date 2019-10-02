/******************************************************************************

7. Try your solution to exercise 2 with some Numbers.

******************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// error() simply disguises throws:
inline void error(const string& s)
{
	throw runtime_error(s);
}


template<typename N>
class Number
{
    N val;    
public: 


    Number() : val{0} {}
    Number(N i) : val{i} {}
    Number(const Number& arg) : val{arg.val}{} 

    Number& operator=(const Number& a) {val = a.val; return *this;}  // copy assignment 
    Number operator+(const Number& a)const {return Number{val+a.val};}
    Number& operator+=(const Number& a) {val+=a.val; return *this;}  
    Number operator-(const Number& a)const {return Number{val-a.val};}
    Number operator*(const Number& a)const  {return Number{val*a.val};}
    Number operator%(const Number& a)const;

    template<class U> friend ostream& operator<<(ostream& out, const Number<U>& i);
    template<class U> friend istream& operator>>(istream& in,  Number<U>& i);
 
}; 

template<typename N>
Number<N> Number<N>::operator%(const Number<N>& a)const
{
    if(a.val == 0) error("divide by zero");
    return fmod(val, a.val);
}


template<class U> 
ostream& operator<<(ostream& out, const Number<U>& i)
{
    out << i.val;
    return out;
}

template<class U> 
istream& operator>>(istream &in,   Number<U>& i) 
{ 
    cout << "Enter Number "; 
    in >> i.val; 
    return in; 
} 



template<typename T, typename C>
T  f(const vector<T>& t, const vector<C>& u) 
//returns the sum of all vt[i]*vu[i]
{
    T res{0};
    for(int i=0; i<t.size() && i<u.size(); ++i){
        res += t.at(i) * u.at(i);
    }
    return res;
}


int main()
{
    Number<double> da{10.2};
    Number<double> db{20.2};
    Number<double> dc{30.0};
    
    Number<double> ia{2};
    Number<double> ib{3};
    Number<double> ic{4};


    vector<Number<double>>v1{da,db,dc};
    vector<Number<double>>v2{ia,ib,ic};
    cout << f(v1,v2) << endl;


 
    return 0;
}

