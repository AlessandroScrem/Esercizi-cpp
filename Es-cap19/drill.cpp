/******************************************************************************
Chapther 19. Vector, Templates, and Exceptions

1. Define template<typename T> struct S { T val; };. 
2. Add a constructor, so that you can initialize with a T. 
3. Define variables of types S<int>, S<char>, S<double>, S<string>, 
    and S<vector<int>>; initialize them with values of your choice. 
4. Read those values and print them. 
5. Add a function template get() that returns a reference to val. 
6. Put the definition of get() outside the class. 
7. Make val private. 
8. Do 4 again using get(). 
9. Add a set() function template so that you can change val. 
10. Replace set() with an S<T>::operator=(const T&). Hint: Much simpler than §19.2.5. 
11. Provide const and non-const versions of get(). 
12. Define a function template<typename T> read_val(T& v) that reads from cin into v. 
13. Use read_val() to read into each of the variables from 3 except the S<vector<int>> variable. 
14. Bonus: Define input and output operators (>> and <<) for vector<T>s. 
    For both input and output use a { val, val, val } format. 
    That will allow read_val() to also handle the S<vector<int>> variable. 
Remember to test after each step. 
*******************************************************************************/
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T> 
class S {
    T val;
    
public: 
    
    S(T t) : val{t}{;}
    
    void out() const {cout << &val << "\n";} //print val address
    const T& get() const {return val;}       // get const
    T& get() {return val;}                   // get non-const
    
    void set(const T& t) {val = t;}
    
    S& operator=(const T& t) {return *this;}
   
    template<class U> friend ostream & operator << (ostream &out, const S<U>& u);
    template<class U> friend istream & operator >> (istream &in,  S<U> &u);
};


template <class U>
ostream & operator << (ostream &out, const S<U> &u) 
{
    out << u.val << endl;
    return out;
}


template <class U> 
istream & operator >> (istream &in, S<U> &u) 
{ 
    in >> u.val;
    return in; 
}

template <typename T>
ostream& operator<<(ostream& out, vector<T> &t)
{
    out << "{";
    for (int i=0; i<t.size();++i){
        out << t.at(i);
        if(i < (t.size()-1)) out << ", ";
    }
    out << "}";
    return out;
}

template <typename T>
istream& operator>>(istream& in, vector<T> &t)
{
    T val;
    in >> val;
    t.push_back(val);
    return in;
}

template <typename T> 
void read_val(T& v)
{
        cin >> v;
}

int main()
{

    vector<int> v1{10,20,30};
    vector<int> v2{1000,2000,3000};
    
    //inizializzazione
    S<int> si{10};
    S<char> sc{'c'};
    S<double> sd{10.5};
    S<string> sstr{"hello world"};
    S<vector<int>> sv{v1};
    
    //modifica
    si.set(20);
    sc.set('d');
    sd.set(20.5);
    sstr.set("Hello Hello...");
    sv.set(vector<int>{100,200,300});
    
    //assegnazione
    S<int> si2{30};
    si = si2;
    sc = S<char>{'e'};
    sd = S<double>{30.5};
    sstr = S<string>{"Hello asssignement..."};
    S<vector<int>> sv2{v2};
    sv = sv2;

    //stampa
    cout << "si = " << si.get() <<"\n";
    cout << "sc = " << sc.get() <<"\n";
    cout << "sd = " << sd.get() <<"\n";
    cout << "sstr = " << sstr.get() <<"\n";
    for(int i: sv.get()) cout << "sv = " << i <<"\n";
    
    // get reference
    S<int&> ri = si.get();
    si.out();
    ri.out();
    // get const
    const S<int> ci = si.get();
    ci.out();

    //template function read_val()
    cout << "Enter integer :";
    read_val(si);
    cout << si << "\n";

    cout << "Enter char :";
    read_val(sc);
    cout << sc << "\n";

    cout << "Enter double :";
    read_val(sd);
    cout << sd << "\n";

    cout << "Enter string :";
    read_val(sstr);
    cout << sstr << "\n";

    cout << "Enter vector<int> :";
    read_val(sv.get());
    cout << sv.get() << "\n";

    return 0;
}


