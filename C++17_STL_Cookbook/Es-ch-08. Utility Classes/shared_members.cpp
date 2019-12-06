/******************************************************************************

Sharing different member values of the same object

*******************************************************************************/

#include <iostream>
#include <memory>
#include <string>

using namespace std;

struct person
{
    string name;
    size_t age;

    person(string n, size_t a)
        : name{n}, age{a}
    { cout << "CTOR " << name << '\n'; }
    ~person() { cout << "DTOR " << name << '\n'; }
};



int main()
{

    shared_ptr<string> shared_name;
    shared_ptr<size_t> shared_age;

    {
        auto sperson (make_shared<person>("John Doe", 30));

        // specific pointers to a member of a shared object
        // it take 2 arguments:
        // 1) the original shared pointer that maintains the person object and,
        // 2) the address of the object the new shared pointer
        shared_name = shared_ptr<string>(sperson, &sperson->name);
        shared_age  = shared_ptr<size_t>(sperson, &sperson->age);

    }

    cout << "name: "  << *shared_name
         << "\nage: " << *shared_age << '\n';

    return 0;
}
