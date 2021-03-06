#include "deltacompiler.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "opcodes.h"

bool Compiler::isIdentifierStart(char c) {
    if((c >= 'a' && c <= 'z') ||
       (c >= 'A' && c <= 'Z') ||
       (c == '_')) {
        return true;
    }
    return false;
}

bool Compiler::isIdentifierChar(char c) {
    if(isIdentifierStart(c) ||
       isDigitChar(c)) {
        return true;
    }
    return false;
}

bool Compiler::isDigitChar(char c) {
    if(c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

bool Compiler::isWhitespaceChar(char c) {
    if(c == ' ' || c == '\t') {
        return true;
    }
    return false;
}

char Compiler::getNext() {
    return code.at(ptr+1);
}

char Compiler::next() {
    return code.at(++ptr);
}

TokenType Compiler::parseidentifier(string* lineret) {
    int32_t oldptr = ptr;
    string identifier;
    char c;
    try {
        while(true) {
            c = next();
            if(!isIdentifierStart(c)) {
                if(isWhitespaceChar(c)) {
                    continue;
                }
                ptr = oldptr;
                return TOK_FAIL;
            }
            identifier = c;
            break;
        }
    } catch(out_of_range err) {
        ptr = oldptr;
        return TOK_FAIL;
    }
    try {
        while(true) {
            c = getNext();
            if(!isIdentifierChar(c)) {
                *lineret = identifier;
                return TOK_IDENTIFIER;
            }
            identifier += c;
            ptr++;
        }

    } catch(out_of_range err) {
        *lineret = identifier;
        return TOK_IDENTIFIER;
    }
}

TokenType Compiler::parsecharacter(char ic) {
    int32_t oldptr = ptr;
    char c;
    while(true) {
        c = next();
        if(c != ic) {
            if(isWhitespaceChar(c)) {
                continue;
            }
            ptr = oldptr;
            return TOK_FAIL;
        }
        break;
    }
    return TOK_CHARACTER;
}

TokenType Compiler::parsenewline(int32_t indent, int32_t* setindent) {
    int32_t oldptr = ptr;
    char c;
    while(isWhitespaceChar(c = next())) {

    }
    if(c == '\n' || (c == '\r' && (c = next()) == '\n')) {
        if(setindent != 0) {

            int32_t rindent = 0;
            while(isWhitespaceChar(c = getNext())) {
                rindent++;
                ptr++;
            }
            if(rindent > indent) {
                *setindent = rindent;
                return TOK_NEWLINE;
            }
        } else {
            int32_t rindent = 0;
            while(isWhitespaceChar(c = getNext())) {
                rindent++;
                ptr++;
            }
            if(rindent == indent) {
                return TOK_NEWLINE;
            }
        }
    }
    ptr = oldptr;
    return TOK_FAIL;
}

TokenType Compiler::parsefunctiondeclaration(FunctionDeclaration*& noderet, int32_t indent) {

    int32_t oldptr = ptr;
    FunctionDeclaration* node = new FunctionDeclaration;
    string* rettypename = new string;
    string* funcname = new string;
    if(parseidentifier(rettypename) != TOK_FAIL) {
        cout << *rettypename << endl;
        node->rettype = rettypename;
        if(parseidentifier(funcname) != TOK_FAIL) {
            cout << *funcname << endl;
            node->name = funcname;
            if(parsecharacter('(') == TOK_FAIL) {
                ptr = oldptr;
                return TOK_FAIL;
            }

            string* argtypename = new string;
            string* argname = new string;

            do {
                if(parseidentifier(argtypename) == TOK_FAIL) {
                    break;
                }
                if(parseidentifier(argname) == TOK_FAIL) {
                    ptr = oldptr;
                    return TOK_FAIL;
                }
                cout << *argtypename << endl;
                cout << *argname << endl;
            } while (parsecharacter(',') != TOK_FAIL);

            if(parsecharacter(')') == TOK_FAIL) {
                ptr = oldptr;
                return TOK_FAIL;
            }

            int* cindent = new int(0);

            if(parsenewline(indent, cindent) == TOK_FAIL) {
                ptr = oldptr;

                return TOK_FAIL;
            }
            cout << *cindent << endl;

            Node* bodynode;

            parsecode(bodynode, *cindent);

            noderet = node;

            return TOK_FUNCTIONDECLARATION;
        }
    }
    ptr = oldptr;
    return TOK_FAIL;
}

TokenType Compiler::parsefunctioncall(FunctionCall*& noderet, int32_t indent) {
    return TOK_FAIL;
}

TokenType Compiler::parsecode(Node*& noderet, int32_t indent) {
    Node* node;
    TokenType lt;
    if((lt = parsefunctiondeclaration((FunctionDeclaration*&)node, indent)) != TOK_FAIL) {
        noderet = node;
        return lt;
    } else if((lt = parsefunctioncall((FunctionCall*&)node, indent)) != TOK_FAIL) {
        noderet = node;
        return lt;
    } else return TOK_FAIL;
}

void Compiler::compile(std::istream* codestream, std::ofstream* out) {
	using namespace std;

    ptr = -1;
    code.assign(std::istreambuf_iterator<char>(*codestream), std::istreambuf_iterator<char>());

    Node* id;
    TokenType lt;
    if((lt = parsecode(id, 0)) != TOK_FAIL) {
        cout << *(((FunctionDeclaration*)id)->name) << endl;
    }

    /*for(std::vector<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it) {
        Token tok = *it;
        cout << "type: " << tok.type << endl;
        cout << "strval: " << tok.strval << endl;
        cout << "intval: " << tok.intval << endl;
        cout << "-----" << endl;
    }*/
}
