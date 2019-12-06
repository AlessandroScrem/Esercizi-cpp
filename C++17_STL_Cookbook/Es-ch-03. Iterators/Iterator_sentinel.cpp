/******************************************************************************

Terminating iterations over ranges with iterator sentinels

*******************************************************************************/

#include <iostream>

class cstring_iterator_sentinel{};

class cstring_iterator
{
    const char *s {nullptr};
public:
    explicit cstring_iterator(const char *str) : s{str} {}
    char  operator*() const { return *s; }
    cstring_iterator& operator++() {
        ++s;
        return *this;
    }
    bool operator!=( const cstring_iterator_sentinel) const {
        return s != nullptr && *s != '\0';
    }
};

class cstring_range
{
    const char *s{nullptr};
public:
    cstring_range(const char *str) : s{str} {}
    cstring_iterator begin() const { return cstring_iterator{s};}
    cstring_iterator_sentinel end()   const { return {};}
};

int main(int argc, char *argv[])
{
    if(argc < 2) {
        std::cout << "Please provide one parameter.\n";
        return 1;
    }

    for (char c : cstring_range(argv[1])) {
        std::cout << c;
    }
    std::cout << '\n';

    return 0;
}

