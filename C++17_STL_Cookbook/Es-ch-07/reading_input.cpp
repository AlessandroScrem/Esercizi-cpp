/******************************************************************************

Reading values from user input

*******************************************************************************/

#include <iostream>
#include <string>

using namespace std;


int main()
{

    cout << "Please enter two numbers:\n";
    int x;
    double y;

    if(cin >> x >> y) {
        cout << "You entered: " << x
             << " and " << y << '\n';
    } else {
       cout << "Oh no, thet did not go well!\n";
       cin.clear();
       cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "now please enter some "
            "comma-separated names:\n> ";
    for(string s; getline(cin >> ws, s, ',');){
        if(s.empty()) { break; }
        cout << "name: \"" << s << "\"\n";
    }

    return 0;
}
