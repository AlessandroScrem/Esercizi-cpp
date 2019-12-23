/******************************************************************************

Implementing a path normalizer

MiniGW 7.4 <filesystem> not found
*******************************************************************************/

#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

int main(int argc, char *argv[])
{

    if(argc != 2){
        cout << "Usage: " << argv[0] << " <path>\n";
        return 1;
    }

    const path dir{argv[1]};

    if(!exists(dir)){
        cout << "Path " << dir << " does not exist.\n";
        return 1;
    }
    // print a path through its .c_str() or .string() method
    //cout << canonical(dir).c_str() << '\n';
    cout << canonical(dir).string() << '\n';


    return 0;
}
