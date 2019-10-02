/******************************************************************************

4. Modify class Link from §17.9.3 to be a template with the type of value as the template argument. 
   Then redo exercise 13 from Chapter 17 with Link<God>. 

******************************************************************************/

#include <iostream>
using namespace std;

template <typename T>
class Link { 
    T value;          
    Link* prev;          
    Link* succ;          

public:
    Link(const T& v, Link* p = nullptr, Link* s = nullptr)                    
        : value{v}, prev{p}, succ{s} { } 
    Link* insert(Link* n);        // insert n before this object 
    Link* add(Link* n);           // insert n after this 
    Link* find(const T& s);  // find s in const list
    
    void setvalue( const T& t){value = t;}      
    const T& getValue(){return value;}               
    
    Link* next() const {return succ;}
    Link* previous() const {return prev;}
    void print_all();
    
};

template <typename T>
Link<T>*  Link<T>::find(const T& s)
 // find s in list; 
 // return nullptr for “not found” 
{
    Link *p = this;
    if(s== value) return this;
    while (p) {
        if(s == p->getValue()) return p;
        p = p->next();
    }
    return nullptr;
       
}

template <typename T>
Link<T>* Link<T>::insert(Link* n)     
// insert n before this object; return n 
{   
        if (n==nullptr) return this;          
        if (this==nullptr) return n;          
        n->succ = this;              // this object comes after n
        if (prev) prev->succ = n;          
        n->prev = prev;             // this object’s predecessor becomes n’s predecessor 
        prev = n;                  // n becomes this object’s predecessor          
        return n;     
}

template <typename T>
Link<T>* Link<T>::add(Link* n)
// insert n after this
{
        if (n==nullptr) return this;          
        if (this==nullptr) return n;
        n->prev = this;     // this object comes befor n
        if(succ) succ->prev = n;
        n->succ = succ;     // this object’s sucecessor becomes n’s successor
        succ = n;           // n becomes this object’s successor
        return n;
}

template <typename T>
void Link<T>::print_all() 
{         
    Link*p = this;
    cout << "{ ";          
    while (p) {                    
        cout << p->value;                    
        if (p=p->next()) cout << ", ";          
        
    }
    cout << " }"; 
    
}

int main()
{
    
    Link<string>* norse_gods = new Link<string>{"Thor"};
    norse_gods->add(new Link<string>{"Loky"});
    norse_gods->add(new Link<string>{"Odin"});
    norse_gods->add(new Link<string>{"Zeus"});
    norse_gods->add(new Link<string>{"Freia"});
 
//    Link* p = norse_gods->find("Zeus");
//    if (p) p->setvalue("Ares");

    
    norse_gods->print_all();
    cout << "\n";


    return 0;
}

