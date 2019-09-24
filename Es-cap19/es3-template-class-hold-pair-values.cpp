/******************************************************************************

3. Write a template class Pair that can hold a pair of values of any type.
     Use this to implement a simple symbol table like the one we used in the calculator (§7.8). 

******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

template <typename T, typename U>
class Pair{
    T val1;
    U val2;
public:
    Pair(T t, U u): val1{u}, val2{u}{;}
    T getVal1(){return val1;}
    U getVal2(){return val2;}
    
};

int main()
{
    Pair<int,char> p{10,'c'};
    cout << "val1 : " << p.getVal1() << endl; 
    cout << "val2 : " << p.getVal2() << endl; 
 
    return 0;
}

