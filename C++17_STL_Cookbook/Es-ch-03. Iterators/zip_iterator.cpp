/******************************************************************************

Building your own zip iterator adapter

*******************************************************************************/

#include <iostream>
#include <vector>
#include <numeric>

#include <valarray>

class zip_iterator
{
    using it_type = std::vector<double>::iterator;

    it_type it1;
    it_type it2;
public:
    zip_iterator(it_type iterator1, it_type iterator2)
        : it1{iterator1}, it2{iterator2}{}
    zip_iterator& operator++() {
        ++it1;
        ++it2;
        return *this;
    }
    bool operator!=( const zip_iterator& o) const{
        return it1 != o.it1 && it2 != o.it2;
    }
    bool operator==( const zip_iterator& o) const{
        return !operator!=(o);
    }
    std::pair<double, double> operator*() const{
        return {*it1, *it2};
    }
};
/*
 * to make the iterator compatible with STL algorithms,
 * so we define the needed type trait boilerplate code for that.
 * It basically says that this iterator is just a forward iterator,
 *  and it returns pairs of double values when dereferenced.
 *  Although we do not use difference_type in this recipe,
 * different implementations of the STL might need it in order to compile
 */
namespace std {
template <>
struct iterator_traits<zip_iterator> {
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<double, double>;
    using difference_type = long int;
};
}

class zipper{

    using vec_type = std::vector<double>;
    vec_type &vec1;
    vec_type &vec2;
public:
    zipper(vec_type &va, vec_type &vb)
        : vec1{va}, vec2{vb} {}
    zip_iterator begin() const { return {std::begin(vec1), std::begin(vec2)}; }
    zip_iterator end()   const { return {std::end(vec1), std::end(vec2)}; }
};


int main()
{
    using namespace std;
    vector<double> a{1.0, 2.0, 3.0};
    vector<double> b{4.0, 5.0, 6.0};

    // The zipper object combines them to one vector-like range
    // where we see pairs of a and b values:
    zipper zipped(a,b);

    // we will define a helper lambda thatÂ takes a pair,
    // multiplies its members, and adds it to an accumulator
    const auto add_product ([] (double sum, const auto &p) {
        return sum + p.first * p.second;
    });

    const auto dot_product (accumulate(
                                begin(zipped), end(zipped), 0.0, add_product));
    cout << dot_product <<'\n';

    // By the way, if you came here to see the most elegant way to do a dot product in C++,
    // and don't really care about the concept of zip-iterators,
    // you should have a look at std::valarray.

    {
    std::valarray<double> a{1.0, 2.0, 3.0};
    std::valarray<double> b{4.0, 5.0, 6.0};
    std::cout << (a * b).sum() << '\n';
    }

    return 0;
}

