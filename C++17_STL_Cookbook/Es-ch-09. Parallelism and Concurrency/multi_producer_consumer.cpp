/******************************************************************************

Implementing the multiple producers/consumers idiom with std::condition_variable

*******************************************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;
using namespace chrono_literals;

// synchronized printing helper
struct pcout : public stringstream
{
    static inline mutex cout_mutex;
    ~pcout() {
        lock_guard<mutex> l{cout_mutex};
        cout << rdbuf();
    }
};

queue<size_t>   q;
mutex           q_mutex;
bool            production_stopped{false};
condition_variable go_produce;
condition_variable go_consume;

// Producer: write values into the same queue
// parameters:
// ID number,
// total number of items to produce
// stock limit
//
static void producer(size_t id, size_t items, size_t stock)
{
    // Locks the queue's mutex and unlocks it again in the go_produce.wait call.
    // It waits for the condition that the queue size is below the stock threshold:
    for (size_t i = 0; i < items; ++i) {
        unique_lock<mutex> lock(q_mutex);
        go_produce.wait(lock, [&] { return q.size() < stock; });
        q.push(id * 100 + i); //  hundreds in the number are the producer ID

        pcout{} << "  Producer " << id << "--> item "
              << setw(3) << q.back() << '\n';

        go_consume.notify_all();
        this_thread::sleep_for(90ms); // sleep period simulates producing items
    }
    pcout{} << "EXIT: Producer " << id << '\n';
}
// consumer function that only accepts a consumer ID
// waiting for items if the production has not stopped, or the queue is not empty
static void consumer(size_t id)
{
    while(!production_stopped || !q.empty()) {
        unique_lock<mutex> lock(q_mutex);
        // wait call when the queue contains items
        // return false in case of the timeout
        if(go_consume.wait_for(lock, 1s, [] { return !q.empty(); } )){
            pcout{} << "                item "
                    << setw(3) << q.front()
                    << " --> Consumer "
                    << id << '\n';
            q.pop();                        // consume item
            go_produce.notify_all();        // notify the producers
            this_thread::sleep_for(130ms);  // simulate that consuming items
        }
    }
    pcout{} << "EXIT Consumer " << id << '\n';
}

int main()
{
    vector<thread> workers;
    vector<thread> consumers;

    for (size_t i = 0; i < 3; ++i) {
        workers.emplace_back(producer, i, 15, 5);
    }

    for (size_t i = 0; i < 5; ++i) {
        consumers.emplace_back(consumer, i);
    }

    for (auto &t : workers) { t.join(); }
    production_stopped = true;
    for (auto &t : consumers) { t.join(); }

    return 0;
}
