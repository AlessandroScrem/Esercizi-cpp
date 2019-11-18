/******************************************************************************

Composing functions by concatenation

*******************************************************************************/

#include <iostream>
#include <functional>

// concat arbitrarily takes many parameters.
// These parameters will be functions, such as f, g, and h,
// the result will be another function object that applies f(g(h(...))) on any input:
template <typename T, typename ...Ts>
auto concat(T t, Ts ...ts){
    if constexpr(sizeof ...(ts) > 0) {
             return [=] (auto ...parameters) {
                 return t (concat(ts...)(parameters...));
             };
    }
    else {
        return t;
    }
}

int main()
{
    // The combined function looks like a single normal function,
    // and the compiler is also able to concatenate those functions
    // without any unnecessary overhead
    // result is 30, because 2 * 3 * (2 + 3) is 30
    auto twice ([] (int i) { return i * 2; });
    auto trice ([] (int i) { return i * 3; });

    auto combined (concat(twice, trice, std::plus<int>{}));

    std::cout << combined(2, 3) << '\n';

    return 0;
}

