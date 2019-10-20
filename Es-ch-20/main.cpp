/******************************************************************************

Chapter 21:
9. Define an Order class with (customer) name, address, data, and vector<Purchase> members.
    Purchase is a class with a (product) name, unit_price, and count members.
    Define a mechanism for reading and writing Orders to and from a file.
    Define a mechanism for printing Orders. Create a file of at least ten Orders,
    read it into a vector<Order>, sort it by name (of customer), and write it back out to a file.
    Create another file of at least ten Orders of which about a third are the same as in the first file,
    read it into a list<Order>, sort it by address (of customer), and write it back out to a file.
    Merge the two files into a third using std::merge().

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>

using namespace std;


// error() simply disguises throws:
[[noreturn]] inline  void error(const string& s)
{
    throw runtime_error(s);
}


void end_of_loop(istream& ist, char term, const string& message)
{
    if (ist.fail()) { // use term as terminator and/or separator
        ist.clear();
        char ch;
        if (ist>>ch && ch==term) return;  // all is fine
        error(message);
    }
}


class Purchase{
public:
    Purchase(string name ="", int price =0, int count =0)
        :product_name{name},unit_price{price},count_memebers{count}{}
    friend istream& operator>>(istream& is, Purchase& p);
    friend ostream& operator<<(ostream& out, const Purchase& p);
private:
    string product_name;
    int unit_price;
    int count_memebers;

};

istream& operator>>(istream& is, Purchase& p){
// read a Purchase  from is into p
// format: ( name unit_price count_member )

    char ch;
    if (is >> ch && ch!='(') {
        is.unget();
        is.clear(ios_base::failbit); // not a Purchase section
        return is;
    }
    char ch2;
    string name;
    int price;
    int count;

    is >> name >> price >> count >> ch2;         // get the data
    if (!is || ch2!=')')  error("bad reading Purchase section");

    p.product_name = name;
    p.unit_price = price;
    p.count_memebers = count;
    return is;
}
ostream& operator<<(ostream& out, const Purchase& p){
    out <<"(" << p.product_name << " "
              << p.unit_price   << " "
              << p.count_memebers  << ")";
    return out;
}

class Order{

public:
    Order(string name ="", string addr = ""):customer_name{name},address{addr}{}
    friend istream& operator>>(istream& is, Order& p);
    friend ostream& operator<<(ostream& out, const Order& p);

private:

    string customer_name;
    string address;
    int data;
    vector<Purchase> memebers;
};

istream& operator>>(istream& is, Order& p){
// read a client Order from is into o
// format: { client name address data }

    char ch;
    is >> ch;
    if (ch!='{') {
        is.unget();
        is.clear(ios_base::failbit); // not a Order section
        return is;
    }

    string Order_marker;
    string om;

    is >> Order_marker;
    if (!is || Order_marker!="client") error("bad start of client");

    string name, address;
    int data;

    is >> name >> address >> data;  // get the data
    p.customer_name = name;
    p.address = address;
    p.data = data;

    for (Purchase pur; is >> pur;) {
        p.memebers.push_back(pur);

    }

    end_of_loop(is,'}',"bad end of Order");

    return is;
}
ostream& operator<<(ostream& out, const Order& p){
    out <<"{" << p.customer_name << " "<< p.address   << " " << p.data  ;
    for(auto i:p.memebers) out  << i;
    out << "}\n";

    return out;
}

template<typename Iter>
void out(Iter first, Iter last){
    while (first!=last){
        cout << *first;
        ++first;
    }
}

int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

        const string fname{"orders.txt"};
        ifstream ifs{fname};

        if(!ifs) cerr << "Can't open " << fname << endl;

        vector<Order>vo;


        while(ifs){
            Order order; // get a fresh order
            if (!(ifs>>order)) break;
            vo.push_back(order);
        }

        out(vo.begin(),vo.end());





    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



