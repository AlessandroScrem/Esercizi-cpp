/******************************************************************************

Implementing handy helper functions with fold expressions

*******************************************************************************/
#include <iostream>
#include <vector>
#include <set>
#include <string>

template <typename ... Ts>
auto sum(Ts ... ts)      {
    return (ts + ...);
}


template <typename R, typename ... Ts>
auto matches(const R& range, Ts ... ts) {
    return (std::count(std::begin(range), std::end(range), ts) + ...);
}

template <typename T, typename ... Ts>
bool insert_all(T &set, Ts ... ts) {
    return (set.insert(ts).second && ...);
}

template <typename T, typename ... Ts>
bool within(T min, T max, Ts ...ts) {
    return ((min <= ts && ts <= max) && ...);
}

template <typename T, typename ... Ts>
void insert_all(std::vector<T> &vec, Ts ... ts) {
    (vec.push_back(ts), ...);
}

int main()
{

    int the_sum {sum(1, 2, 3, 4, 5)}; // Value: 15
    std::cout << the_sum << std::endl;

    std::string a {"Hello "};
    std::string b {"World"};
    std::cout << sum(a, b) << '\n'; // Output: Hello World

    // Usage example
    // Match ranges against individual items
    std::vector<int> v {1, 2, 3, 4, 5};
    std::cout << matches(v,                  2, 5) << std::endl; // returns 2
    std::cout << matches(v,              100, 200) << std::endl; // returns 0
    std::cout << matches("abcdefg", 'x', 'y', 'z') << std::endl; // returns 0
    std::cout << matches("abcdefg", 'a', 'd', 'f') << std::endl; // returns 3

    // Usage example
    // Check if multiple insertions into a set are successful
    std::set<int> my_set {1, 2, 3};
    insert_all(my_set, 4, 5, 6); // Returns true
    insert_all(my_set, 7, 8, 2); // Returns false, because the 2 collides

    std::set<int> my_set2 {1, 2, 3};
    insert_all(my_set2, 4, 2, 5);
    // Returns false
    // set contains {1, 2, 3, 4} now, without the 5!

    // Usage example
    // Check if all the parameters are within a certain range
    within( 10,  20,    1, 15, 30);    // --> false
    within( 10,  20,    11, 12, 13);   // --> true
    within(5.0, 5.5,    5.1, 5.2, 5.3); // --> true

    std::string aaa {"aaa"};
    std::string bcd {"bcd"};
    std::string def {"def"};
    std::string zzz {"zzz"};
    within(aaa, zzz,    bcd, def); // --> true
    within(aaa, def,    bcd, zzz); // --> false

    // Usage example
    // Pushing multiple items into a vector
    std::vector<int> v1 {1, 2, 3};
    insert_all(v1, 4, 5, 6);
    std::cout << "insert_all" << std::endl;
    for (auto i : v1) {
        std::cout << i << std::endl;
    }

    return 0;
}
