/******************************************************************************

Deleting items from an unsorted std::vector in O(1) time

*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T>
void quick_remove_at(vector<T> &v, size_t idx){
    if(idx < v.size()){
        v[idx].~T(); // call destructor
        v[idx] = move(v.back());
        v.pop_back();
    }
}
template <typename T>
void quick_remove_at(std::vector<T> &v, typename std::vector<T>::iterator it)      {
     if (it != std::end(v)) {
         *it = std::move(v.back());
         v.pop_back();
     }
}

struct A{
    int val;
    A(int v): val{v}{}
    ~A(){cout << val << "destructor \n";}
};

int main()
{
    std::vector<int> v {123, 456, 789, 100, 200};
    quick_remove_at(v, 2);
    for (int i : v) {
        std::cout << i << ", ";
    }
    std::cout << '\n';

    quick_remove_at(v, std::find(std::begin(v), std::end(v), 123));
    for (int i : v) {
        std::cout << i << ", ";
    }
    std::cout << '\n';


    vector<A> va{A{1},A{2},A{3}};

    std::cout << "quick_remove_at 2" << std::endl;
    quick_remove_at(va,1);
    for(const A& i: va){
         std::cout << i.val  << ",";
    }
    std::cout << std::endl;


    return 0;
}

