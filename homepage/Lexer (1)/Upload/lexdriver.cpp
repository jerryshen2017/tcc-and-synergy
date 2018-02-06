// lexdriver.cpp : a simple driver for the the Lexer class
#include <iostream>
#include <vector>
#include "Lexer.h"
using namespace std;

int main() {
    Lexer lexer;
    Token tok; string line;
    while (cin) {
        cout << "> ";
        getline(cin, line);
        lexer.set_input(line);
        vector<Token> my_tok_vec = lexer.tokenize();
        cout << "There are " << my_tok_vec.size() << " tokens. They are: \n";        
        lexer.restart();
        while (lexer.has_more_token()) {
            tok = lexer.next_token();
            switch (tok.type) {
                case IDENT:    cout << "IDENT:   " << tok.value << endl; break;
                case DELIM:    cout << "DELIM:   " << tok.value << endl; break;
                case OPERATOR: cout << "OPERATOR:" << tok.value << endl; break;
                case COMMENT:  cout << "COMMENT: " << tok.value << endl; break;
                case NUMBER:   cout << "NUMBER:  " << tok.value << endl; break;
                case STRING:   cout << "STRING:  " << tok.value << endl; break;
                case ENDTOK:   cout << "EOF:     " << endl; break;
                case ERRTOK:   cout << "[ ERROR ]" << endl; break;
            }
        }
    }
    return 0;
}
