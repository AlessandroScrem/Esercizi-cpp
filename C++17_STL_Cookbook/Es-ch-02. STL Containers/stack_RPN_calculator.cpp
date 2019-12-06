/******************************************************************************

Implementing a simple RPN calculator with std::stack

The RPN is a notation thatÂ can be used to express mathematical expressions
in a way thatÂ is really simple to parse. In RPN, 1 + 2 is 1 2 +. Operands first, then the operation.
Another example: (1 + 2) * 3 would be 1 2 + 3 *

*******************************************************************************/

#include <iostream>
#include <stack>
#include <iterator>
#include <map>
#include <sstream>
#include <cassert>
#include <vector>
#include <stdexcept>
#include <cmath>

using namespace std;

template <typename IT>
double evaluate_rpn(IT it, IT end)      {
    // evaluate_rpn function accepts iterators,
    // it is very easy to feed it with different inputs than the standard input stream

     stack<double> val_stack; // memorize all operands

     // lambda helper function.
     // It modifies the stack by pulling the highest item from it and then returns that item
     auto pop_stack ([&](){
         auto r (val_stack.top());
         val_stack.pop();
         return r;
     });

     // define all the supported mathematical operations in a map.
     // The operations are represented by callable lambdas,
     // which take two operands, return the result
      map<string, double (*)(double, double)> ops {
          {"+", [](double a, double b) { return a + b; }},
          {"-", [](double a, double b) { return a - b; }},
          {"*", [](double a, double b) { return a * b; }},
          {"/", [](double a, double b) { return a / b; }},
          {"^", [](double a, double b) { return pow(a, b); }},
          {"%", [](double a, double b) { return fmod(a, b); }},
      };

      // iterate through the input. Assuming that the input iterators give us strings,
      // we feed a new std::stringstream per token, because it can parse numbers.
      for (; it != end; ++it) {
          stringstream ss {*it};

          if (double val; ss >> val) {  // we have an operand, which we push on the stack
              val_stack.push(val);
          }
           else {  // it must be something other than an operator; in that case, it can only be an operand
              const auto r {pop_stack()};
              const auto l {pop_stack()};

               try {  // The at call of the map will throw an out_of_range exception
                      // in case the user provides a mathematical operation we don't know of
                  const auto & op     (ops.at(*it)); // we get the operand dereferencing the iterator it
                  const double result {op(l, r)};    //the lambda object accepts operands l and r as parameter
                  val_stack.push(result);
              }
              // operation string was unknown to us
              catch (const out_of_range &) {
                  throw invalid_argument(*it);
              }
           }
      }
      return val_stack.top();
}

int main()
{
    // evaluate_rpn function accepts iterators,
    // it is very easy to feed it with different inputs than the standard input stream
    // cout << evaluate_rpn(istream_iterator<string>{cin}, {})  << '\n';
    // vector<string> v {"3", "2", "1", "+", "*", "2", "/"};
    // cout << evaluate_rpn(begin(v), end(v)) << '\n';
    try {
        stringstream s {"3 2 1 + * 2 /"};
        cout << evaluate_rpn(istream_iterator<string>{s}, {}) << '\n';
    }
    catch (const invalid_argument &e) {
        cout << "Invalid operator: " << e.what() << '\n';
    }

    return 0;
}

