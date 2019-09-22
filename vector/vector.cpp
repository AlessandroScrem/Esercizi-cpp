#include "vector.h"


// copy constructor
vector::vector(const vector & arg)
// allocate elements, then initialize them by copying
    :sz{arg.sz},elem{new double[arg.sz]},space{arg.space}
{
    std::copy(arg.elem,arg.elem+sz,elem);
}

// copy assignment
vector &vector::operator=(const vector& a)
// make this vector a copy of a
{
    if (this==&a) return *this; // self-assignment, no work needed

         if (a.sz<=space) {     // enough space, no need for new allocation
             for (int i = 0; i<a.sz; ++i) elem[i] = a.elem[i];   // copy elements
             sz = a.sz;
             return *this;
    }
    // no enough space, need new allocation
    double* p = new double[a.sz];       //allocate new space
    std::copy(a.elem,a.elem+sz,p);      //copy elements
    delete[] elem;                      //deallocate space
    elem = p;                           //set new elements
    space = sz = a.sz;                  //set new size and space
    return *this;

}

// move constructor
vector::vector(vector &&a)
    :sz{a.sz}, elem{a.elem}, space{a.space}     // copy a’s elem space and sz
{
    a.space = a.sz = 0;                   // make a the empty vector
    a.elem = nullptr;
}

//move assignement
vector &vector::operator=(vector && a)
{
    delete[] elem;          // deallocate old space
    elem = a.elem;          // copy a’s elem space and sz
    space = a.space;
    sz = a.sz;
    a.elem = nullptr;       // make a the empty vector
    a.space = a.sz = 0;
    return *this;           // return a self-reference
}

//print elements
void vector::out()
{
    for (int i=0;i<size();++i) {
        std::cout << "vec[" <<i << "]" << elem[i] << '\n';
        if(i==size()-1) std::cout << '\n';
    }
}

//add space for new elements
void vector::reserve(int newalloc)
{
    if (newalloc<=space) return;                // never decrease allocation
    double* p = new double[newalloc];           // allocate new space
    for (int i=0; i<sz; ++i) p[i] = elem[i];    // copy old elements
    delete[] elem;                              // deallocate old space
    elem = p;
    space = newalloc;
}

//increase size and initialize elemnts to zero
void vector::resize(int newsize)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
    reserve(newsize);
    for (int i=sz; i<newsize; ++i) elem[i] = 0;          // initialize new elements
    sz = newsize;
}

//add element to vector
void vector::push_back(double d)
// increase vector size by one; initialize the new element with d
{
    if (space==0)
        reserve(8);         // start with space for 8 elements
    else if (sz==space)
        reserve(2*space);   // get more space
    elem[sz] = d;           // add d at end
    ++sz;                   // increase the size (sz is the number of elements)
}
