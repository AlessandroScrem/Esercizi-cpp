#include <iostream>
#include <array>
#include <vector>
#include <list>
#include <string>

using namespace std;

struct Range_error : out_of_range {	// enhanced vector range error reporting
    int index;
    Range_error(int i) :out_of_range("Range error: "+to_string(i)), index(i) { }
};

template <typename C>
void out(const C& c, std::string s)
{
    if(c.begin() == c.end()) return;

    std::cout << s << " : { ";
    for (auto i : c) {
         std::cout << i << " ";
    }
    std::cout << "}\n";
}

template <typename C>
void addval(C& c, int val)
{
    if(c.begin() == c.end()) return;
    for (auto i = c.begin() ; i != c.end();  ++i) {
         *i +=val;
     }
}

template<typename Iter1, typename Iter2>
// requires Input_iterator<Iter1>() && Output_iterator<Iter2>()
Iter2 copy2(Iter1 f1, Iter1 e1, Iter2 f2)
// copy [f1,e1] to [f2,f2+(e1–f1)] and returns f2
{
    if(f1==e1) return f2; // the sequence is empty, so that there is nothing to copy.
    for(Iter1 i = f1; i != e1; ++i)
        *f2++ =  *i;
    return f2;
}

int main()
{
try {
    const int size = 10;

    // 1 2 3
    array<int,10> ai;
    vector<int> vi{};
    list<int> li{};

    for (int i=0; i<size; ++i) {
        ai[i] = i;
        vi.push_back(i);
        li.push_back(i);
    }

    out(ai, "array");
    out(vi, "vector");
    out(li, "list");

    // 4
    array<int,10> ai2{ai};
    vector<int> vi2{vi};
    list<int> li2{li};

    // 5
    // Increase the value of each element in the array by 2;
    // increase the value of each element in the vector by 3;
    // increase the value of each element in the list by 5

    addval(ai2, 2);
    addval(vi2, 3);
    addval(li2, 5);

    out(ai2, "array 2");
    out(vi2, "vector 2");
    out(li2, "list 2");

    // 7
    //  copy the array into the vector
    copy2(ai.begin(), ai.end(), vi.begin() );
    out(vi, "array copy to vector");
    //  copy the list into the array
    copy2(li.begin(), li.end(), ai.begin() );
    out(ai, "list copy to array");

    // 8. Use the standard library find() to see if the vector contains the value 3
    int val = 3;
    auto result = find(vi.begin(), vi.end(), val);
    if(result == vi.end())
        std::cout << val << " not found ...\n";
    else
        std::cout << val <<  " found at position " << result-vi.begin() << "\n";

    // use find() to see if the list contains the value 27 and print out its position if it does
    int val2 = 27;
    auto result2 = find(li.begin(), li.end(), val2);
    if(result2 == li.end())
        std::cout << val2 << " not found ...\n";
    else{
        int pos = 0;
        for (auto i = li.begin(); i != result2 ; ++i) {
            ++pos;
        }
        std::cout << val2 <<  " found at position " << pos  << "\n";
    }

    }
    catch (Range_error& re) {
        cerr << "bad index: " << re.index << "\n";
    }
    catch (exception& e) {
        cerr << "exception: " << e.what() << endl;
    }
    catch (...) {
        cerr << "exception\n";
    }
}
