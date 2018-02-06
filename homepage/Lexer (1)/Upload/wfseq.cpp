// ============================================================================ 
// wfseq.cpp : 
// ~~~~~~~~~
// - testing whether an input line contains a well-formed sequence of 
// delimiters (){}[].
#include <iostream>
#include <stack>
#include "Lexer.h"
using namespace std; // bad practice

// illustrate the use of global constants
const string open_delims("([{");
const string close_delims(")]}");

int main() {
    Lexer lexer; Token tok; string line; size_t p;
    stack<Token> mystack;
    while (cin) {
        cout << "> " << flush;
        getline(cin, line);
        lexer.set_input(line);
        while (lexer.has_more_token()) {
            if ( (tok = lexer.next_token()).type != DELIM ) continue;
            
            if (open_delims.find(tok.value) != string::npos) { 
                // tok is open delim
                mystack.push(tok);
                continue;
            }

            p = close_delims.find(tok.value); // 0, 1, 2, or string::npos
            if (p != string::npos) {          // tok is a close delim
                if (mystack.empty() || 
                    open_delims.find(mystack.top().value) != p) {
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
        } else {
            cout << "Well-formed!\n";
        }
    }
    return 0;
}
