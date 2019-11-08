/******************************************************************************

Simplifying compile time decisions with constexpr-if

*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

template <typename T>
struct addable       {
    T val;

    addable(T v) : val{v} {}

    template <typename U>
    T add(U x) const {
        if constexpr (std::is_same_v<T, std::vector<U>>) {
            auto copy (val);
            for (auto &n : copy) {
                n += x;
            }
            return copy;
        } else {
            return val + x;
        }
    }
};



int main()
{

   std::cout << addable<int>{1}.add(2)
             << std::endl;  // is 3

   std::cout << addable<float>{1.0}.add(2)
             << std::endl;          // is 3.0

   std::cout << addable<std::string>{"aa"}.add("bb")
              << std::endl; // is "aabb"

   std::vector<int> v {1, 2, 3};
   std::vector<int> v1 = addable<std::vector<int>>{v}.add(10);
   // is std::vector<int>{11, 12, 13}

   for (const auto i : v1) {
       std::cout << i << std::endl;
   }

   std::vector<std::string> sv {"a", "b", "c"};
   std::vector<std::string> sv1 = addable<std::vector<std::string>>{sv}.add(std::string{"z"});
   // is {"az", "bz", "cz"}

   for ( const auto &i : sv1) {
       std::cout << i << std::endl;
   }


    return 0;
}
