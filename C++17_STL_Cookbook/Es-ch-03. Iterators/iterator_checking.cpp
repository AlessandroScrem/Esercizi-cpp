/******************************************************************************

Automatically checking iterator code with checked iterators

*******************************************************************************/


#include <iostream>
#include <vector>

// to enable sanitizer fo msvc run in debug mode!

int main()
{

    std::vector<int> v{1, 2, 3};
    v.shrink_to_fit();

    const auto it (std::begin(v));
    //  print the dereferenced iterator, which is completely fine
    std::cout << *it << '\n';

    v.push_back(123);

    //  iterator is still pointing to the old location, and we cannot know what really happened
    std::cout << *it << '\n'; // bad bad bad!

    return 0;
}

