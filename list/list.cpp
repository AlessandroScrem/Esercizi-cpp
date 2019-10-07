/******************************************************************************


// Implementation of std lib list<T>
//
// implemented:
//
// constructor
// push_back()
// push_front()
// size()
// insert()
// erase()
// iterator begin() end()




*******************************************************************************/

#include <stdio.h>
#include <string>
#include <iostream>

struct Range_error : std::out_of_range {
// enhanced vector range error reporting
    int index;
    Range_error(int i) :std::out_of_range("Range error: "+std::to_string(i)), index(i) { }
};
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

    //Elem& front();              // the first element
    //Elem& back();               // the last element

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
    for(auto p = begin();length>0;){
        p = erase(p);
    }
    delete node; // delete the one before end link
}


template<typename Elem>
typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)  //non funziona
// insert v into list after p
{
    Link<Elem> *nl = new Link<Elem>(v, p.curr->prev, p.curr);   // create newlink(value,prev,succ)
    //std::cout << nl << " " << nl->val << std::endl;

    p.curr->prev->succ = nl;    // newlink become the successor of previous link
    p.curr->prev = nl;          // newlink become the previous of current link

    ++length;                     // increment the list size

    return --p;                 // return the iterator after p
}
template<typename Elem>
typename list<Elem>::iterator list<Elem>::erase(iterator p)
// remove p from the list
{
    auto next = p.curr->succ;  // move iterator to next link
    p.curr->prev->succ =  p.curr->succ;    // the successor become the successor of previous link
    p.curr->succ->prev =  p.curr->prev;    // the previous become the previous of the successor link
    //std::cout << p.curr << " " << p.curr->val << std::endl;
    delete p.curr;  // free
    --length;
    return next;     // return iterator at the next link
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
    setlocale(LC_ALL, "en_US.UTF-8");

try {

    list<int> lst;

    lst.push_back(1);
    lst.push_back(2);
    lst.push_back(3);
    lst.push_back(4);

    list<int>::iterator i = lst.begin();

    ++i;

    //lst.insert(i, 10);
    out(lst.begin() ,lst.end());

    auto h = high(lst.begin() ,lst.end());
    std::cout << *h << std::endl;

    std::cout << "fine\n";

    }
    catch (Range_error& re) {
        std::cerr << "bad index: " << re.index << "\n";
    }
    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }
/**/

}
