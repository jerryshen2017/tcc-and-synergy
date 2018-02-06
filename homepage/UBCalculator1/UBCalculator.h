// ============================================================================ 
// Calculator.h
// ~~~~~~~
// author    : Tamal T. Biswas
// - a simple calculator class
// - The class can evaluate any infix expression. 
// ============================================================================ 

#ifndef _UBCALCULATOR_H_
#define _UBCALCULATOR_H_

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include "Lexer.h"
#include "error_handling.h"
using namespace std;


/**
 * -----------------------------------------------------------------------------
 * the Calculator class:
 * - take a string to be scanned
 * - scan for tokens and return one at a time
 * -----------------------------------------------------------------------------
 */
class UBCalculator {
public:
	// constructor
	UBCalculator(){
		precedenceMap = createPrecedenceMap();
	};
	//This is the code that I added.
	std::string convert(const std::string& expression);


	bool well_formed (string s);    // edited 07/05/2016.

	// a couple of modifiers
	void setLine(std::string);
private:

   //This is the code that I added.
	void process_operator(char op);

	// This is the code that I added.
	bool is_operator(char ch) const
	{
		return OPERATORS.find(ch) != std::string::npos;
	}

	int precedence(char op)
	{
		return precedenceMap[op];
	}

	float calculate(float operand1, float operand2, char op);

	static std::map<char, char> createDelimMatch()
	{
		std::map<char, char> m;
		m[')'] = '(';
		m['}'] = '{';
		m[']'] = '[';
		return m;
	}
	static std::map<char, int> createPrecedenceMap()
	{
		std::map<char, int> m;
		m['+'] = 0;
		m['-'] = 0;
		m['*'] = 1;
		m['/'] = 1;
		m['('] = -1;
		m['{'] = -1;
		m['['] = -1;

		return m;
	}

	static const std::string OPERATORS; // This is the code that I added.
	static const int PRECEDENCE[]; // This is the code that I added.

    std::stack<char> operator_stack;  // This is the code that I added.
	std::stack<float> value_stack;  // 07/05/2016

	static std::map<char, int> precedenceMap;
	const static std::map<char, char> delimMatch;
	const static std::string openDelims; 
	const static std::string closeDelims;
};

#endif
