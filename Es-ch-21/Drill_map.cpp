/******************************************************************************

Drill
1. Define a map<string,int> called msi.
2. Insert ten (name,value) pairs into it, e.g., msi["lecture"]=21.
3. Output the (name,value) pairs to cout in some format of your choice.
4. Erase the (name,value) pairs from msi.
5. Write a function that reads value pairs from cin and places them in msi.
6. Read ten pairs from input and enter them into msi.
7. Write the elements of msi to cout.
8. Output the sum of the (integer) values in msi.
9. Define a map<int,string> called mis.
10. Enter the values from msi into mis;
    that is, if msi has an element ("lecture",21), mis should have an element (21,"lecture").
11. Output the elements of mis to cout.
*******************************************************************************/


#include <string>
#include <iostream>
#include <map>
#include <algorithm>


template <typename T>
void out(T& t){
    for(auto &p : t)
        std::cout << p.first << " " << p.second << std::endl;
}

template <typename Iter>
void sum(Iter b, Iter e){
    int result =0;
    while(b!=e){
        result += b->second;
        ++b;
    }
     std::cout << "Somma val: "<< result  << std::endl;
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
    /**/
        std::map<std::string,int> msi{
            {"Baseball",    10},
            {"Football",    12},
            {"Volleyball",  90},
            {"Tennis" ,     34},
            {"Basketball",  67},
            {"Athletics",   95},
            {"Badminton",    5},
            {"Boxing",      85},
            {"Canoe",       29},
            {"Hokey",       28}};

    out(msi);
    std::cout << "\n";

    msi.erase("Tennis");
    out(msi);
    std::cout << "\n";

/* 5. Write a function that reads value pairs from cin and places them in msi.

    std::pair<std::string,int>p{};
    while(std::cin >> p.first >> p.second)
        msi.insert(p);
    out(msi);
    std::cout << "\n";
*/
    sum(msi.begin(),msi.end());

// 9. Define a map<int,string> called mis.
    std::map<int,std::string>mis;

    std::pair<int,std::string>e{};
    for(auto &p : msi){
        e.second = p.first;
        e.first = p.second;
        mis.insert(e);
    }
    out(mis);
    std::cout << "\n";

     }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



