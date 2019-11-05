/******************************************************************************

Letting the constructor automatically deduce the resulting template class type

*******************************************************************************/
#include <iostream>
#include <string>

template <typename T1, typename T2, typename T3>
class my_wrapper {
    T1 t1;
    T2 t2;
    T3 t3;
public:
    explicit my_wrapper(T1 t1_, T2 t2_, T3 t3_): t1{t1_}, t2{t2_}, t3{t3_}{}
    /* ...*/
};

template <typename T>
struct sum {
    T value;
    template <typename ... Ts>
    sum(Ts&& ... values) : value{(values + ...)} {}
};

/*
    If we provide integers, floats, and doubles, the compiler needs to
    figure out which type fits all the values without information loss. In order to
    achieve that, we provide an explicit deduction guide:
*/
template <typename ... Ts>
sum(Ts&& ... ts) -> sum<std::common_type_t<Ts...>>;

int main()
{
    /* before C++17
    my_wrapper<int, double, const char *> wrapper {123, 1.23, "abc"};
    */
    
    // C++17 code
    my_wrapper wrapper {123, 1.23, "abc"};
    
    /* sum explaination ...
    In the first line we instantiate a sum object with constructor arguments of type unsigned, double, int, and float.
    The std::common_type_t returns double as the common type, so we get a sum<double> instance.
    
    In the second line, we provide an std::string instance and a C-style string. 
    Following our deduction guide, the compiler constructs an instance of type sum<std::string>.
    */
    sum s {1u, 2.0, 3, 4.0f};
    sum string_sum {std::string{"abc"}, "def"};
    
    std::cout << s.value << '\n'
              << string_sum.value << '\n';

    return 0;
}
