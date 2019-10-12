/******************************************************************************

Chapter 20: 
17. Define an ownership_vector that hold pointers to objects like pvector
    but provides a mechanism for the user to decide which objects are owned by the vector
    (i.e., which objects are deleted by the destructor).

    Hint: This exercise is simple if you were awake for Chapter 13.

*******************************************************************************/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdexcept>
//using namespace std;


template<typename T>
class ownership_vector{

public:
    using iterator = T**;      // T* is the simplest possible iterator
    using size_type = unsigned long;
    using value_type = T;

    ownership_vector() : sz{0}, elem{nullptr}, space{0}{}
    explicit ownership_vector(size_type s) : sz{s}, elem{new T [s]}, space{s}
    {
        for (size_type i=0;i<s;++i)elem[i]=nullptr;      //initialize vector to nullptr
    }

    ~ownership_vector() {
        for (size_type i=0;i<sz;++i){
            std::cout << "delete : "<< *elem[i] << " " << elem[i] << " ";
            //delete  ;
            (*elem[i]).~T();
        }
        delete [] elem;}   //free memory

    iterator insert(iterator p,  T* val);  // insert element before p return iterator in p
    iterator erase(iterator p);                 // erase p element return next iterator

    iterator  begin(){return &elem[0];}        // return first element
    iterator end(){return &elem[sz];}     // return one after last element

    T&  operator[](size_type n)  { return *elem[n]; }            // return the object reference

    size_type size()const{return sz;}                 //the current size
    size_type capacity() const { return space; }      //the current space
    T* const back()const {return  elem[sz-1];}       //the last element

    void push_back( T* val);                     //add element owned by vector
    void push_back( T& val);                     //add element not owned by vector

    void reserve(size_type newalloc);                 //add space for new elements

private:
    size_type sz;       //size
    T** elem;            //posize_typeer to the elements
    size_type space;    // number of elements plus “free space”/“slots”
                        // for new elements (“the current allocation”)
};




// erase p: return p+1
template<typename T>
typename ownership_vector<T>::iterator ownership_vector<T>::erase(iterator p)
{
    if(p == end()) return p;
    std::cout << "erase : " << **p << " " << p << " ";
    delete *p;
    for (auto pos = p+1; pos != end() ; ++pos)
        *(pos-1) = *pos;      // copy element “one position to the left”
    (*(end()-1)) = nullptr;     // destroy surplus copy of last element
    --sz;
    return p;
}

// insert val before p: return p
template<typename T>
typename ownership_vector<T>::iterator ownership_vector<T>::insert(ownership_vector::iterator p,  T* val)
{
    long long index = p-begin();
    if (size()==capacity())
        reserve(size()==0?8:2*size());   // make sure we have space
    // first copy last element into uninitialized space:
    elem[sz] = back();
    ++sz;
    iterator pp = begin()+index;      // the place to put val
    for (auto pos = end()-1; pos!=pp; --pos)
        *pos = *(pos-1);                // copy elements one position to the right
    *(begin()+index) = val;             // “insert” val
    return pp;

}

//add element to vector
template<typename T>
void ownership_vector<T>::push_back(T* val)
// increase vector size by one; initialize the new element with d
{
    if (space==0) reserve(8);               // start with space for 8 elements
    else if (sz==space) reserve(2*space);   // get more space
    elem[sz] = val;         // add d at end
    ++sz;                   // increase the size
}

//add element to vector
template<typename T>
void ownership_vector<T>::push_back(T& val)
// increase vector size by one; initialize the new element with d
{
    if (space==0) reserve(8);               // start with space for 8 elements
    else if (sz==space) reserve(2*space);   // get more space
    elem[sz] = &val;         // add d at end
    ++sz;                   // increase the size
}


//add space for new elements
template<typename T>
void ownership_vector<T>::reserve(size_type newalloc)
{
    if (newalloc<=space) return;                // never decrease allocation
    T** p = new T*[newalloc];
    for (size_type i=0; i<sz; ++i) p[i] = elem[i];  // copy
    for (size_type i=0; i<sz; ++i) delete elem[i];          // destroy
    elem = p;
    space = newalloc;
}



template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3)
void out (Iterator first, Iterator last)          // return an iterator to the element in [first,last) that has the highest value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << **p << "--";
    std::cout << "\n";
}

template<typename C>
void debug (C& c)
{
    using size_type = unsigned long;
    std::cout << c.size()      <<" size\n";
    std::cout << c.capacity()  <<" capacity\n";
     for (size_type i = 0 ; i < c.size(); ++i)
        std::cout << c[i] << " ";
    std::cout << "\n";
}

struct Nomi
{
    Nomi(std::string n = "null")
        : nome{n}{ std::cout << "constructor of: " << nome << " " << this <<std::endl; }
    std::string nome;
    int i;
    ~Nomi(){ std::cout << "destructor of: " << nome << " " << this <<std::endl; }
};

std::ostream& operator<<(std::ostream& out, const Nomi& n)
{
    out  << n.nome;
    return out;
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
        ownership_vector<Nomi> v{};
        Nomi* pl = new Nomi{"pluto"};
        Nomi* pa = new Nomi{"paperino"};
        Nomi* mi = new Nomi{"minnie"};
        Nomi* zp = new Nomi{"zio paperone"};
        Nomi g{"gamba"};

        v.push_back(pl);
        v.push_back(pa);
        v.push_back(mi);
        v.push_back(g);

        auto it = v.begin();
        ++it;
        v.erase(it);

        it = v.begin();
        ++it; ++it;
        v.insert(it, zp);


        std::cout << "v[1]: " << v[0].nome << "\n\n";

        std::cout << "pvector : " ;
        out(v.begin(),v.end());
        std::cout << "pvector size: " << v.size() << "\n\n";



    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }
/**/

}

