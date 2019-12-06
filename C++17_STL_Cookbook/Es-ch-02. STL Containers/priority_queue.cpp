/******************************************************************************

Implementing a personal to-do list using std::priority_queue

*******************************************************************************/

#include <iostream>
#include <queue>
#include <tuple>
#include <string>

int main()
{
    using item_type = std::pair<int, std::string>;
    std::priority_queue<item_type> q;

    std::initializer_list<item_type> il {
        {1, "dishes"},
        {0, "watch tv"},
        {2, "do homework"},
        {0, "read comics"},
    };
    for (const auto &p : il) {
        q.push(p);
             }
     while(!q.empty()) {
         std::cout << q.top().first << ": " << q.top().second << '\n';
         q.pop();
     }
     std::cout << '\n';

    return 0;
}

