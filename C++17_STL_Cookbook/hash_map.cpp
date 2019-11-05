/******************************************************************************

Using std::unordered_map with custom types

*******************************************************************************/

#include <iostream>
#include <unordered_map>

struct coord {
    int x;
    int y;
};

bool operator==(const coord &l, const coord &r)      {
    return l.x == r.x && l.y == r.y;
}

namespace std
{
    template <>
    struct hash<coord>
    {
         using argument_type = coord;
         using result_type   = size_t;

         // We are just adding the numeric member values of struct coord,
         // which is a poor hashing technique, but for the sake of showing how to implement it
         result_type operator()(const argument_type &c) const
         {
             return static_cast<result_type>(c.x)
                     + static_cast<result_type>(c.y);
         }
    };
}

int main()
{
    std::unordered_map<coord, int> m {{{0, 0}, 1},
                                      {{0, 1}, 2},
                                      {{2, 1}, 3}};

    for (const auto & [key, value] : m) {
        std::cout << "{(" << key.x
                  << ", " << key.y
                  << "): " << value << "} ";
    }
    std::cout << '\n';

    return 0;
}

