/******************************************************************************

Adding polymorphy by wrapping lambdas into std::function

*******************************************************************************/

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <functional>

// auto is not allowed in function prototype
/*
static auto consumer (auto &container)
{
    return [&] (auto value) {
        container.push_back(value);
    };
}
*/

// changed to template
template <typename C>
static auto consumer (C &container)
{
    return [&] (auto value) {
        container.push_back(value);
    };
}

template <typename C>
static void print (const C &c)
{
    for (auto i : c){
        std::cout << i << ", ";
    }
    std::cout << '\n';
}

int main()
{
    std::deque<int>  d;
    std::list<int>   l;
    std::vector<int> v;

    const std::vector<std::function<void(int)>> consumers
            { consumer(d), consumer(l), consumer(v) };

    // we feed 10 integer values to all the data structures by looping over the values
    for (int i{0}; i < 10; ++i){
        for(auto &&consume : consumers){
            consume(i);
        }
    }

    print(d);
    print(l);
    print(v);

    return 0;
}

