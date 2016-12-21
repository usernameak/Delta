#ifndef DELTACOMPILER_H
#define DELTACOMPILER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*enum TokenType {TOK_NONE, TOK_CAP, TOK_CAPARG, TOK_CAPASSIGN};// TOK_IDENTIFIER, TOK_STRING, TOK_OPENPAREN, TOK_CLOSEPAREN, TOK_INT};

enum TokenState {TS_NONE, TS_CAPSTART, TS_CAPCHAR, TS_CAPARGS, TS_CAPATOMS};

struct Token {
    TokenType type;
    string strval;
    int32_t intval = 0;
};*/

enum linetype {LT_FAIL, LT_FUNCTIONDECLARATION, LT_IDENTIFIER, LT_CHARACTER, LT_NEWLINE};

struct functiondeclarationnode {
    string name;
    string rettype;
    vector<string> argtypes;
    vector<string> args;
    linetype bodytype;
    void* body;
};

class Compiler {
private:
    int32_t ptr;
    string code;
    bool isIdentifierStart(char);
    bool isIdentifierChar(char);
    bool isDigitChar(char);
    bool isWhitespaceChar(char);
    linetype parsecode(void*);
    linetype parsefunctiondeclaration(functiondeclarationnode*, int32_t);
    linetype parsecharacter(char);
    linetype parsenewline(int32_t, int32_t*);
    char getNext();
    char next();
    linetype parseidentifier(string*);

public:
	void compile(istream*, ofstream*);
};

#endif
