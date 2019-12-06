/******************************************************************************

Using the erase-remove idiom on std::vector

*******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
      vector<int> v {1, 2, 3, 2, 5, 2, 6, 2, 4, 8};

      //4. The next step is to remove the items. What do we remove?
      //   There are multiple 2 values. Let's remove them.
      const auto new_end (remove(begin(v), end(v), 2));

      // 5. Interestingly, that was only one of the two steps.
      //    The vector still has the same size. The next line makes it actually shorter.
      v.erase(new_end, end(v));

      // 6. Let's stop by here in order to print the vector's content to the terminal, and then continue.
      for (auto i : v) {
          cout << i << ", ";
      }
      cout << '\n';

      // 7. Now, let's remove a whole class of items, instead of specific values.
      //    In order to do that, we define a predicate function first,
      //    which accepts a number as parameter, and returns true, if it is an odd number.
      const auto odd ([](int i) { return i % 2 != 0; });

      // 8. Now we use the remove_if function and feed it with the predicate function.
      //    Instead of removing in two steps as we did before, we do it in one.
      v.erase(remove_if(begin(v), end(v), odd), end(v));

      // 9. All odd items are gone now, but the vector's capacity is still at the old 10 elements.
      //    In a last step, we reduce that also to the actual current size of the vector.
      //    Note that this might lead the vector code to allocate a new chunk of memory that
      //    fits and moves all items from the old chunk to the new one.
      v.shrink_to_fit();

      // 10. Now, let's print the content after the second run of removing items and that's it.
      for (auto i : v) {
          cout << i << ", ";
      }
      cout << '\n';


    return 0;
}
