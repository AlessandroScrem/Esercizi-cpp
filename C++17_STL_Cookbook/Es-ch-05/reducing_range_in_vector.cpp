/******************************************************************************

Limiting the values of a vector to a specific numeric range with std::clamp

*******************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// return fn that  scale val in range min-max nim to new_max
static auto norm (int min, int max, int new_max){
    const double diff (max - min);
    return [=] (int val) { return int ((val - min) / diff * new_max); };
}

// return fn that cut val in range min to max
static auto clampval (int min, int max) {
    return [=] (int val) -> int { return clamp(val, min, max); };
}


int main()
{

    vector<int> v{0, 1000, 5, 250, 300, 800, 900, 321};

    const auto [min_it, max_it] (minmax_element(begin(v), end(v)));

    vector<int> v_norm;
    v_norm.reserve(v.size());

    transform(begin(v), end(v), back_inserter(v_norm), norm(*min_it, *max_it, 255));
    copy(begin(v_norm), end(v_norm), ostream_iterator<int>{cout, ", "});
    cout << '\n';

    transform(begin(v), end(v), begin(v_norm), clampval(0, 255));
    copy(begin(v_norm), end(v_norm), ostream_iterator<int>{cout, ", "});
    cout << '\n';

    return 0;
}
