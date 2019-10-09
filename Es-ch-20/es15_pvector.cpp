/******************************************************************************

Chapter 20: 
15. Define a pvector to be like a vector of pointers except that it contains
    pointers to objects and its destructor deletes each object.

*******************************************************************************/
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdexcept>
//using namespace std;


template<typename T>
class pvector{

public:
    using iterator = T*;      // T* is the simplest possible iterator
    using size_type = unsigned long;
    using value_type = T;

    pvector() : sz{0}, elem{nullptr}, space{0}{}
    explicit pvector(size_type s) : sz{s}, elem{new T [s]}, space{s}
    {
        for (size_type i=0;i<s;++i)elem[i]=nullptr;      //initialize vector to nullptr
    }

    ~pvector() {
        for (size_type i=0;i<sz;++i){
            std::cout << "delete : "<< *elem[i] << " " << elem[i] << " ";
            delete  elem[i];
        }
        delete [] elem;}   //free memory

    iterator insert(iterator p, const T val);  // insert element before p return iterator in p
    iterator erase(iterator p);                 // erase p element return next iterator

    iterator  begin(){return &elem[0];}        // return first element
    iterator end(){return &elem[sz];}     // return one after last element

    size_type size()const{return sz;}                 //the current size
    size_type capacity() const { return space; }      //the current space
    T* const back()const {return  &elem[sz-1];}       //the last element

    void push_back(/*const*/ T val);                     //add element to vector
    void reserve(size_type newalloc);                 //add space for new elements

private:
    size_type sz;       //size
    T* elem;            //posize_typeer to the elements
    size_type space;    // number of elements plus “free space”/“slots”
                        // for new elements (“the current allocation”)
};




// erase p: return p+1
template<typename T>
typename pvector<T>::iterator pvector<T>::erase(iterator p)
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
typename pvector<T>::iterator pvector<T>::insert(pvector::iterator p, const T val)
{
    long long index = p-begin();
    if (size()==capacity())
        reserve(size()==0?8:2*size());   // make sure we have space
    // first copy last element into uninitialized space:
    elem[sz] = *back();
    ++sz;
    iterator pp = begin()+index;      // the place to put val
    for (auto pos = end()-1; pos!=pp; --pos)
        *pos = *(pos-1);                // copy elements one position to the right
    *(begin()+index) = val;             // “insert” val
    return pp;

}

//add element to vector
template<typename T>
void pvector<T>::push_back(T val)
// increase vector size by one; initialize the new element with d
{
    if (space==0) reserve(8);               // start with space for 8 elements
    else if (sz==space) reserve(2*space);   // get more space
    elem[sz] = val;         // add d at end
    ++sz;                   // increase the size
}


//add space for new elements
template<typename T>
void pvector<T>::reserve(size_type newalloc)
{
    if (newalloc<=space) return;                // never decrease allocation
    T* p = new T[newalloc];
    for (size_type i=0; i<sz; ++i) p[i] = elem[i];  // copy
    for (size_type i=0; i<sz; ++i) delete elem[i];          // destroy
    elem = p;
    space = newalloc;
}



template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3)
void out (Iterator first, Iterator last)          // return an iterator to the element in [first,last) that has the highest value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << **p << " ";
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
        : nome{n}{
        std::cout << "constructor of: " << nome << " " << this <<std::endl; }
    std::string nome;
    int i;
    ~Nomi(){
        std::cout << "destructor of: " << nome << " " << this <<std::endl; }
};

std::ostream& operator<<(std::ostream& out, const Nomi& n)
{
    out << n.nome;
    return out;
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
        pvector<Nomi*> v{};
        Nomi* pl = new Nomi{"pluto"};
        Nomi* pa = new Nomi{"paperino"};
        Nomi* mi = new Nomi{"minnie"};
        Nomi* zp = new Nomi{"zio paperone"};

        v.push_back(pl);
        v.push_back(pa);
        v.push_back(mi);

        auto it = v.begin();
        ++it;
        v.erase(it);

        it = v.begin();
        ++it; ++it;
        v.insert(it, zp);


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

