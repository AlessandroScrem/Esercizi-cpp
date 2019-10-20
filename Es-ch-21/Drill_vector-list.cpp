/******************************************************************************

Drill
    After each operation (as defined by a line of this drill) print the vector.

1. Define a struct Item { string name; int iid; double value; ... };,
    make a vector<Item>, vi, and fill it with ten items from a file.
2. Sort vi by name.
3. Sort vi by iid.
4. Sort vi by value; print it in order of decreasing value (i.e., largest value first).
5. Insert Item("horse shoe",99,12.34) and Item("Canon S400", 9988,499.95).
6. Remove (erase) two Items identified by name from vi.
7. Remove (erase) two Items identified by iid from vi.
8. Repeat the exercise with a list<Item> rather than a vector<Item>.
*******************************************************************************/


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

struct Item{
   std::string name;
   int iid;
   double value;
};

std::istream& operator>>(std::istream& is, Item& item){
    is >> item.name >> item.iid >> item.value;
    return is;
}
std::ostream& operator<<(std::ostream& os, Item& item){
    os << item.name  << " "
       << item.iid   << " "
       << item.value << std::endl;
    return os;
}


template <typename T>
void out (T& t){
    for(auto i: t)
        std:: cout << i;
}

//exercice with vector<Item>
void f1(){


    const std::string  fname{"item.txt"};
    std::vector<Item> vec;

    std::ifstream ifs(fname.c_str());
    if(!ifs) std::cerr << "can't open " << fname << "\n";
    Item item;
// 1:
    while(ifs >> item)
        vec.push_back(item);

    out(vec);
    std::cout << "\n";
// 2:
    std::sort(vec.begin(), vec.end(),  // sort by name
              [](const Item& a, const Item& b)
                    {return a.name<b.name;});
    out(vec);
    std::cout << "\n";

// 3:
    std::sort(vec.begin(), vec.end(),  // sort by iid
              [](const Item& a, const Item& b)
                    {return a.iid<b.iid;});
    out(vec);
    std::cout << "\n";

// 4:
    std::sort(vec.begin(), vec.end(),  // sort by value reverse order
              [](const Item& a, const Item& b)
                    {return a.value>b.value;});
    out(vec);
    std::cout << "\n";

// 5. Insert Item("horse shoe",99,12.34) and Item("Canon S400", 9988,499.95).
    vec.insert(vec.begin(), Item{"horse shoe",99,12.34});
    vec.insert(vec.begin(), Item{"Canon S400", 9988,499.95});
    out(vec);
    std::cout << "\n";

// 6. Remove (erase) two Items identified by name from vi.
    auto it = std::find_if(vec.begin(), vec.end(),[]( Item& a){
            return a.name == "horse shoe";});
    if (it != vec.end())
        vec.erase(it);
    out(vec);
    std::cout << "\n";

// 7. Remove (erase) two Items identified by iid from vi.
    auto ite = std::find_if(vec.begin(), vec.end(),[]( Item& a){
        return a.iid == 9988;});
    if (ite != vec.end())
        vec.erase(ite);
    out(vec);
   std::cout << "\n";
}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

//exercice with list<Item>

        const std::string  fname{"item.txt"};
        std::list<Item> lst;

        std::ifstream ifs(fname.c_str());
        if(!ifs) std::cerr << "can't open " << fname << "\n";
        Item item;
// 1:
        while(ifs >> item)
            lst.push_back(item);

        out(lst);
        std::cout << "\n";
// 2:
        lst.sort([](const Item& a, const Item& b) // sort by name
                    {return a.name<b.name;});
        out(lst);
        std::cout << "\n";

// 3:
        lst.sort([](const Item& a, const Item& b)  // sort by iid
                         {return a.iid<b.iid;});
        out(lst);
        std::cout << "\n";

// 4:
        lst.sort([](const Item& a, const Item& b)  // sort by value reverse order
                        {return a.value>b.value;});
        out(lst);
        std::cout << "\n";

// 5. Insert Item("horse shoe",99,12.34) and Item("Canon S400", 9988,499.95).
        lst.insert(lst.begin(), Item{"horse shoe",99,12.34});
        lst.insert(lst.begin(), Item{"Canon S400", 9988,499.95});
        out(lst);
        std::cout << "\n";

// 6. Remove (erase) two Items identified by name from vi.
        auto it = std::find_if(lst.begin(), lst.end(),[]( Item& a){
                return a.name == "horse shoe";});
        if (it != lst.end())
            lst.erase(it);
        out(lst);
        std::cout << "\n";

// 7. Remove (erase) two Items identified by iid from vi.
        auto ite = std::find_if(lst.begin(), lst.end(),[]( Item& a){
            return a.iid == 9988;});
        if (ite != lst.end())
            lst.erase(ite);
        out(lst);
       std::cout << "\n";

     }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



