#include "std_lib_facilities.h"

/*
    Simple Calculator

    Revision history:

    This is example code from Chapter 6.6.
    Originally written by Bjarne Stroustrup
    Revised by Alessandro Screm Sep 2019

 This program implement a simple calculator
 Input from cin output to cout.
 Input comes from cin through the Token_stream called ts.

The grammar for inpu parser is:

Calculation:
    Statements
    Print
    Print
    Quit
    Calculation Statement
Statement:
    Declaration
    Expression
Declaration:
    "let" name "=" Expression
Print:
    ;
Quit:
    q
Expression:
    Term
    Expression "+" Term
    Expression "-" Term
Term:
    Primary
    Term "*" Primary
    Term "/" Primary
    Term "%" Primary
Primary:
    Number
    "(" Expression ")"
    "{" Expression "}"
    "+" Primary
    "-" Primary
Number:
    floatimg-point-literal

*/

const char number = '8';      // we use '8' to represent a number
const char print  = ';';      // t.kind==print means that is a  a print Token
const char quit   = 'q';      // t.kind==quit means that is a  a quit Token
const char prompt = '>';
const char result = '=';      // used to indicate that what follow is the a result
const char name   = 'a';      // name token
const char let    = 'L';      // declaration token
const string declkey = "let"; // declaration keywork
const string exitkey = "exit";


//------------------------------------------------------------------------------

struct Variable {
    string name;
    double value;
    Variable(string n, double v) :name(n), value(v) { }
};

//------------------------------------------------------------------------------

static vector<Variable> var_table;

//------------------------------------------------------------------------------

double get_value(string s)
    //return the value of the Variable named s
{
    for (const Variable& v : var_table)
        if (v.name == s) return v.value;
    error("get: undefined name ",s);
    return 0;
}

//------------------------------------------------------------------------------

void set_value(string s, double d)
    //set value of the Variable named s to d
{
    for (Variable& v : var_table)
        if (v.name == s) {
            v.value = d;
            return;
        }
    error("set: undefined name ",s);
}

//------------------------------------------------------------------------------

bool is_declared(string s)
    //is var already in var_table?
{
    for (const Variable& v : var_table)
        if (v.name == s) return true;
    return false;
}

//------------------------------------------------------------------------------

double define_name(string var, double val)
    //add (var, val) to var_table
{
    if(is_declared(var))error(var, " declared twice");
    var_table.push_back(Variable(var,val));
    return val;
}


//------------------------------------------------------------------------------

struct Token {
    char kind;        // what kind of token
    double value;     // for numbers: a value
    string name;
    Token(char ch):kind{ch}{}    // initialize kind from char
    Token(char ch, double val) :kind{ch}, value(val) { } //initialize kind and value
    Token(char ch, string n) :kind{ch}, name{n} { }      //initialize kind and name
};


//------------------------------------------------------------------------------

class Token_stream
{
public:
    Token_stream():full(false), buffer(0) { }
    Token get();                                    //get a Token
    void putback(Token t){ buffer=t; full=true; }   //put a Token back
    void ignore(char c);        //discard characters up and including a c

private:
    bool  full;     //is there a Token in the buffer?
    Token buffer;   //here is where we keep a Token put back using putback()
};

//------------------------------------------------------------------------------

Token Token_stream::get()
    // read character fron cin and compose a Token ready
{
    if (full) {  //check if we have a token ready
        full=false;
        return buffer;
    }
    char ch;
    cin >> ch;  // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
    case '(':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case ';':
    case '=':
        return Token(ch);   // let each character represent itself
    case '.':               // a floating-point-literal can start with a dot
    case '0':               //number literal
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {	cin.putback(ch);    // put digit back into the input stream
        double val;
        cin >> val;
        return Token(number,val);
    }
    default:
        //if (isspace(ch)) return Token (print); // cin skip space and newline
        if (isalpha(ch)) {
            string s;
            s += ch;
            while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch;
            cin.putback(ch);
            if (s == declkey) return Token(let);	//declaration keyword
            if (s == exitkey) return Token(quit);       //exit
            return Token(name,s);
        }
        error("Bad token");
        return Token(' ');
    }
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
    // ignore all cin input until get the char c
    // c represent the kind of token
{
    //first look in buffer
    if (full && c==buffer.kind) {
        full = false;
        return;
    }
    full = false;

    //now search input
    char ch;
    while (cin>>ch)
        if (ch==c) return;
}

