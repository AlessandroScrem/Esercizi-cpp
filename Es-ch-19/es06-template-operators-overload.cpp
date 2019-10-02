/******************************************************************************

6. Repeat the previous exercise, but with a class Number<T> where T can be any numeric type. 
   Try adding % to Number and see what happens when you try to use % for Number<double> and Number<int>.

******************************************************************************/

#include <iostream>
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
    Number& operator=(const Number& a) {
        val = a.val; 
        return *this;
    }
    Number operator+(const Number& a) {return Number{val+a.val};}
    Number operator-(const Number& a) {return Number{val-a.val};}
    Number operator*(const Number<N>& a) {return Number{val*a.val};}
    Number operator%(const Number& a);
    template<class U> friend ostream& operator<<(ostream& out, const Number<U>& i);
    template<class U> friend istream& operator>>(istream& in,  Number<U>& i);
 
}; 

template<typename N>
Number<N> Number<N>::operator%(const Number<N>& a)
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





int main()
{
    try{
    Number<double> a{10.3};
    Number<double> b{20.2};
    Number<double> c{b%a};

    
    cout << "a : " << a << endl;
    cout << "b : " << b << endl;
    cout << "c : " << c << endl;
    }
    
    catch(runtime_error& e) {
        cerr << e.what() << endl;           //write error message
    }
    
    return 0;
}

