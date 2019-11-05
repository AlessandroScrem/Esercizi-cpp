/******************************************************************************

Inserting items efficiently and conditionally into std::map
1. The key does not exist yet. Create a fresh key-value pair.
2. The key does exist already. Take the existing item and modify it

*******************************************************************************/

#include <iostream>
#include <list>
#include <string>
#include <map>

using namespace std;

struct billionaire {
    string name;
    double dollars;
    string country;
};

int main()
{

      list<billionaire> billionaires {
          {"Warren Buffet", 75.6, "USA"},
          {"Bill Gates", 86.0, "USA"},
          {"Jeff Bezos", 72.8, "USA"},
          {"Amancio Ortega", 71.3, "Spain"},
          {"Mark Zuckerberg", 56.0, "USA"},
          {"Carlos Slim", 54.5, "Mexico"},
          // ...
          {"Liliane Bettencourt", 39.5, "France"},
          // ...
          {"Bernard Arnault", 41.5, "France"},
          // ...
          {"Wang Jianlin", 31.3, "China"},
          {"Li Ka-shing", 31.2, "Hong Kong"}
          // ...
      };

      // Since C++17
      map<string, pair< billionaire, size_t>> m;
      for (const auto &b : billionaires) {
          auto [iterator, success] = m.try_emplace(b.country,b, 1);
           if (!success) {                                      // country already exist in map
              if(b.dollars> iterator->second.first.dollars){    // if exist new richest
                      iterator->second.first = b;
              }
              iterator->second.second += 1;
          }
      }
      for (const auto & [key, value] : m) {
           const auto &[b, count] = value;
                   cout << b.country << " : " << count
                   << " billionaires. Richest is "
                   << b.name << " with " << b.dollars
                   << " B$\n";
       }

      return 0;
}