//------------------------------------------------------------------------------


double expression(Token_stream &ts);

//------------------------------------------------------------------------------

double primary(Token_stream &ts)
    // deal with numbers and parentheses
    // read and evaluate a Primary
{
    Token t = ts.get();
    switch (t.kind) {
    case '(':                       // handle '(' expression ')'
    {	double d = expression(ts);
        t = ts.get();
        if (t.kind != ')') error("'(' expected");
        return d;
    }
    case '-':
        return - primary(ts);
    case number:
        return t.value;             // return the number's value
    case name:
        return get_value(t.name);   // return the variable's value
    default:
        error("primary expected");
        return 0;
    }
}

//------------------------------------------------------------------------------

double term(Token_stream &ts)
    // deal with *, /, and %
{
    double left = primary(ts);

    while(true) {
        Token t = ts.get(); // get the next token
        switch (t.kind) {
        case '*':
            left *= primary(ts);
            break;
        case '/':
        {	double d = primary(ts);
            if (d == 0) error("divide by zero");
            left /= d;
            break;
        }
        case '%':
        {
            double d = primary(ts);
            if (d == 0) error("divide by zero");
            left = fmod(left, d);
            break;
        }
        default:
            ts.putback(t);  // put t back into the stream
            return left;
        }
    }
}

//------------------------------------------------------------------------------

double expression(Token_stream &ts)
    // deal with + and -
    // call term()
{
    double left = term(ts);    // read and evaluate a Term
    while(true) {
        Token t = ts.get();  // get the next token
        switch(t.kind) {
        case '+':
            left += term(ts);  // evaluate Term and add
            break;
        case '-':
            left -= term(ts);  // evaluate Term and subtract
            break;
        default:
            ts.putback(t);   // put t back into the stream
            return left;     // finally: no more + or - : return the answer
        }
    }
}

//------------------------------------------------------------------------------

double declaration(Token_stream &ts)
    //assume we have seen "let"
    //handle name = expression
    //declare a variable called "name" with the initial value "expression"
{
    Token t = ts.get();     // get the next token
    if (t.kind != name) error ("name expected in declaration");
    string name = t.name;
    if (is_declared(name)) error(name, " declared twice");

    Token t2 = ts.get();    // get the next token
    if (t2.kind != '=') error("= missing in declaration of " ,name);

    double d = expression(ts);
    var_table.push_back(Variable(name,d));
    return d;
}

//------------------------------------------------------------------------------

double statement(Token_stream &ts)
    //evaluate if there is a declaretion
    //otherwise call expression()
{
    Token t = ts.get();         // get the next token
    switch(t.kind) {
    case let:
        return declaration(ts);   // evaluate Term and add
    default:
        ts.putback(t);          // put t back into the stream
        return expression(ts);
    }
}

//------------------------------------------------------------------------------

void clean_up_mess(Token_stream &ts)
    //discard all token until get print command
{
    ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate()
    // handle print , quit commands
    // call statement()
{
    Token_stream ts;

    while(true)
    try {
        cout << prompt;
        Token t = ts.get();
        while (t.kind == print) t=ts.get(); //first discard all "prints"
        if (t.kind == quit) return;
        ts.putback(t);
        cout << result << statement(ts) << endl;
    }
    catch(runtime_error& e) {
        cerr << e.what() << endl;           //write error message
        clean_up_mess(ts);
    }
}

//------------------------------------------------------------------------------

int main()
{

    try {
        calculate();
        return 0;
    }
    catch (exception& e) {
        cerr << "exception: " << e.what() << endl;
        char c;
        while (cin >>c&& c!=';') ;
        return 1;
    }
    catch (...) {
        cerr << "exception\n";
        char c;
        while (cin>>c && c!=';');
        return 2;
    }
}
