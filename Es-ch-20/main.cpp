/******************************************************************************


*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>


using namespace std;


// error() simply disguises throws:
[[noreturn]] inline  void error(const string& s)
{
    throw runtime_error(s);
}




int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {




    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



