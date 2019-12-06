/******************************************************************************

Defining functions on the run using lambda expressions

*******************************************************************************/

#include <iostream>
#include <string>

int main()
{

    auto just_one ( []() {return 1; } );
    auto just_two ( []   {return 2; } ); //  parameterless function, are optional

    std::cout << just_one() << "," << just_two() << '\n';

    auto plus ( [] (auto l, auto r) { return l +r ;} );

    std::cout << plus(1, 2) << '\n';
    std::cout << plus(std::string{"a"}, "b") << '\n';

    std::cout << [] (auto l, auto r) { return l + r;} (1, 2)
              << '\n';
    // to modify its own captured variables, we use the mutable keyword,
    // as the compiler would not allow it otherwise
    auto counter ([count = 0] () mutable { return ++count; });

    for (size_t i{0}; i < 5; ++i) {
        std::cout << counter() << ", ";
    }
    std::cout << '\n';

    // variables and capture them by reference
    int a{0};
    auto incrementer ([&a] { ++a; });

    incrementer();
    incrementer();
    incrementer();

    std::cout << "Value of 'a' after 3 incrementer() calls: "
              << a << '\n';

    // This example is currying.
    // Currying means that we take a function that can accept some parameters
    // and store it in another function object, which accepts fewer parameters
    // for exaple plus function defined before:

    auto plus_ten ([=] (int x) { return plus (10, x);});
    std::cout << plus_ten(5) << '\n';

    return 0;
}

