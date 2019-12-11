/******************************************************************************

Implementing the producer/consumer idiom with std::condition_variable

*******************************************************************************/

#include <iostream>
#include <queue>
#include <tuple>
#include <condition_variable>
#include <thread>

using namespace std;
using namespace chrono_literals;

queue<size_t>       q;
mutex               mut;
condition_variable  cv;
bool                finished{false};

// producer function.
// It accepts an argument items:
// the maximum number of items for production
static void producer(size_t items)
{
    for (size_t i{0}; i < items; ++i) {
        this_thread::sleep_for(100ms); //simulates some computational complexity
        {
            lock_guard<mutex> lk{mut};
            q.push(i);
        }
        cv.notify_all(); // wakes up the consumer
    }
    {
        lock_guard<mutex> lk{mut};
        finished = true;    // After having produced all items ...
    }
    cv.notify_all(); // wakes up the consumer
}

// consumer function.
// It takes no arguments
// blindly consume items until the queue runs empty
static void consumer()
{
    while(!finished){
        unique_lock<mutex> l{mut};
        // cv.wait: call unlocks the lock and waits until the condition is true
        // Then, it locks the mutex again
        cv.wait(l, [] { return !q.empty() || finished; });

        while (!q.empty()) {
            cout << "Got " << q.front()
                 << " from queue.\n";
            q.pop();  // consumes everything until the queue is empty
        }
    }
}

int main()
{
    thread t1{producer, 10};
    thread t2{consumer};
    t1.join();
    t2.join();

    cout << "Finished!\n";

    return 0;
}
