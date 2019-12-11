/******************************************************************************

Synchronizing concurrent std::cout use

*******************************************************************************/

#include <iostream>
#include <mutex>
#include <thread>
#include <sstream>
#include <vector>

using namespace std;

// parallel cout: print safetely
struct pcout : public stringstream
{
    static inline mutex cout_mutex;

    ~pcout() {
        lock_guard<mutex> l{cout_mutex}; // mutex is released leaving the scope
        cout << rdbuf();
        cout.flush();
    }
};

static void print_cout(int id)
{
    cout << "cout hello from " << id << '\n';
}

static void print_pcout(int id)
{
    pcout{} << "pcout hello from " << id << '\n';
}

int main()
{
    vector<thread> v;

    for(size_t i{0}; i < 10; ++i ){
        v.emplace_back(print_cout, i);
    }

    for(auto &t : v ) { t.join(); }

    cout << "-------------------------\n";

    v.clear();
    for(size_t i{0}; i < 10; ++i){
        v.emplace_back(print_pcout, i);
    }

    for(auto &t : v) { t.join(); }

    return 0;
}
