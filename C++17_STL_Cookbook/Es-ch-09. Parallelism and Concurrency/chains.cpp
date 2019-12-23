/******************************************************************************

Implementing a tiny automatic parallelization library with std::future

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <thread>
#include <string>
#include <sstream>
#include <future>

using namespace std;
using namespace chrono_literals;

using seconds = chrono::duration<double>;

#define PARALLEL

struct pcout : public stringstream
{
    static inline mutex cout_mutex;
    ~pcout() {
        lock_guard<mutex> l{cout_mutex};
        cout << rdbuf();
        cout.flush();
     }
};
// create an std::string object from a C-string.
// sleep for 3 seconds to simulate computationheavy
static string create(const char *s)
{
    pcout{} << "3s CREATE " << quoted(s) << '\n';
    this_thread::sleep_for(3s);
    return{s};
}

// accepts two string objects as arguments and returns their concatenation
// wait 5-second to simulate a time-consuming task
static string concat(const string &a, const string &b)
{
    pcout{} << "5s CONCAT "
            << quoted(a) << " "
            << quoted(b) << '\n';
    this_thread::sleep_for(5s);
    return a + b;
}

// accepts a string and concatenates it with itself.
// It shall take 3 seconds to do this
static string twice(const string &s)
{
    pcout{} << "3s TWICE " << quoted(s) << '\n';
    this_thread::sleep_for(3s);
    return s + s;
}

// asynchronize accepts a function f and returns a callable object that captures it
// We can call this callable object with any number of arguments,
// and then it will capture those together with f in another callable object which it returns to us
// This last callable object can be called without arguments.
// It does then call f asynchronously with all the arguments it captures
template <typename F>
static auto asyncronize(F f)
{
    return [f] (auto ...xs) {
        return [=] () {
            return async(launch::async, f, xs...);
        };
    };
}

//  accepts a function f, and captures it in a callable object that it returns.
// That object can be called with a number of future objects.
// It will then call .get() on all the futures, apply f to them and return its result
template <typename F>
static auto fut_unwrap(F f)
{
    return [f] (auto ...xs) {
        return f(xs.get()...);
    };
}

// Helper function also accept a function f, returns a callable object that captures f.
// Callable object accept any number of arguments, returns captured together with f in another callable object.
// Final callable object can then be called without arguments.
// It does then call all the callable objects that are captured in the xs... pack.
// These return futures which need to be unwrapped with fut_unwrap.
// The future-unwrapping and actual application of the real function f
// on the real values from the futures does again happen asynchronously using std::async
template <typename F>
static auto async_adapter(F f)
{
    return [f] (auto ...xs) {
        return [=] () {
            return async(launch::async, fut_unwrap(f), xs()...);
        };
    };
}

int main()
{

    // We must use asynchronize on create because it shall return a future,
    // but we will feed it with real values instead of futures
    auto pcreate (asyncronize(create));
    // The function async_adapter makes a completely normal function wait
    // for future arguments and return a future result.
    // It is kind of a translating wrapper from the synchronous to the asynchronous world
    auto pconcat (async_adapter(concat));
    auto ptwice  (async_adapter(twice));

    const auto tic (chrono::steady_clock::now());


#ifdef PARALLEL
    // parallel version
    auto result(
                pconcat(
                    ptwice(
                        pconcat(
                            pcreate("foo "),
                            pcreate("bar "))),
                    pconcat(
                        pcreate("this "),
                        pcreate("that "))));

    cout << "Setup done. Nothing executed yet.\n";
    cout << result().get() << '\n';
    cout << "PARALLEL\n";

#else
    // serial version
    auto result(
                concat(
                    twice(
                        concat(
                            create("foo "),
                            create("bar "))),
                    concat(
                        create("this "),
                        create("that "))));

    cout << "Setup done. Nothing executed yet.\n";
    cout << result << '\n';
    cout << "SERIAL\n";

#endif
    const auto toc (chrono::steady_clock::now());
    cout << "Elapsed time: " << seconds(toc -tic ).count() << '\n';

    return 0;
}
