#ifndef DELTACOMPILER_H
#define DELTACOMPILER_H

#include <iostream>
#include <string>

using namespace std;

enum TokenType {TOK_NONE, TOK_IDENTIFIER, TOK_STRING, TOK_OPENPAREN, TOK_CLOSEPAREN, TOK_INT};

struct Token {
    TokenType type;
    string strval;
    int32_t intval = 0;
};

class Compiler {
private:
    bool isIdentifierStart(char);
    bool isIdentifierChar(char);
    bool isDigitChar(char);
public:
	void compile(istream*, ofstream*);
};

#endif
