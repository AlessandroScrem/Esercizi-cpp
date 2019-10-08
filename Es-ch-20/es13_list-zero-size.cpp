/******************************************************************************

Chapter 20: 
13. We don’t really need a “real” one-past-the-end Link for a list.
    Modify your solution to the previous exercise to use 0 to represent a pointer
    to the (nonexistent) one-past-the-end Link (list<Elem>::end());
    that way, the size of an empty list can be equal to the size of a single pointer

*******************************************************************************/
#include <stdio.h>
#include <string>
#include <iostream>

template<typename Elem>
struct Link {
    Link(const Elem& v = Elem{0} ,  Link* p = nullptr,   Link* s = nullptr)
        : val{v}, prev{p}, succ{s}{}

    Link* prev;               // previous link
    Link* succ;               // successor (next) link
    Elem val;                 // the value
};

template<typename Elem>
class list {

    Link<Elem>* node;    // the first link

public:
    list() : node{nullptr}{ }      // create one beyond the last link
    ~list();                // destroy all the  links

    class iterator;         // member type: iterator

    iterator begin() {return  iterator(node) ;}         // iterator to first element
    iterator end()  {return iterator(nullptr) ;}        // iterator to one beyond last element

    iterator insert(iterator p, const Elem& v);         // insert v into list before p
    iterator erase(iterator p);                         // remove p from the list

    void push_back(const Elem& v);//  {insert(end(), v);}  // insert v at end
    void push_front(const Elem& v);// {insert(begin(), v);}  // insert v at front

    void pop_front();           // remove the first element
    void pop_back();            // remove the last element

    Elem&front();               // the first element
    Elem& back();               // the last element

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

};

template<typename Elem>
list<Elem>::~list()
 // destroy all the  links
{
    while (node != nullptr) {
        auto p = node->succ;
        delete node;
        node = p;
    }
}


template<typename Elem>
typename list<Elem>::iterator list<Elem>::insert(iterator it, const Elem& val)  //non funziona
// insert v into list after it
{
    if(it.curr == nullptr) { push_back(val); return end();}    // insert at end

    Link<Elem> *nl = new Link<Elem>(val, it.curr->prev, it.curr);   // create newlink(value,prev,succ)

    if(nl->prev) nl->prev->succ = nl;    // newlink become the successor of previous link
    if(nl->succ) nl->succ->prev = nl;    // newlink become the previous of current link

    return iterator(nl);                 // return the iterator at the newly inserted element
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::erase(iterator it)
// remove it from the list
{
    if(it.curr == nullptr) return iterator(it);     // nothing to do
    iterator ret = iterator(it.prev);               // move iterator to next link

    if(it.curr->prev) it.curr->prev->succ =  it.curr->succ;         // the successor become the successor of previous link
    if(it.curr->succ) it.curr->succ->prev =  it.curr->prev;         // the previous become the previous of the successor link
    delete it.curr;  // free

    return ret;     // return iterator at the next link
}

template<typename Elem>
void list<Elem>::push_front(const Elem& v)
{
    node = new Link<Elem>{v, nullptr, node};
    if (node->succ != nullptr) node->succ->prev = node;
}

template<typename Elem>
void list<Elem>::push_back(const Elem& v)
{
    if(!node) {push_front(v); return;} // first link

    auto it = begin();
    while(it.curr->succ != nullptr) ++it;
    it.curr->succ = new Link<Elem>{v, it.curr};
}

template<typename Iterator>  // requires Input_iterator<Iter>() (ยง19.3.3)
void out(Iterator first, Iterator last)
// print all the list value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << *p << " ";
    std::cout << "\n";
}

template<typename Iter>  // requires Input_iterator<Iter>() (§19.3.3)
Iter high(Iter first, Iter last)
// return an iterator to the element in [first,last) that has the highest value
{
    Iter high = first;
    for (Iter p = first; p!=last; ++p)
        if (*high<*p) high = p;
    return high;
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
    lst.insert(lst.end(), 5);

    list<int>::iterator i = lst.begin();

    ++i;

    lst.insert(i, 10);
    out(lst.begin() ,lst.end());

    auto h = high(lst.begin() ,lst.end());
    std::cout << "High : "<< *h << std::endl;


    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }
/**/

}

