/******************************************************************************

Automatically handling shared heap memory with std::shared_ptr

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

void f(shared_ptr<Foo> sp)
{
    cout << "f: use counter at "
         << sp.use_count() << '\n';
}

int main()
{
    shared_ptr<Foo> fa;

    {
        cout << "Inner scope begin\n";

        shared_ptr<Foo> f1{new Foo{"foo"}};
        auto            f2 (make_shared<Foo>("bar"));

        cout << "f1: use counter at: " <<  f1.use_count() << '\n';
		// shared ptr f1 is going to be increment to 2
        fa = f1;
        cout << "f1: use counter at: " <<  f1.use_count() << '\n';
    }
    cout << "Back to outer scope\n";

    cout << fa.use_count() << '\n';

    // shared_ptd copied to f()
    cout << "first f() call\n";
    f(fa);

    // shared_ptd moved to f()
    cout << "second f() call\n";
    f(move(fa));

    cout << "and of main()\n";


    return 0;
}
