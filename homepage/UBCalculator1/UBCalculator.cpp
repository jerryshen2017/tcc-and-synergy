#include "UBCalculator.h"
#include <sstream>
#include <cctype>
#include <string>
#include "error_handling.h"
using namespace std;

using std::string; // This is the part that I added.
using std::istringstream;  // This is also the part that I added.



const std::map<char, char> UBCalculator::delimMatch = UBCalculator::createDelimMatch();
std::map<char, int> UBCalculator::precedenceMap = UBCalculator::createPrecedenceMap();
const std::string UBCalculator::openDelims = "([{";
const std::string UBCalculator::closeDelims = ")]}";

const string UBCalculator::OPERATORS = "+-*/";  // This is the code that I added.
const int UBCalculator::PRECEDENCE[] = { 1, 1, 2, 2 };  // This is the code that I added.


// Evaluate str
void UBCalculator::setLine(std::string str)
{
   if(well_formed(str))
      convert(str);      //edited 07/05/2016
}

bool UBCalculator::well_formed(string line) {
   Lexer lexer; Token tok;  size_t p;
   stack<Token> mystack;
   lexer.set_input(line);
   while (lexer.has_more_token()) {
      if ( (tok = lexer.next_token()).type != DELIM ) continue;

      if (openDelims.find(tok.value) != string::npos) {
         // tok is open delim
         mystack.push(tok);
         continue;
      }

      p = closeDelims.find(tok.value); // 0, 1, 2, or string::npos
      if (p != string::npos) {          // tok is a close delim
         if (mystack.empty() ||
             openDelims.find(mystack.top().value) != p) {
            mystack.push(tok); // make sure it's not empty
            break;
         } else {
            mystack.pop();
         }
      }
   } // end while(lexer.has_more_token())

   if (!mystack.empty()) {
      cout << "You drunk?\n";
      while (!mystack.empty()) mystack.pop();
      return false;
   } else {
      cout << "Well-formed!\n";
      return true;
   }
}

float UBCalculator::calculate(float operand1, float operand2, char op)
{
   switch(op)
   {
      case '+':
         return operand1 + operand2;
      break;
      case '-':
         return operand1 - operand2;
      break;
      case '*':
         return operand1 * operand2;
           break;
      case '/':
         if(operand2 == 0.0)
         {
            cout << "Can't divide by 0\n";
            return 0;
         }
         return operand1 / operand2;
           break;
   }
   return 0.0;
}

// This is the part of code that I added.
string UBCalculator::convert(const string& expression) {
   Lexer lexer; Token tok;  size_t p;
   lexer.set_input(expression);
   vector<Token> tokens = lexer.tokenize();     //edited on 07/05/2016.
   // make sure that we push the numbers inside the value stack.

   //float x = 0;   // This foat value gets intiliazed on the top.


   for(unsigned i=0;i<tokens.size(); ++i)      //edited on 07/05/2016
   {
      tok = tokens[i];
      if(tok.type == DELIM && tok.value[0] == '(') {
         operator_stack.push(tok.value[0]);
      }
      else if (tok.type == DELIM && tok.value[0] == ')') {
         while( ! operator_stack.empty() ) { //1.2.5.1 first condition

            char nextOp = tok.value[0];
            char stackOp = operator_stack.top();
            operator_stack.pop();//1.2.5.1.1
            if (stackOp != '(') { //1.2.5.1 second condition
               float val2 = value_stack.top();
               value_stack.pop(); //1.2.5.1.2
               float val1 = value_stack.top();
               value_stack.pop(); //1.2.5.1.2
               float result = calculate(val1, val2, stackOp); //1.2.5.1.3
               value_stack.push(result); //1.2.5.1.4

            }
            else {
               break;
            }
         }

      }
      else if (tok.type == OPERATOR)
      {
         while( ! operator_stack.empty() ) { //1.2.5.1 first condition

            char nextOp = tok.value[0];
            char stackOp = operator_stack.top();
            int nextOpPrecedence = precedence(nextOp);
            int stackOpPrecedence = precedence(stackOp);
            if (stackOpPrecedence >= nextOpPrecedence) { //1.2.5.1 second condition
               operator_stack.pop();//1.2.5.1.1
               float val2 = value_stack.top();
               value_stack.pop(); //1.2.5.1.2
               float val1 = value_stack.top();
               value_stack.pop(); //1.2.5.1.2
               float result = calculate(val1, val2, stackOp); //1.2.5.1.3
               value_stack.push(result); //1.2.5.1.4

            }
            else {
               break;
            }
         }
         operator_stack.push(tok.value[0]); //1.2.5.2
      }else if(tok.type == NUMBER) {
         value_stack.push(atof(tok.value.c_str()));

         // and I am not sure why this doesn't work.
      //}else if((tokens[i] == "("&& tokens[i+2] == ')') || ( tok == '[' && tok == ']') || ( tok == '{' && tok == '}') ) {
      //    value_stack.push_back(tokens[i+1]);
      }

   }

   // now we use a for loop to loop through the stacks.
   while( ! operator_stack.empty() ) {
          float val2 = value_stack.top();
          value_stack.pop();
          float val1 = value_stack.top();
          value_stack.pop();
          float result = calculate(val1,val2,operator_stack.top());
          value_stack.push(result);

          operator_stack.pop();

   }
   cout<<"The answer is: " << value_stack.top() << endl;
   return "";
   //postfix = " ";
   /*
   while (!operator_stack.empty())
      operator_stack.pop();
   istringstream infix_tokens(expression);
   string next_token;
   while(infix_tokens >> next_token) {
      if (isalnum(next_token[0])) {
        // postfix += next_token;
        // postfix += " ";
      } else if (is_operator(next_token[0])) {
         process_operator(next_token[0]);
      } else {
         //throw ("Unexpected Character Encountered"); This is part of the code that I actually comment out.
         cout << "Unexpected character encountered " << endl;

      }
   }
   while (!operator_stack.empty()) {
      char op = operator_stack.top();
      operator_stack.pop();
      postfix += op; postfix += " ";
   }
   return postfix;
    */
}

//This is the part where I added.
/*
void UBCalculator::process_operator(char op) {
   if (operator_stack.empty()) { operator_stack.push(op); }
   else { if (precedence(op) > precedence(operator_stack.top())) { operator_stack.push(op);
      } else {
         while (!operator_stack.empty() && (precedence(op) <= precedence(operator_stack.top()))) {
            postfix += operator_stack.top();
         } postfix += " "; operator_stack.pop();
      }
      operator_stack.push(op);
   }
}
*/

