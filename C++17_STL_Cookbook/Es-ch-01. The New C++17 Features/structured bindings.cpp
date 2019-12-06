/******************************************************************************

Using structured bindings to unpack bundled return values

*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

std::pair<int, int> divide_remainder(int dividend, int divisor){
    std::pair<int, int>result;
    if(divisor == 0)
        return  result;
    result.first = dividend / divisor;
    result.second = dividend % divisor;
    return result;
} 

struct employee {
    unsigned id;
    std::string name;
    std::string role;
    unsigned salary;
};

int main()
{
    const auto result (divide_remainder(16, 3));
    
    /* code before C++17
    std::cout << "16 / 3 is "
              << result.first << " with a remainder of "
              << result.second << '\n';
    */
    
    // code C++17
    auto [fraction, remainder] = divide_remainder(16, 3);
    std::cout << "16 / 3 is "
              << fraction << " with a remainder of "
              << remainder << '\n';
              
    std::vector<employee> employees {{102,"Bob","Employee",1200},{103,"Rob","HR",1300}};
    for (const auto &[id, name, role, salary] : employees) {
        std::cout << "Name: " << name
        << " Role: " << role
        << " Salary: " << salary << '\n';
    } 
    
    std::map<std::string, size_t> animal_population {
        {"humans", 7000000000},
        {"chickens", 17863376000},
        {"camels", 24246291},
        {"sheep", 1086881528},
        /* ... */
        };
        
    for (const auto &[species, count] : animal_population) {
        std::cout << "There are " << count << " "
                  << species << " on this planet.\n";
    }    
    return 0;
}
