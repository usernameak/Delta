#pragma once

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

enum dtoken {TOK_FAIL, TOK_FUNCTIONDECLARATION, TOK_IDENTIFIER, TOK_CHARACTER, TOK_NEWLINE};

struct functiondeclarationnode {
    string* name;
    string* rettype;
    vector<string> argtypes;
    vector<string> args;
    dtoken bodytype;
    void* body;
};

struct functioncallnode {};

class Compiler {
private:
    int32_t ptr;
    string code;
    bool isIdentifierStart(char);
    bool isIdentifierChar(char);
    bool isDigitChar(char);
    bool isWhitespaceChar(char);
    dtoken parsecode(void**, int32_t);
    dtoken parsefunctiondeclaration(functiondeclarationnode*, int32_t);
    dtoken parsefunctioncall(functioncallnode**, int32_t);
    dtoken parsecharacter(char);
    dtoken parsenewline(int32_t, int32_t*);
    char getNext();
    char next();
    dtoken parseidentifier(string*);

public:
	void compile(istream*, ofstream*);
};
