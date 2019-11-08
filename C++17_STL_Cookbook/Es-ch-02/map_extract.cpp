/******************************************************************************

Efficiently modifying the keys of std::map items

*******************************************************************************/

#include <iostream>
#include <list>
#include <string>
#include <map>

using namespace std;

template <typename M>
void print(const M &m)      {
    cout << "Race placement:\n";
    for (const auto &[placement, driver] : m) {
        cout << placement << ": " << driver << '\n';
    }
}

int main()
{
      map<int, string> race_placement {
          {1, "Mario"}, {2, "Luigi"}, {3, "Bowser"},
          {4, "Peach"}, {5, "Yoshi"}, {6, "Koopa"},
          {7, "Toad"}, {8, "Donkey Kong Jr."}};

      print(race_placement);

      {
      auto a (race_placement.extract(3));
      auto b (race_placement.extract(8));

      // Now we can swap Bowser's and Donkey Kong Jr.'s keys.
      // we can modify the keys of items which we extracted using the extract method.
      swap(a.key(), b.key());

      // std::map's insert method got a new overload in C++17 that accepts the handles of extracted nodes,
      // in order to insert them without touching the allocator
      race_placement.insert(move(a));
      race_placement.insert(move(b));
      }

      print(race_placement);

      return 0;
}

