/******************************************************************************

10. Implement a simple unique_ptr supporting only a constructor, destructor, –>, *, and release(). 
    In particular, don’t try to implement an assignment or a copy constructor. 

******************************************************************************/

#include <iostream>
#include <stdlib.h>

template<typename T> 
class allocator 
{ 
public:          
    
    T* allocate(int n){ return (T*) malloc(n *sizeof(T));}   // allocate space for n objects of type T
    
    void deallocate(T* p, int n) { free(p); p = nullptr;}     // deallocate n objects of type T starting at p
    void construct(T* p, const T& v) { *p = v;}      // construct a T with the value v in p          
    void destroy(T* p) { p = nullptr;}               // destroy the T in p 
}; 

template<typename T, typename A = allocator<T>>
class vector{
    /*
     * invariant:
     * if 0<=n<sz, elem[n] is element n
     * sz<=space;
     * if sz<space there is space for (space–sz) typeT after elem[sz–1]
    */
    A alloc;            // use allocate to handle memory for elements
    int sz;             //size
    T* elem;            //pointer to the elements
    int space;          // number of elements plus “free space”/“slots”
                        // for new elements (“the current allocation”)
public:
    vector() : sz{0}, elem{nullptr}, space{0}{}
    explicit vector(int s) : sz{s}, elem{alloc.allocate(s)}, space{s}
    {
        for (int i=0;i<s;++i)elem[i]=0.0;      //initialize
    }

    vector(std::initializer_list<T>lst)       // initializer-list constructor
        :sz{static_cast<int>(lst.size())}          // uninitialized memory
        ,elem{alloc.allocate(sz)}                  // for elements
        ,space{sz}
    {
        std::copy( lst.begin(),lst.end(),elem);    // initialize (using std::copy();
    }

    ~vector() {alloc.deallocate(elem,space); std::cout << "vector destructor\n";}   //free memory

    vector(const vector&);                      // copy constructor: define copy
    vector(vector&& a);                         // move constructor

    vector& operator=(const vector&);           // copy assignment
    vector& operator=(vector&&);                // move assignment

    T& operator[](int n) { return elem[n]; }            // for non-const vectors
    const T& operator[](int n) const {return elem[n];}  // for const vectors

    int size()const{return sz;}                 //the current size
    int capacity() const { return space; }      //the current space

    void resize(int newsize, T val=T());       //increase size and initialize elemnts to zero
    void push_back(const T& val);                 //add element to vector
    void reserve(int newalloc);                 //add space for new elements

    void out();                                 //print all elements
};



// copy constructor
template<typename T, typename A>
vector<T,A>::vector(const vector& arg)
// allocate elements, then initialize them by copying
    :sz{arg.sz},elem{new T[arg.sz]},space{arg.space}
{
    std::copy(arg.elem,arg.elem+sz,elem);
}

// move constructor
template<typename T, typename A>
vector<T,A>::vector(vector &&a)
    :sz{a.sz}, elem{a.elem}, space{a.space}     // copy a’s elem space and sz
{
    a.space = a.sz = 0;                   // make a the empty vector
    a.elem = nullptr;
}

// copy assignment
template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(const vector& a)
// make this vector a copy of a
{
    if (this==&a) return *this; // self-assignment, no work needed

         if (a.sz<=space) {     // enough space, no need for new allocation
             for (int i = 0; i<a.sz; ++i) alloc.construct(elem[i], a.elem[i]);   // copy elements
             sz = a.sz;
             return *this;
    }
    // no enough space, need new allocation
    T* p = alloc.allocate(a.sz);       //allocate new space
    for (int i = 0; i<a.sz; ++i) alloc.construct(p, a.elem[i]);   // copy elements
    alloc.deallocate(elem,space);        //deallocate space
    elem = p;                           //set new elements
    space = sz = a.sz;                  //set new size and space
    return *this;

}

//move assignement
template<typename T, typename A>
vector<T,A>& vector<T,A>::operator=(vector && a)
{
    alloc.deallocate(elem, space);          // deallocate old space
    elem = a.elem;          // copy a’s elem space and sz
    space = a.space;
    sz = a.sz;
    alloc.destroy(a.elem);   // make a the empty vector
    a.space = a.sz = 0;
    return *this;           // return a self-reference
}

//print elements
template<typename T, typename A>
void vector<T,A>::out()
{
    std::cout << "elem address :" << elem << std::endl;
    for (int i=0;i<size();++i) {
        std::cout << "vec[" <<i << "]" << elem[i] << '\n';
        if(i==size()-1) std::cout << '\n';
    }

}


//add space for new elements
template<typename T, typename A>
void vector<T,A>::reserve(int newalloc)
{
    if (newalloc<=space) return;                // never decrease allocation
    T* p = alloc.allocate(newalloc);            // allocate new space
    for (int i=0; i<sz; ++i) alloc.construct(&p[i], elem[i]);  // copy
    for (int i=0; i<sz; ++i) alloc.destroy(&elem[i]);          // destroy
    alloc.deallocate(elem,space);                              // deallocate old space
    elem = p;
    space = newalloc;
}

//increase size and initialize elemnts to zero
template<typename T, typename A>
void vector<T,A>::resize(int newsize, T val)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
    reserve(newsize);
    for (int i=sz; i<newsize; ++i) alloc.construct(&elem[i],val);  //construct
    for (int i=sz; i<newsize; ++i) alloc.destroy(&elem[i]);        //destroy
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

template<typename T>
class unique_ptr
{
    T* ptr;
public:
     unique_ptr():ptr{nullptr}{}
     unique_ptr(T* p): ptr{p}{}
    ~unique_ptr(){if (ptr)delete ptr; std:: cout << "free unique\n";}
	T* operator->()const { return ptr; }
	T* release(){			// Releases ownership of its stored pointer
		T* p = ptr;			
		ptr = nullptr;		//set prt to nullptr
		return p;
	}
	T& const operator*() const { return *ptr; }	// Returns a reference to the managed object
};


int main()
{

   vector<int> v{1,2,3};
   v.push_back(4);
   vector<int> v1 = v;
   v.out();
   v1.out();
   int * pi{ nullptr };			// create a rawpointer
 
   {
	unique_ptr<vector<int>> pv{ new vector<int>{20,20,30} };
	pv->resize(5);
	std::cout << "vector newsize: " << pv->size() << std::endl;
	pv->out();

	unique_ptr<int> spi{ new int{10} };
	std::cout << "dereference ptr: " << *spi*2 << "\n";

	pi = spi.release();		// move pointer to rawpointer
	std::cout << "dereference raw ptr: " << *pi << "\n";

   }

   delete pi;				// free memory

   char c;
   std::cin >> c;


}



