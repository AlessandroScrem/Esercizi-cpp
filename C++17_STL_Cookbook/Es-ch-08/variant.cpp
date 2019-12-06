/******************************************************************************

Storing different types with std::variant

*******************************************************************************/

#include <iostream>
#include <variant>
#include <string>
#include <algorithm>
#include <list>

using namespace std;

class cat
{
    string name;
public:
    cat(string n) :name{n}  {}
    void meow() const {
        cout << name << " says Meow!\n";
    }
};

class dog
{
    string name;
public:
    dog(string n) :name{n}  {}
    void woof() const {
        cout << name << " says Woof!\n";
    }
};

using animal = variant<dog, cat>;

template <typename T>
bool is_type(const animal &a){
    return holds_alternative<T>(a);
}

// twofold function object, overload that accepts dogs and  cat
// it just calls the woof or the meow function
struct animal_voice
{
    void operator() (const dog &d) const { d.woof(); }
    void operator() (const cat &c) const { c.meow(); }
};

int main()
{
    list<animal> l {cat{"Tuba"}, dog{"Balou"}, cat{"Bobby"}};

    // print the contents of theÂ list three times,
    // and each time in a different way. One way is using variant::index().
    // BecauseÂ animalÂ is an alias ofÂ variant<dog, cat>,
    // a return value of 0 means that the variant holds a dog instance.
    // Index 1 means it is a cat. The order of the types in the variant specialization is the key here.
    for (const animal &a : l) {
        switch (a.index()) {
        case 0:
            get<dog>(a).woof();
            break;
        case 1:
            get<cat>(a).meow();
            break;
        }
    }
    cout << "-----\n";

    // We can also explicitly ask for every type.
    // The get_if<dog> returns a dog-typed pointer to the internal dog instance.
    // If there is no dog instance inside, then the pointer is null.
    // This way, we can try to get at different types until we finally succeed:
    for (const animal &a : l) {
        if(const auto d (get_if<dog>(&a)); d) {
            d->woof();
        } else if (const auto c (get_if<cat>(&a)); c) {
            c->meow();
        }
    }
    cout << "-----\n";

    // The last and most elegant way is variant::visit.
    // This function accepts a function object and a variant instance
    for (const animal &a : l) {
        visit(animal_voice{}, a);
    }
    cout << "-----\n";

    // count the number of cats and dogs in the variant list
    // used in combination with std::count_if to
    // return us the number of instances of this type
    cout << "There are "
         << count_if(begin(l), end(l), is_type<cat>)
         << " cats and "
         << count_if(begin(l), end(l), is_type<dog>)
         << " dogs in the list.\n";

    return 0;
}
