/******************************************************************************

Sampling data in large vectors

*******************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <random>
#include <iomanip>
#include <iterator>

using namespace std;

int main()
{

    const size_t data_points    {100000};
    const size_t sample_points  {100};
    const double   mean {10};
    const double dev {3};

    random_device rd;
    mt19937 gen {rd()};
    normal_distribution<> d {mean, dev};

    vector<int> v;
    v.reserve(data_points);

    generate_n(back_inserter(v), data_points, [&] { return  d(gen); });

    vector<int> samples;
    v.reserve(sample_points);

    sample(begin(v), end(v), back_inserter(samples),
           sample_points, mt19937{random_device{}()});

    map<int, size_t> hist;

    for (int i : samples) {
        ++hist[i];
    }

    for (const auto &[value, count] : hist) {
        cout << setw(2) << value << " "
             << string(count, '*') << '\n';
    }


    return 0;
}
