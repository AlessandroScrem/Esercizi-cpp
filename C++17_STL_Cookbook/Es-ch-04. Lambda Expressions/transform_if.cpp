/******************************************************************************

Implementing transform_if using std::accumulate and lambdas

*******************************************************************************/

#include <iostream>
#include <iterator>
#include <numeric>
#include <strstream>

template <typename T>
auto map(T fn){
    return [=] (auto reduce_fn) {
        return [=] (auto accum, auto input){
            return reduce_fn(accum, fn(input));
        };
    };
}

template <typename T>
auto filter (T predicate){
    return [=] (auto reduce_fn) {
        return [=] (auto accum, auto input) {
            if(predicate(input)) {
                return reduce_fn(accum, input);
            } else {
                return accum;
            }
        };
    };
}

int main()
{

    // std::istream_iterator<int> it {std::cin};
    // changed cin to istr
    std::istrstream istr{"1 2 3 4 5 6"};
    std::istream_iterator<int> it {istr};
    std::istream_iterator<int> end_it;

    auto even  ([] (int i) { return i % 2 == 0; });
    auto twice ([] (int i) { return i * 2; });

    auto copy_and_advance([] (auto it, auto input) {
        *it = input;
        return ++it;
    });

    static_cast<void>(std::accumulate(it, end_it,
                    std::ostream_iterator<int>{std::cout, ", "},
                    filter(even)(
                        map(twice)(
                            copy_and_advance
                        )
                    )));
    std::cout << '\n';

    return 0;
}

