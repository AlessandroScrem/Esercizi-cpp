#include <iostream>
#include <vector>

using namespace std;

vector<int> f(){
    vector<int> v{100,200,300};
    return v;
}
template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3)
void out (Iterator first, Iterator last)          // return an iterator to the element in [first,last) that has the highest value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << *p << " ";
    std::cout << "\n";
}

int main()
{

    //    const vector<int> v0{33,33,33};
        vector<int> v{22,33};
    //    v = v0;
        out(v.begin(), v.end());
        v = f();
    //    std::cout << v.size();
        out(v.begin(), v.end());


}
