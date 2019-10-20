/******************************************************************************

Chapter 21:
3. Implement count() yourself. Test it.

*******************************************************************************/

#include <string>
#include <iostream>
#include <vector>


template<typename T>
T count(std::vector<T>& t){
    T retval = 0;
    for (auto first = t.begin(); first< t.end();++first) {
        retval += *first;
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
        std::cout << "Count : " << count(vi) << std::endl;



     }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



