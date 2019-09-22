#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>

class vector{
    /*
     * invariant:
     * if 0<=n<sz, elem[n] is element n
     * sz<=space;
     * if sz<space there is space for (space–sz) doubles after elem[sz–1]
    */
    int sz;             //size
    double *elem;       //pointer to the elements
    int space;          // number of elements plus “free space”/“slots”
                        // for new elements (“the current allocation”)
public:
    vector() : sz{0}, elem{nullptr}, space{0}{}
    explicit vector(int s) : sz{s}, elem{new double[s]}, space{s}
    {
        for (int i=0;i<s;++i)elem[i]=0.0;      //initialize
    }

    vector(std::initializer_list<double>lst)       // initializer-list constructor
        :sz{static_cast<int>(lst.size())}          // uninitialized memory
        ,elem{new double[sz]}                      // for elements
        ,space{sz}
    {
        std::copy( lst.begin(),lst.end(),elem);    // initialize (using std::copy();
    }

    ~vector() {delete [] elem;}                 //free memory

    vector(const vector&);                      // copy constructor: define copy
    vector(vector&& a);                         // move constructor

    vector& operator=(const vector&);           // copy assignment
    vector& operator=(vector&&);                // move assignment

    double& operator[](int n) { return elem[n]; }            // for non-const vectors
    const double& operator[](int n) const {return elem[n];}  // for const vectors

    int size()const{return sz;}                 //the current size
    int capacity() const { return space; }      //the current space

    void resize(int newsize);                   //increase size and initialize elemnts to zero
    void push_back(double d);                   //add element to vector
    void reserve(int newalloc);                 //add space for new elements

    void out();                                 //print all elements
};



#endif // VECTOR_H
