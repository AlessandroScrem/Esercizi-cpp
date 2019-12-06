/******************************************************************************

Calculating the error sum of two vectors

*******************************************************************************/

#include <iostream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>

using namespace std;

#ifndef M_PI
namespace
{
    const double M_PI = std::acos(-1.0);
}
#endif

int main()
{

    const size_t sig_len{100};
    vector<double> as(sig_len); // a for analog
    vector<int>    ds(sig_len); // d for digital

    auto sin_gen ([n{0}] () mutable { return 5.0 * sin(n++ * 2.0 * M_PI / 100); });

    generate(begin(as), end(as), sin_gen);
    copy(begin(as), end(as), begin(ds));

    copy(begin(as), end(as), ostream_iterator<double>{cout, " "});
    cout << '\n';

    copy(begin(ds), end(ds), ostream_iterator<int>{cout, " "});
    cout << '\n';

    cout << inner_product(begin(as), end(as), begin(ds),
                          0.0, std::plus<double>{},
                          [] (double a, double b) {return pow(a-b, 2); })
         << '\n';


    return 0;
}
