/******************************************************************************

Catching readable exceptions from std::iostream errors

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <system_error>
#include <cstring>

using namespace std;


int main()
{

    ifstream f;
    f.exceptions(f.failbit | f.badbit);

    try {
        f.open("non exixtent.txt");

        int i;
        f >> i;

        cout << "integer has value: " << i << '\n';

    } catch (ios_base::failure& e) {
        cerr << "caught error: ";
        if(errno) {
            cerr << strerror(errno) << '\n';
        } else {
            cerr << e.what() << 'n';
        }
    }

    return 0;
}
