/******************************************************************************

Automatically parallelizing code that uses standard algorithms

*******************************************************************************/

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <execution>
#include <chrono>

using namespace std;

using seconds = chrono::duration<double>;

static bool odd(int n){ return n% 2; }


int main()
{

    vector <int> d(50000000);

    mt19937 gen;
    uniform_int_distribution<int> dis(0, 1000000);

    auto rand_num ([=] () mutable { return dis(gen); });

    const auto tic (chrono::steady_clock::now());

    // execution policy are:
    // seq(default),
    // par(parallel),
    // par_unseq (parallel vectorized)
    generate(execution::par, begin(d), end(d), rand_num);
    sort(    execution::par, begin(d), end(d));
    reverse( execution::par, begin(d), end(d));
    auto odds (count_if(execution::par, begin(d), end(d), odd));

    const auto toc (chrono::steady_clock::now());

    cout << "Time spent is: "
         << seconds(toc - tic).count()
         << " seconds\n";

    cout << (100.0 * odds / d.size())
         << "% of the numbers are odd.\n";



    return 0;
}
