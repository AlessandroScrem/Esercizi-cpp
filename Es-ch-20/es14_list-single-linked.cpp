/******************************************************************************

Chapter 20: 
14. Define a singly-linked list, slist, in the style of std::list.
    Which operations from list could you reasonably eliminate from slist
    because it doesn’t have back pointers?

*******************************************************************************/
#include <stdio.h>
#include <string>
#include <iostream>

template<typename Elem>
struct Link {
    Link(const Elem& v = Elem{0} ,Link* s = nullptr)
        : val{v}, succ{s}{}

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
//    iterator& operator--() { curr = curr->prev; return *this;}   // backward

    Elem& operator*() { return curr->val; }   // get value (dereference)

    bool operator==(const iterator& b) const { return curr==b.curr; }
    bool operator!= (const iterator& b) const { return curr!=b.curr; }

};

template<typename Elem>
list<Elem>::~list()
 // destroy all the  links
{
    while (node != nullptr) {
//        std::cout << "delete : "<< node->val << node << std::endl;
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

    auto prev = node;
    while (prev->succ != it.curr) // find the link before it;
        prev = prev->succ;

    auto *nl = new Link<Elem>(val, it.curr);   // create newlink(value,succ)
    prev->succ = nl;    // newlink become the successor of previous link

    return iterator(nl);                 // return the iterator at the newly inserted element
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::erase(iterator it)
// remove it from the list
{
    if(it.curr == nullptr) return iterator(it);     // nothing to do
    auto prev = node;
    while (prev->succ != it.curr) // get the iterator before it;
        prev = prev->succ;
    prev->succ = it.curr->succ;  // the successor become the successor of previous link

//    std::cout << "delete : " << it.curr << std::endl;
    delete it.curr;  // free
    return iterator(prev->succ);     // return iterator at the next link
}

template<typename Elem>
void list<Elem>::push_front(const Elem& v)
{
    node = new Link<Elem>{v, node};
//    std::cout << "new : "<< node->val  << node << std::endl;

}

template<typename Elem>
void list<Elem>::push_back(const Elem& v)
{
    if(!node) {push_front(v); return;} // first link

    auto it = begin();
    while(it.curr->succ != nullptr) ++it;
    it.curr->succ = new Link<Elem>{v, nullptr};
//    std::cout << "new : "<< it.curr->succ->val << it.curr->succ << std::endl;

}

template<typename Iterator>  // requires Input_iterator<Iter>() (ยง19.3.3)
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
    lst.insert(lst.end(), 5);

    list<int>::iterator i = lst.begin();

    ++i;

    lst.insert(i, 10);
    out(lst.begin() ,lst.end());

    i=lst.begin();  ++i; ++i;
    lst.erase(i);
    std::cout << "Erase 2 : " << std::endl;
    out(lst.begin() ,lst.end());

    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }
/**/

}

