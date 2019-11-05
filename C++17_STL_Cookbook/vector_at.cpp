/******************************************************************************

Accessing std::vector instances the fast or the safe way

*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;


int main()
{

    const size_t container_size {1000};
    vector<int> v (container_size, 123);

try {
        std::cout << "Out of range element value: "
                  << v.at(container_size + 10) << '\n';

    } catch (const std::out_of_range &e) {
        std::cout << "Ooops, out of range access detected: "
                  << e.what() << '\n';
    }

    return 0;
}

