/******************************************************************************

Chapter 21:
4. Implement count_if() yourself. Test it.

*******************************************************************************/

#include <string>
#include <iostream>
#include <vector>


template<typename T, typename Op>
T count_if(std::vector<T>& t, Op op){
    T retval = 0;
    for (auto first = t.begin(); first< t.end();++first) {
        if(op(*first))retval += *first;
    }
    return retval;
}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
    /**/
        std::vector<int> vi{1,2,3,4,5,6,7,8,9,10};

        std::cout << "Size : " << vi.size() << std::endl;
        std::cout << "Count : " << count_if(vi, [](int i) {return i<5;}) << std::endl;



     }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



