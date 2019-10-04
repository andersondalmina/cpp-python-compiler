#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>

#include "./token.cpp"
#include "./token_list.cpp"

using namespace std;

void readFile(istream& file);
void getNextChar();
void getToken();
void dumpTokenList();
void scanIndentation();
int scanIdentifier(string);
int scanKeyword(string);
int scanLiteral(string);
int scanOperator(string);
int scanDelimiter(string);

// lineText is a line read from file
std::string lineText;

// lastChar is the last char read from de line
char lastChar;

// line and columns read
int line = 0;
int column = 0;

// currentState is the current state of the analysis
enum states { initialState, indentationState, stringState, numberState, keywordState, operatorDelimiterState, commentState } currentState;

// tokenType is the type of the current token
int tokenType;

// TokenList is a list with all tokens recognized
vector<Token> tokenList;

// indentStack is the stack to control indentation
stack<int> indentStack;
