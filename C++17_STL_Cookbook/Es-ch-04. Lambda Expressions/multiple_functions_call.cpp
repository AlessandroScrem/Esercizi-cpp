/******************************************************************************

Calling multiple functions with the same input

*******************************************************************************/

#include <iostream>

template <typename ...F>
static auto multicall (F  ...functions){
    return [=] (auto x) { (void) std::initializer_list<int>{
            ((void)functions(x), 0)...};
        };
}

template <typename F ,typename ...Xs>
static auto for_each(F f, Xs ...xs) {
    (void) std::initializer_list<int>{((void)f(xs), 0)...};
}

static auto brace_print (char a, char b) {
    return [=] (auto x) {std::cout << a << x << b << ", "; };
}

int main()
{
    auto f  (brace_print('(', ')'));
    auto g  (brace_print('[', ']'));
    auto h  (brace_print('{', '}'));
    auto nl ([] (auto) {std::cout << '\n';});

    auto call_fgh (multicall(f, g, h, nl));

    // For each of the numbers we want to print them individually three times surrounded
    // by different pairs of braces/parentheses.
    // This way, we can do a single function call and end up with five calls to our multifunction,
    // which doesÂ another fourÂ calls to f, g, h, and nl
    for_each(call_fgh, 1, 2, 3, 4, 5);

    return 0;
}

