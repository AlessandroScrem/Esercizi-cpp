/******************************************************************************

Chapter 20: 
20. Run a small timing experiment to compare the cost of using vector and list.
    You can find an explanation of how to time a program in §26.6.1.
    Generate N random int values in the range [0:N). As each int is generated,
    insert it into a vector<int> (which grows by one element each time).
    Keep the vector sorted; that is, a value is inserted after every previous
    value that is less than or equal to the new value and before every previous
    value that is larger than the new value.
    Now do the same experiment using a list<int> to hold the ints.
    For which N is the list faster than the vector? Try to explain your result.
    This experiment was first suggested by John Bentley.

*******************************************************************************/


#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <chrono>
#include <iomanip>


template<typename Cont>
long long populate(Cont& t, int n){
// insert n random int in Cont& t keeping the Cont in ascending order
// out the time spent to pupuate the Container

    auto t1 = std::chrono::system_clock::now();                   // begin time

    auto i = n;
    while(i--) {
       int size = rand()%n; // generate new int
       auto it = t.begin();
       while (it!= t.end() && size>= *it  )
           ++it;            // get the position in ascending order
       t.insert(it,size);
    }

    auto t2 = std::chrono::system_clock::now();                    // end time
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();

}

template<typename Iterator>  // requires Input_iterator<Iter>() (§19.3.3)
void out (Iterator first, Iterator last)          // return an iterator to the element in [first,last) that has the highest value
{
    for (Iterator p = first; p!=last; ++p)
        std::cout << *p << "\n";
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
        const int size = 5000; // max size of element
        const int step = 500;   // increment
        const int rep = 5;   // repeat  populate() # times

        std::cout <<"Size vec [ms] lst [ms] vec-list [ms]\n";

         for (int i=0;i<size; i+=step) {
            long long vectime = 0, lsttime = 0;
            for (int ii = 0; ii<rep;++ii) {
                std::vector<int> v1;
                std::list<int> l1;
                vectime += populate(v1,i);
                lsttime += populate(l1,i);
            }
            vectime /=rep; lsttime /=rep; // calc the mean
            std::cout << std::left << std::setw(8) << i
                      << std::setw(10) << vectime
                      << std::setw(10) << lsttime
                      << std::setw(10) << vectime-lsttime
                      << "\n";
        }

    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }
/**/

}



