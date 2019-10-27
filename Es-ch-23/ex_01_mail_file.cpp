/******************************************************************************
Ch 23:
 1. Get the email file example to run; test it using a larger file of your own creation.
    Be sure to include messages that are likely to trigger errors,
    such as messages with two address lines,
    several messages with the same address and/or same subject,
    and empty messages.
    Also test the program with something that simply isn’t a message
    according to that program’s specification,
    such as a large file containing no –––– lines.
*******************************************************************************/

#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include<map>

using namespace std;

// error() simply disguises throws:
[[noreturn]] inline  void error(const string& s)
{
    throw runtime_error(s);
}

typedef vector<string>::const_iterator Line_iter;

class Message {   // a Message points to the first and the last lines of a message
    Line_iter first;
    Line_iter last;
public:
    Message(Line_iter p1, Line_iter p2) :first{p1}, last{p2} { }
    Line_iter begin() const { return first;}
    Line_iter end() const { return last;}
    // . . .
};

using Mess_iter = vector<Message>::const_iterator;

struct Mail_file {      // a Mail_file holds all the lines from a file
                            // and simplifies access to messages
    string name;            // file name
    vector<string> lines;   // the lines in order
    vector<Message> m;      // Messages in order

    Mail_file(const string& n);     // read file n into lines

    Mess_iter begin() const { return m.begin(); }
    Mess_iter end() const { return m.end(); }
};

Mail_file::Mail_file(const string& n)
// open file named n
// read the lines from n into lines
// find the messages in the lines and compose them in m
// for simplicity assume every message is ended by a –––– line
{
    ifstream in {n};                 // open the file
    if (!in) {
       cerr << "no " << n << '\n';
       exit(1);                    // terminate the program
    }

    for (string s; getline(in,s); )  // build the vector of lines
          lines.push_back(s);

    auto first = lines.begin();      // build the vector of Messages
        for (auto p = lines.begin(); p!=lines.end(); ++p) {
            if (*p == "––––") {               // end of message
                m.push_back(Message(first,p));
                first = p+1;                 // –––– not part of message
             }
        }
}

int is_prefix(const string& s, const string& p)
// is p the first part of s?
{
    int n = p.size();
    if (string(s,0,n)==p) return n;
    return 0;
}

bool find_from_addr(const Message* m, string& s)
// find the name of the sender in a Message;
// return true if found
// if found, place the sender’s name in s:
{
    for (const auto& x : *m)
        if (int n = is_prefix(x, "From: ")) {
            s = string(x,n);
            return true;
        }
    return false;
}

string find_subject(const Message* m)
// return the subject of the Message, if any, otherwise "":
{
    for (const auto& x : *m)
        if (int n = is_prefix(x, "Subject: "))
            return string(x,n);
    return "";
}


int main()
{
    setlocale(LC_ALL, "en_US.UTF-8");

try {

        Mail_file mfile {"my–mail–file-ex01.txt"};  // initialize mfile from a file

        // first gather messages from each sender together in a multimap:

        multimap<string, const Message*> sender;

        for (const auto& m : mfile) {
            string s;
            if (find_from_addr(&m,s))
                sender.insert(make_pair(s,&m));
        }

        // now iterate through the multimap
        // and extract the subjects of John Doe’s messages:
        auto pp = sender.equal_range("John Doe <jdoe@machine.example>");
        for(auto p = pp.first; p!=pp.second; ++p)
            cout << find_subject(p->second) << '\n';
            /*for (const auto& x : *p->second)
                cout << x << "\n";
            */
    }

    catch ( std::exception& e) {
         std::cerr << "exception: " << e.what() <<  std::endl;
    }
    catch (...) {
         std::cerr << "exception\n";
    }


}



