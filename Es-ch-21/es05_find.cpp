/******************************************************************************

Chapter 21:
5. What would we have to do if we couldn’t return end() to indicate “not found”?
    Redesign and re-implement find() and count() to take iterators to the first and last elements.
    Compare the results to the standard versions.
*******************************************************************************/

#include <string>
#include <iostream>
#include <vector>


template<typename Iter, typename Op>
int count_if(Iter first, Iter last, Op op, int retval =0){
    while (first!= last) {
        if(op(*first))++retval;
        ++first;
    }
    return retval;
}

template<typename Iter>
bool find(Iter first, Iter last, const int& val){
    while (first!= last){
        if(*first==val) return true;
        ++first;
    }
   return false;

}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
    /**/
        std::vector<int> vi{1,2,3,4,5,6,7,8,9,10};

        std::cout << "Size : " << vi.size() << std::endl;
        std::cout << "Count : " << count_if(vi.begin(),vi.end(),
                                            [](int i) {return i<5;}) << std::endl;
        int num = 20;
        if(find(vi.begin(),vi.end(), num))
            std::cout << "Found num : " << num << "\n" ;
        else
            std::cout << "Not found! " << num << "\n" ;



     }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



