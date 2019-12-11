/******************************************************************************

Performing exception safe shared locking with std::unique_lock and std::shared_lock

*******************************************************************************/

#include <iostream>
#include <shared_mutex>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono_literals;

// global instance for the sake of simplicity
shared_mutex shared_mut;

using shrd_lck = shared_lock<shared_mutex>;
using uniq_lck = unique_lock<shared_mutex>;

static void print_exclusive()
{
    uniq_lck l{shared_mut, defer_lock};

    if(l.try_lock()){
        cout << "Got exclusive lock.\n";
    } else {
        cout << "Unable to lock exclusively.\n";
    }
}

static void exclusive_trow()
{
    uniq_lck l{shared_mut};
    throw 123;
}

int main()
{

    {
        shrd_lck sl1{shared_mut};
        cout << "shared lock once.\n";

        {
            shrd_lck sl2{shared_mut};
            cout << "shared lock twice.\n";

            print_exclusive(); // Unable to lock exclusively
        }

        cout << "shared lock once again.\n";
        print_exclusive(); // Unable to lock exclusively

    }
    cout << "lock is free.\n";

    try{
        exclusive_trow();  // lock created and destroyed automatically
    } catch (int e) {
        cout << "Got exception " << e << '\n';
    }
    print_exclusive(); // got exclusive lock


    return 0;
}
