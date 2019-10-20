/******************************************************************************

Drill
1. Read some floating-point values (at least 16 values) from a file into a vector<double> called vd.
2. Output vd to cout.
3. Make a vector vi of type vector<int> with the same number
    of elements as vd;copy the elements from vd into vi.
4. Output the pairs of (vd[i],vi[i]) to cout, one pair per line.
5. Output the sum of the elements of vd.
6. Output the difference between the sum of the elements of vd and the sum of the elements of vi.
7. There is a standard library algorithm called reverse that takes a sequence (pair of iterators)
    as arguments; reverse vd,and output vd to cout.
8. Compute the mean value of the elements in vd; output it.
9. Make a new vector<double> called vd2 and copy all elements of vd with values
    lower than (less than) the mean into vd2.
10. Sort vd; output it again.
*******************************************************************************/


#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

template <typename T>
void out(T& t){
    for(auto p : t)
        std::cout << p << std::endl;
}

template <typename T, typename C>
void out_pair(T& vd, C& vi){
    for (size_t i=0; i<vd.size(); ++i)
        std::cout <<  "vd[" << i <<"] " << vd[i] <<  " vi[" << i <<"] " << vi[i] << std::endl;
}



int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {
    /**/
     std::vector<double>vd;
     const std::string fname{"double.txt"};

     std::ifstream ifs{fname};
     if(!ifs) std::cerr << "can't open " << fname << std::endl;

// 1. Read some floating-point values (at least 16 values) from a file into a vector<double> called vd.
// 2. Output vd to cout.

     double val{0};
     while(ifs >> val)
         vd.push_back(val);
     out(vd);
     std::cout << std::endl;

// 3. Make a vector vi of type vector<int> with the same number
     std::vector<int>vi(vd.size());
     std::copy(vd.begin(),vd.end(),vi.begin());
     out(vi);
     std::cout << std::endl;

// 4. Output the pairs of (vd[i],vi[i]) to cout, one pair per line.
     out_pair(vd,vi);
     std::cout << std::endl;

     double vdsum = std::accumulate(vd.begin(),vd.end(),0.0);
     double visum = std::accumulate(vi.begin(),vi.end(),0.0);

//5. Output the sum of the elements of vd.
// 6. Output the difference between the sum of the elements of vd and the sum of the elements of vi.
     std::cout << "sum(vd) = " << vdsum << std::endl;
     std::cout << "sum(vi) = " << visum << std::endl;
     std::cout << "sum(vd) - sum(vi) = " << vdsum - visum << std::endl;
     std::cout << std::endl;

// 7. There is a standard library algorithm called reverse that takes a sequence (pair of iterators)
//     as arguments; reverse vd,and output vd to cout.
     std::reverse(vd.begin(),vd.end());
     out(vd);

// 8. Compute the mean value of the elements in vd; output it.

     double  vdmean = vdsum/vd.size();
     std::cout << "the mean of vd is :" << vdmean << std::endl;
     std::cout << std::endl;

// 9. Make a new vector<double> called vd2 and copy all elements of vd with values
//     lower than (less than) the mean into vd2.

     std::vector<double>vd2;
     vd2.resize(vd.size());
     auto it = std::copy_if(vd.begin(),vd.end(), vd2.begin(), [&](double v){return v< vdmean;});
     vd2.resize(std::distance(vd2.begin(),it));  // shrink container to new size
     out(vd2);
     std::cout << std::endl;

     std::sort(vd2.begin(),vd2.end());
     out(vd2);
     std::cout << std::endl;








     }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



