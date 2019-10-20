/******************************************************************************

Chapter 21:
7. Write a binary search function for a vector<int> (without using the standard one).
    You can choose any interface you like. Test it.
    How confident are you that your binary search function is correct?
    Now write a binary search function for a list<string>. Test it.
    How much do the two binary search functions resemble each other?
    How much do you think they would have resembled each other if you had not known about the STL?

*******************************************************************************/

#include <string>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <typename Iter, typename T>
Iter search(Iter first, Iter last, const T& val){
    while(first!=last && *first!= val)++first;
    return first;
}


template<typename T>
bool vector_search(vector<T>& v, const T& val){
    for(auto p : v)
        if(p == val)return true;
    return false;
}

template<typename T>
bool list_search(list<T>& v, const T& val){
    for(auto p : v)
        if(p == val)return true;
    return false;
}



template<typename Cont>
bool search(Cont& v, typename  Cont::value_type const &val){
    for(auto p : v)
        if(p == val)return true;
    return false;
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

        vector<int>vi{3,6,3,8,3,8,5,767,776,3443,99,334};
        list<string>ls{"pluto","pippo","paperino","annabella"};

        auto val = 99;
        if(search(vi,val))
            cout << "Found " << val << endl;
        else
            cout << "Not found " << endl;

        string vals = "paperino";
        if(search(ls,vals))
            cout << "Found " << vals << endl;
        else
            cout << "Not found " << endl;

/* STL implementation

        auto ret = search(vi.begin(),vi.end(),776);
        if(ret!=vi.end())
            cout << "Found " << *ret << endl;
        else
            cout << "Not found " << endl;

        auto ret2 = search(ls.begin(),ls.end(),"pippo");
        if(ret2!=ls.end())
            cout << "Found " << *ret2 << endl;
        else
            cout << "Not found " << endl;
*/

    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



