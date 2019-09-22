/******************************************************************************
5. Define a class Int having a single member of class int. 
   Define constructors, assignment, and operators +, –, *, / for it. 
   Test it, and improve its design as needed (e.g., define operators << and >> for convenient I/O). 

******************************************************************************/

#include <iostream>
using namespace std;

class Int
{
    
    int val;
public: 

    Int() : val{0} {}
    Int(int i) : val{i} {}
    Int& operator=(const Int& a) {
        val = a.val; 
        return *this;
    }
    Int operator+(const Int& a) {return Int{val+a.val};}
    Int operator-(const Int& a) {return Int{val-a.val};}
    Int operator*(const Int& a) {return Int{val*a.val};}
    friend ostream& operator<<(ostream& out, const Int& i);
    friend istream& operator>>(istream& in,  Int& i);
 
};
 
ostream& operator<<(ostream& out, const Int& i)
{
    out << i.val;
    return out;
}

istream& operator>>(istream &in,   Int &i) 
{ 
    cout << "Enter integer "; 
    in >> i.val; 
    return in; 
} 




int main()
{
    Int a{10};
    Int b{20};
    
    Int c{a*b};
    
    cin >> c;
    
    cout << "a : " << a << endl;
    cout << "b : " << b << endl;
    cout << "c : " << c << endl;
 
    return 0;
}

