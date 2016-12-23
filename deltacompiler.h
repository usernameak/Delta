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

enum TokenType {TOK_FAIL, TOK_FUNCTIONDECLARATION, TOK_IDENTIFIER, TOK_CHARACTER, TOK_NEWLINE};

class Node {
    public:
    TokenType tokentype;
};

class FunctionDeclaration : Node {
    public:
    string* name;
    string* rettype;
    vector<string> argtypes;
    vector<string> args;
    TokenType bodytype;
    Node* body;
};

class FunctionCall : Node {

};

/*struct FunctionDeclaration {
    string* name;
    string* rettype;
    vector<string> argtypes;
    vector<string> args;
    TokenType bodytype;
    void* body;
};*/

//struct FunctionCall {};

class Compiler {
private:
    int32_t ptr;
    string code;
    bool isIdentifierStart(char);
    bool isIdentifierChar(char);
    bool isDigitChar(char);
    bool isWhitespaceChar(char);
    TokenType parsecode(Node*&, int32_t);
    TokenType parsefunctiondeclaration(FunctionDeclaration*&, int32_t);
    TokenType parsefunctioncall(FunctionCall*&, int32_t);
    TokenType parsecharacter(char);
    TokenType parsenewline(int32_t, int32_t*);
    char getNext();
    char next();
    TokenType parseidentifier(string*);

public:
	void compile(istream*, ofstream*);
};
