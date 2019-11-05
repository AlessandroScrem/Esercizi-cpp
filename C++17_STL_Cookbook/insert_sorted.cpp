/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;

template<typename C, typename T>
void insert_sorted( C &v, const T &item){
    const auto insert_pos (lower_bound(begin(v), end(v), item));
    v.insert(insert_pos, item);    
}

int main()
{
    vector<string> v {"some", "random", "value", "words",
                      "without", "order", "aaa", "yyy"};
    
    assert(false == is_sorted(begin(v),end(v)));
    sort(begin(v),end(v));
    assert(true == is_sorted(begin(v),end(v)));
    
    insert_sorted(v, "foobar");
    insert_sorted(v, "zzz");
    
    for(const auto &w : v){
        std::cout << w << " ";
    }
    std::cout << std::endl;
    
    

    return 0;
}
