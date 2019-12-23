/******************************************************************************

Getting canonical file paths from relative paths

*******************************************************************************/

#include <iostream>
//#include <filesystem>
#include <experimental/filesystem>


using namespace std;
//using namespace filesystem;

// system_complete require experimental
// canonical  composed paths require experimental
using namespace experimental::filesystem;

int main()
{
      path p {"testdir/foobar.txt"};

    cout << "current_path      : " << current_path()
         << "\nabsolute_path   : " << absolute(p).string()
         << "\nsystem_complete : " << system_complete(p)
         << "\ncanonical(p)    : " << canonical(p)
         << '\n';

    // concatenate folder names and filenames
    cout << path{"testdir"} / "foobar.txt" << '\n';

    cout << "canonical testdir     : "
         << canonical("foobar.txt", current_path() / "testdir")
         << "\ncanonical testdir 2 : "
         << canonical(p, current_path() / "testdir/..")
         << '\n';

    // test for the equivalence of two paths
    cout << "equivalence: "
         << equivalent("testdir/foobar.txt", "testdir/../testdir/foobar.txt")
         << '\n';

    return 0;
}
