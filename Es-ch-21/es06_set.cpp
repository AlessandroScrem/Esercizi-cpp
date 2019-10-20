/******************************************************************************

Chapter 21:
6. In the Fruit example in §21.6.5, we copy Fruits into the set.
    What if we didn’t want to copy the Fruits? We could have a set<Fruit*> instead.
    However, to do that, we’d have to define a comparison operation for that set.
    Implement the Fruit example using a set<Fruit*, Fruit_comparison>.
    Discuss the differences between the two implementations.

*******************************************************************************/

#include <string>
#include <iostream>
#include <vector>
#include <set>


using namespace std;

struct Fruit {
    string name;
    int count;
    ~Fruit(){cout << "distruttore Fruit "<< this->name << "\n";}
};

ostream& operator<<(ostream& out, Fruit* f){
    out << "{" <<f->name << "," << f->count << "}\n";
    return out;
}

struct Fruit_comparison {
    bool operator()(const Fruit* a, const Fruit* b) const
    {
        return a->count<b->count;
    }
};

template<typename Iter>
void out(Iter first, Iter last){
    while (first!=last){
        cout << *first;
        ++first;
    }
}
template<typename Iter>
void free(Iter first, Iter last){
    while (first!=last){
        delete *first;
        ++first;
    }
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

    set<Fruit*,Fruit_comparison> inventory;
    inventory.insert(new Fruit{"Kiwi",100});
    inventory.insert(new Fruit{"Quince",0});
    inventory.insert(new Fruit{"Plum",8});
    inventory.insert(new Fruit{"Apple",7});
    inventory.insert(new Fruit{"Grape",2345});
    inventory.insert(new Fruit{"Orange",99});

    out(inventory.begin(),inventory.end());
    free(inventory.begin(),inventory.end());



    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



