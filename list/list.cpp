/******************************************************************************

Chapter 20: Linked List Iterator

*******************************************************************************/
#include <stdio.h>
#include <iostream>

template<typename Elem> 
struct Link {
    Link() {prev = succ = this;}   // on empty Link prev e succ point to this
    Link(const Elem& v ,  Link* p ,   Link* s ) : val{v}, prev{p}, succ{s}{}

    Link* prev;               // previous link          
    Link* succ;               // successor (next) link         
    Elem val;                 // the value
};

template<typename Elem> 
class list {
    
    Link<Elem>* node;    // one beyond the last link 
    int length;          // the length of the list

public:
    list() : node{new Link<Elem>}, length{0}{ }      // create one beyond the last link
    ~list();                // destroy all the  links
    
    class iterator;         // member type: iterator
    
    iterator begin() {return  iterator(node->succ) ;}        // iterator to first element          
    iterator end()  {return iterator(node) ;}           // iterator to one beyond last element
    
    iterator insert(iterator p, const Elem& v);         // insert v into list before p         
    iterator erase(iterator p);                         // remove p from the list
    
    void push_back(const Elem& v)  {insert(end(), v);}  // insert v at end          
    void push_front(const Elem& v) {insert(begin(), v);}  // insert v at front          
    
    void pop_front();           // remove the first element          
    void pop_back();            // remove the last element
    
    Elem& front();              // the first element         
    Elem& back();               // the last element
    
    int size(){return length;}    // get the list size
    // . . . 
}; 

template<typename Elem>         // requires Element<Elem>() 
class list<Elem>::iterator { 
    Link<Elem>* curr;              // current link 
public:
    friend class list;
    iterator(Link<Elem>* p) :curr{p} {}
    
    iterator& operator++() {curr = curr->succ; return *this; }   // forward          
    iterator& operator--() { curr = curr->prev; return *this;}   // backward 
    
    Elem& operator*() { return curr->val; }   // get value (dereference)
    
    bool operator==(const iterator& b) const { return curr==b.curr; }
    bool operator!= (const iterator& b) const { return curr!=b.curr; } 
    
    Link<Elem>* getLink(){return curr;}
}; 

template<typename Elem> 
list<Elem>::~list()
 // destroy all the  links
{
    for (auto p = begin(); p!=end(); ++p)
         erase(p);
    delete node; // delete the one before end link
}    


template<typename Elem> 
typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)  //non funziona
// insert v into list after p   
{
    Link<Elem> *nl = new Link<Elem>(v, p.curr->prev, p.curr);   // create newlink(value,prev,succ)
    
    p.curr->prev->succ = nl;    // newlink become the successor of previous link
    p.curr->prev = nl;          // newlink become the previous of current link
    
    ++length;                     // increment the list size
    
    return --p;                 // return the iterator after p
}
template<typename Elem> 
typename list<Elem>::iterator list<Elem>::erase(iterator p)
// remove p from the list
{
    p.curr->prev->succ =  p.curr->succ;    // the successor become the successor of previous link
    p.curr->succ->prev =  p.curr->prev;    // the previous become the previous of the successor link
    delete p.curr;  // free
    --length;
    return ++p;     // return iterator at the next link
}     


template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3) 
void out(Iterator first, Iterator last)  
// print all the list value
{          
    for (Iterator p = first; p!=last; ++p)                   
        std::cout << *p << " ";
    std::cout << "\n";
} 



int main()
{
    list<int> lst;
    
    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);
    
    list<int>::iterator i = lst.begin();
    
    ++i;
    
    lst.insert(i, 10);
    out(lst.begin() ,lst.end());
    

    printf("Hello World");

    return 0;
}
