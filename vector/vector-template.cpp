#include <iostream>
#include <stdlib.h>

// implemented:
// basic allocator class
// copy constructor, move constructor
// copy assignment, move assignment
// operator[]
// reserve resize
// push_back()
// size() capacity()
// iterator begin() end()
// erase()
// out()

template<typename T> class allocator {
    T* data;
     using size_type = unsigned long;
public:
     T* allocate(size_type n){
         data =  new T[n];   // allocate space for n objects of type T
         return data;
     }

     void deallocate(T* p, size_type) { delete [] p;}     // deallocate n objects of type T starting at p
     void construct(T* p, const T& v) { *p = v;}  // construct a T with the value v in p
     void destroy(T* p) { p = nullptr;}           // destroy the T in p
};



template<typename T, typename A = allocator<T>>
class vector{
    /*
     * invariant:
     * if 0<=n<sz, elem[n] is element n
     * sz<=space;
     * if sz<space there is space for (space–sz) typeT after elem[sz–1]
    */
    using size_type = unsigned long;
    using value_type = T;

    A alloc;            // use allocate to handle memory for elements
    size_type sz;             //size
    T* elem;            //posize_typeer to the elements
    size_type space;          // number of elements plus “free space”/“slots”
                        // for new elements (“the current allocation”)
public:
    using iterator = T*;      // T* is the simplest possible iterator
    vector() : sz{0}, elem{nullptr}, space{0}{}
    explicit vector(size_type s) : sz{s}, elem{alloc.allocate(s)}, space{s}
    {
        for (size_type i=0;i<s;++i)elem[i]=0;      //initialize
    }

    vector(std::initializer_list<T>lst)         // initializer-list constructor
        :sz{static_cast<size_type>(lst.size())}       // uninitialized memory
        ,elem{alloc.allocate(sz)}               // for elements
        ,space{sz}
    {
        std::copy( lst.begin(),lst.end(),elem);    // initialize (using std::copy();
    }

    ~vector() {alloc.deallocate(elem,space);}   //free memory

    vector(const vector&);                      // copy constructor: define copy
    vector(vector&& a);                         // move constructor

    iterator insert(iterator p, const T& val);  // insert element before p return iterator in p
    iterator erase(iterator p);                 // erase p element return next iterator

    iterator  begin()const{return &elem[0];}        // return first element
    iterator end()const{return &elem[sz];}     // return one after last element

    vector& operator=(const vector&);           // copy assignment
    vector& operator=(vector&&);                // move assignment

    T& operator[](size_type n) { return elem[n]; }            // for non-const vectors
    const T& operator[](size_type n) const {return elem[n];}  // for const vectors

    size_type size()const{return sz;}                 //the current size
    size_type capacity() const { return space; }      //the current space
    T* const back()const {return  &elem[sz-1];}       //the last element

    void resize(size_type newsize, T val=T());        //increase size and initialize elemnts to zero
    void push_back(const T& val);                     //add element to vector
    void reserve(size_type newalloc);                 //add space for new elements
};

// copy constructor
template<typename T, typename A>
vector<T,A>::vector(const vector& arg)
// allocate elements, then initialize them by copying
      :sz{arg.sz},elem{alloc.allocate(arg.sz)},space{arg.space}
{
    std::copy(arg.elem,arg.elem+sz,elem);
}

// move constructor
template<typename T, typename A>
vector<T,A>::vector(vector &&a)
    :sz{a.sz}, elem{a.elem}, space{a.space}     // copy a’s elem space and sz
{
    a.space = a.sz = 0;                   // make a the empty vector
    alloc.destroy(a.elem);
}

// copy assignment
template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a)
// make this vector a copy of a
{
    if (this==&a) return *this; // self-assignment, no work needed

    if (a.sz<=space) {     // enough space, no need for new allocation
        for (size_type i = 0; i<a.sz; ++i) alloc.construct(&elem[i], a.elem[i]);   // copy elements
        sz = a.sz;
        return *this;
    }
    // no enough space, need new allocation
    T* p = alloc.allocate(a.sz);            // allocate new space
    for (size_type i=0; i<sz; ++i) alloc.construct(&p[i], a.elem[i]);  // copy
    alloc.deallocate(elem,space);                                // deallocate old space
    elem = p;                           //set new elements
    space = sz = a.sz;                  //set new size and space
    return *this;

}

