/******************************************************************************

Automatically handling resources with std::unique_ptr

*******************************************************************************/

#include <iostream>
#include <memory>
#include <string>

using namespace std;

class Foo
{
public:
    string name;
    Foo(string n) : name{move(n)}
        { cout << "CTOR " << name << '\n'; }
    ~Foo() { cout << "DTOR " << name << '\n'; }
};

void process_item(unique_ptr<Foo> p)
{
    if(!p) { return; }

    cout << "Processing " << p->name << '\n';
}

int main()
{
    // After we left the scope, both objects are destructed immediately
    {
        unique_ptr<Foo> p1{new Foo{"Foo"}};
        auto            p2{make_unique<Foo>("bar")};
    }

    // When process_item returns, the object is destroyed
    process_item(make_unique<Foo>("Foo1"));

    // foo2 is destroyed when process_item returns
    // foo3 will continue living until the main function returns
    auto p1 (make_unique<Foo>("Foo2"));
    auto p2 (make_unique<Foo>("Foo3"));

    process_item(move(p1));

    cout << "End of main()\n";

    return 0;
}
