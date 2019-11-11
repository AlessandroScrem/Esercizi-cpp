/******************************************************************************

Implementing algorithms in terms of iterators

*******************************************************************************/

#include <iostream>

class fibit{

    size_t i{0};
    size_t a{0};
    size_t b{1};
public:
    fibit() = default;

    explicit fibit(size_t i_) : i{i_} {}

    size_t operator*() const { return b; }
    fibit& operator++() {
        const size_t old_b{b};
        b += a;
        a = old_b;
        ++i;
        return *this;
    }
    bool operator!=(fibit &o) { return i != o.i;}
};

class fib_range{
    size_t end_n;

public:
    fib_range(size_t end_n_) : end_n{end_n_} {}
    fibit begin() const { return fibit();}
    fibit end()   const { return fibit(end_n);}
};

int main()
{

    for(size_t i : fib_range(10)){
        std::cout << i << ", ";
    }
    std::cout << "\n";

    return 0;
}