//move assignement
template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector && a)
{
    alloc.deallocate(elem,space);                                // deallocate old space
    elem = a.elem;          // copy a’s elem space and sz
    space = a.space;
    sz = a.sz;
    alloc.destroy(a.elem);  // make a the empty vector
    a.space = a.sz = 0;
    return *this;           // return a self-reference
}

// erase p: return p+1
template<typename T, typename A>
// requires Element<T>() &&  Allocator<A>()
typename vector<T,A>::iterator vector<T,A>::erase(iterator p)
{
    if(p == end()) return p;
    for (auto pos = p+1;pos != end() ;++pos)
        *(pos-1) = *pos;            // copy element “one position to the left”
    alloc.destroy(&*(end()-1));     // destroy surplus copy of last element
    --sz;
    return p;
}

// insert val before p: return p
template<typename T, typename A>
typename vector<T,A>::iterator vector<T,A>::insert(vector::iterator p, const T &val)
{
    long long index = p-begin();
    if (size()==capacity())
        reserve(size()==0?8:2*size());   // make sure we have space
    // first copy last element into uninitialized space:
    alloc.construct(elem+sz,*back());
    ++sz;
    iterator pp = begin()+index;      // the place to put val
    for (auto pos = end()-1; pos!=pp; --pos)
        *pos = *(pos-1);                // copy elements one position to the right
    *(begin()+index) = val;             // “insert” val
    return pp;

}


//add space for new elements
template<typename T, typename A>
void vector<T,A>::reserve(size_type newalloc)
{
    if (newalloc<=space) return;                // never decrease allocation
    T* p = alloc.allocate(newalloc);            // allocate new space
    for (size_type i=0; i<sz; ++i) alloc.construct(&p[i], elem[i]);  // copy
    for (size_type i=0; i<sz; ++i) alloc.destroy(&elem[i]);          // destroy
    alloc.deallocate(elem,space);                              // deallocate old space
    elem = p;
    space = newalloc;
}

//increase size and initialize elemnts to zero
template<typename T, typename A>
void vector<T,A>::resize(size_type newsize, T val)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
    reserve(newsize);
    for (size_type i=sz; i<newsize; ++i) alloc.construct(&elem[i],val);  //construct
    for (size_type i=sz; i<newsize; ++i) alloc.destroy(&elem[i]);        //destroy
    sz = newsize;
}

//add element to vector
template<typename T, typename A>
void vector<T,A>::push_back(const T& val)
// increase vector size by one; initialize the new element with d
{
    if (space==0) reserve(8);               // start with space for 8 elements
    else if (sz==space) reserve(2*space);   // get more space
    alloc.construct(&elem[sz],val);         // add d at end
    ++sz;                                   // increase the size
}

template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3)
void out(Iterator first, Iterator last)          // return an iterator to the element in [first,last) that has the highest value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << *p << " ";
    std::cout << "\n";
}


int main(/*size_type argc, char *argv[]*/)
{

    vector<int> v{10,20,30};
    v.push_back(40);

    out(v.begin(), v.end());

    auto i = v.begin();
    ++i; ++i;

    std::cout << "erase :" << *i << "\n";
    v.erase(i);

    out(v.begin(), v.end());
    std::cout << v.size() << " :elementi\n";

    i = v.begin();
    ++i; ++i;
    std::cout << "i:" << *i << " \n";
    std::cout << "insert 30 before:" << *i << " \n";
    v.insert(i, 30);

    out(v.begin(), v.end());
    std::cout << v.size() << " :elementi\n";

    vector<int> v2{0};
    i = v2.begin();
    std::cout << "v2 insert 30 before:" << *i << " \n";
    v2.insert(i, 30);
    out(v2.begin(), v2.end());



}



