/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct X { // simple test class
    int val;
    
    void out(const string& s, int nv)
            { cerr << this << "–>" << s << ": " << val << " (" << nv << ")\n"; }
            
    X(){ out("X()",0); val=0; } // default constructor
    X(int v) { val=v; out( "X(int)",v); }
    X(const X& x){ val=x.val; out("X(X&) ",x.val); } // copy constructor
    X& operator=(const X& a) // copy assignment
        { out("X::operator=()",a.val); val=a.val; return *this; }
    ~X() { out("~X()",0); } // destructor
};

X glob(2); // a global variable
X copy(X a) { return a; }
X copy2(X a) { X aa = a; return aa; }
X& ref_to(X& a) { return a; }
X* make(int i) { X a(i); return new X(a); }
struct XX { X a; X b; };

int main()
{
    cout << "inizio \n";

    X loc {4};        // local variable
    X loc2 {loc};     // copy construction
    loc = X{5};       // copy assignment
    
    cout << "loc2 = copy(loc);\n";
    loc2 = copy(loc); // call by value and return
    
    cout << "loc2 = copy2(loc);\n";
    loc2 = copy2(loc);
    
    cout << "X loc3 {6};\n";
    X loc3 {6};
    
    X& r = ref_to(loc); // call by reference and return
    delete make(7);
    delete make(8);
    vector<X> v(4);     // default values
    XX loc4;
    X* p = new X{9};    // an X on the free store
    delete p;
    X* pp = new X[5];   // an array of Xs on the free store
    delete[] pp;

    return 0;
}

