#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Vector senza allocator...

template<typename T, class A = allocator<T>>
class vector{
    /*
     * invariant:
     * if 0<=n<sz, elem[n] is element n
     * sz<=space;
     * if sz<space there is space for (space–sz) doubles after elem[sz–1]
    */
    using size_type = unsigned long;
    A alloc;            // use allocate to handle memory for elements
    size_type sz;             //size
    size_type space;          // number of elements plus “free space”/“slots”
    T *elem;            //pointer to the elements
                        // for new elements (“the current allocation”)
public:
    using iterator = T*;      // T* is the simplest possible iterator
    //class iterator;
    vector() : sz{0}, elem{nullptr}, space{0}{}
    explicit vector(T s) : sz{s}, elem{new T[s]}, space{s}
    {
        for (int i=0;i<s;++i)elem[i]=0.0;      //initialize
    }

    vector(std::initializer_list<T>lst)       // initializer-list constructor
        :sz{static_cast<size_type>(lst.size())}          // uninitialized memory
        //,elem{new T[sz]}                      // for elements
        ,elem{alloc.allocate(sz)}
        ,space{sz}
    {
        std::copy( lst.begin(),lst.end(),elem);    // initialize (using std::copy();
    }

    ~vector() {delete [] elem;}                 //free memory

    vector(const vector&);                      // copy constructor: define copy
    vector(vector&& a);                         // move constructor

    iterator  begin()const {return (&elem[0]);}        // return first element
    iterator  end()const {return (&elem[sz]);}     // return one after last element

    vector& operator=(const vector&);           // copy assignment
    vector& operator=(vector&&);                // move assignment

    T& operator[](int n) { return elem[n]; }            // for non-const vectors
    const T& operator[](int n) const {return elem[n];}  // for const vectors

    int size()const{return sz;}                 //the current size
    int capacity() const { return space; }      //the current space

    void resize(int newsize);                   //increase size and initialize elemnts to zero
    void push_back(T d);                   //add element to vector
    void reserve(int newalloc);                 //add space for new elements

    void out();                                 //print all elements
};


// copy constructor
template<typename T, class A>
vector<T,A>::vector(const vector & arg)
// allocate elements, then initialize them by copying
   :sz{arg.sz},elem{alloc.allocate(arg.sz)},space{arg.sz}
    //:sz{arg.sz},elem{new T[arg.sz]},space{arg.sz}
{
    for (int i=0; i< arg.sz; ++i)elem[i] = arg.elem[i]; // copy elements
}


// move constructor
template<typename T, class A>
vector<T,A>::vector(vector &&a)
    :sz{a.sz}, elem{a.elem}, space{a.space}     // copy a’s elem space and sz
{    std::cout << "move constructor \n";

    a.space = a.sz = 0;                   // make a the empty vector
    a.elem = nullptr;
}

// copy assignment
template<typename T, class A>
vector<T,A> &vector<T,A>::operator=(const vector& a)
// make this vector a copy of a
{   std::cout << "copy assignement \n";
    if (this==&a) return *this; // self-assignment, no work needed

         if (a.sz<=space) {     // enough space, no need for new allocation
             for (int i = 0; i<a.sz; ++i) elem[i] = a.elem[i];   // copy elements
             sz = a.sz;
             return *this;
    }
    // no enough space, need new allocation
    T* p = new T[a.sz];       //allocate new space
    std::copy(a.elem, a.elem+a.sz, p);  //copy elements
    delete[] elem;                      //deallocate space
    elem = p;                           //set new elements
    space = sz = a.sz;                  //set new size and space
    return *this;

}


//move assignement
template<typename T, class A>
vector<T,A>& vector<T,A>::operator=(vector && a)
{
    std::cout << "move assignement \n"; std::cout << a.elem[0] <<" a.elem[0] \n";
    delete[] elem;          // deallocate old space
    elem = a.elem;          // copy a’s elem space and sz
    space = a.space;
    sz = a.sz;
    a.elem = nullptr;       // make a the empty vector
    a.space = a.sz = 0;
    return *this;           // return a self-reference
}


//print elements
template<typename T, class A>
void vector<T,A>::out()
{
    for (int i=0;i<size();++i) {
        std::cout << "vec[" <<i << "]" << elem[i] << '\n';
        if(i==size()-1) std::cout << '\n';
    }
}

//add space for new elements
template<typename T, class A>
void vector<T,A>::reserve(int newalloc)
{
    if (newalloc<=space) return;                // never decrease allocation
    T* p = new T[newalloc];           // allocate new space
    for (int i=0; i<sz; ++i) p[i] = elem[i];    // copy old elements
    delete[] elem;                              // deallocate old space
    elem = p;
    space = newalloc;
}

//increase size and initialize elemnts to zero
template<typename T, class A>
void vector<T,A>::resize(int newsize)
// make the vector have newsize elements
// initialize each new element with the default value 0.0
{
    reserve(newsize);
    for (int i=sz; i<newsize; ++i) elem[i] = 0;          // initialize new elements
    sz = newsize;
}

//add element to vector
template<typename T, class A>
void vector<T,A>::push_back(T d)
// increase vector size by one; initialize the new element with d
{
    if (space==0)
        reserve(8);         // start with space for 8 elements
    else if (sz==space)
        reserve(2*space);   // get more space
    elem[sz] = d;           // add d at end
    ++sz;                   // increase the size (sz is the number of elements)
}

template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3)
void out (Iterator first, Iterator last)          // return an iterator to the element in [first,last) that has the highest value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << *p << " ";
    std::cout << "\n";
}

//template<typename T>
vector<int> f(){
    vector<int> v{100,200,300};
    return v;
}

struct Nomi
{

    Nomi(std::string n = "")
        : nome{n}{}
    std::string nome;
    int i;
};

std::ostream& operator<<(std::ostream& out, const Nomi& n)
{
    out << n.nome;
    return out;
}
int main()
{
    vector<Nomi> v{};
    v.push_back(Nomi{"pluto"});
    v.push_back(Nomi{"minnie"});
    v.push_back(Nomi{"paperino"});


    out(v.begin(), v.end());
    std::cout << "  \n";

    vector<Nomi> v2{v};

   out(v2.begin(), v2.end());

   std::cout << "fine \n";

}


