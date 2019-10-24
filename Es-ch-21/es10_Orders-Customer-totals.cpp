/******************************************************************************

Chapter 21:
10. Compute the total value of the orders in the two files from the previous exercise.
    The value of an individual Purchase is (of course) its unit_price*count.

*******************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip>

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
    double value(){return unit_price*count_memebers;}

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
    Order(string name ="", string addr = "",int d=0 )
        :customer_name{name},address{addr}, data{d}{}

    bool  operator<(const Order& o)const {return  customer_name< o.customer_name;}
    bool operator==(const Order& o){return customer_name== o.customer_name;}
    static bool cmp_by_address(const Order& a, const Order& b) {return a.address<b.address;}
    double value(){
        double result =0;
        for(auto o: memebers) result += o.value();
        return result;
    }
    void print_value(){cout << setw(12)<< left<< customer_name  << value() << endl;}

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

template<typename T>
void readf (vector<T>& cont , const string& fn){
// read file to cont  :
    ifstream ifs{fn};
    if(!ifs) cerr << "Can't open " << fn << endl;
    for (T o; ifs >> o;){
        cont.push_back(o);
        o = T();    // get a fresh order
    }
    ifs.close();
}

template<typename T>
void writef(const T& cont , const string& fn){
// write cont to file:
    ofstream ofs{fn};
    for  (auto o : cont)
        ofs << o;
    ofs.close();
}


void out_value(vector<Order>& orders){
    for (auto o: orders )
        o.print_value();
}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

        const string of1{"orders.txt"};
        vector<Order>vo;
        // read orders to vector

        readf(vo, of1);
//        out(vo.begin(),vo.end());
        // sort by customer name by default
        sort(vo.begin(),vo.end());

        const string of1sorted{"sorted_orders1.txt"};
        // write sorted by name to file
        writef(vo, of1sorted);

        const string of2{"orders2.txt"};
        vector<Order>vo2;

        // read orders2 to vector
        readf(vo2, of2);
//        out(vo2.begin(),vo2.end());


        // sort by address
        sort(vo2.begin(),vo2.end(),Order::cmp_by_address);
//        out(vo2.begin(),vo2.end());

        const string of2sorted{"sorted_orders2.txt"};
        // write sorted by address to file
        writef(vo2, of2sorted);

        // sort v2 by customer name
        sort(vo2.begin(),vo2.end());

        // create dest vector for merging into
        vector<Order>vo3(vo.size()+vo2.size());
        merge(vo.begin(),vo.end(),vo2.begin(),vo2.end(),vo3.begin());
//        out(vo3.begin(),vo3.end());

        // copy vector in a set to remove duplicates
        set<Order>unique{vo3.begin(),vo3.end()};
//        out(unique.begin(),unique.end());
//        cout << "size : " << unique.size() << endl;
        cout << "\n Orders of vo\n";
        out_value(vo);
        cout << "\n Orders of vo2\n";
        out_value(vo2);

        double total_value_v0 = 0;
        double total_value_vo2 = 0;
        for (auto o : vo) total_value_v0 += o.value();
        for (auto o : vo2) total_value_vo2 += o.value();
        cout << "Total value of Orders 1: " << total_value_v0 << endl;
        cout << "Total value of Orders 2: " << total_value_vo2 << endl;




    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



