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
       (c >= '0' && c <= '9')) {
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

linetype Compiler::parseidentifier(string* lineret) {
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
                return LT_FAIL;
            }
            identifier = c;
            break;
        }
    } catch(out_of_range err) {
        ptr = oldptr;
        return LT_FAIL;
    }
    try {
        while(true) {
            c = getNext();
            if(!isIdentifierChar(c)) {
                *lineret = identifier;
                return LT_IDENTIFIER;
            }
            identifier += c;
            ptr++;
        }

    } catch(out_of_range err) {
        *lineret = identifier;
        return LT_IDENTIFIER;
    }
}

linetype Compiler::parsecharacter(char ic) {
    int32_t oldptr = ptr;
    char c;
    while(true) {
        c = next();
        if(c != ic) {
            if(isWhitespaceChar(c)) {
                continue;
            }
            ptr = oldptr;
            return LT_FAIL;
        }
        break;
    }
    return LT_CHARACTER;
}

linetype Compiler::parsenewline(int32_t indent, int32_t* setindent) {
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
                return LT_NEWLINE;
            }
        } else {
            int32_t rindent = 0;
            while(isWhitespaceChar(c = getNext())) {
                rindent++;
                ptr++;
            }
            if(rindent == indent) {
                return LT_NEWLINE;
            }
        }
    }
    ptr = oldptr;
    return LT_FAIL;
}

linetype Compiler::parsefunctiondeclaration(functiondeclarationnode* lineret, int32_t indent) {
    int32_t oldptr = ptr;
    string* rettypename = new string;
    string* funcname = new string;
    char c;
    if(Compiler::parseidentifier(rettypename) != LT_FAIL) {
        cout << *rettypename << endl;
        if(Compiler::parseidentifier(funcname) != LT_FAIL) {
            cout << *funcname << endl;

            if(parsecharacter('(') == LT_FAIL) {
                ptr = oldptr;
                return LT_FAIL;
            }

            string* argtypename = new string;
            string* argname = new string;

            while(true) {
                if(Compiler::parseidentifier(argtypename) == LT_FAIL) {
                    break;
                }
                if(Compiler::parseidentifier(argname) == LT_FAIL) {
                    ptr = oldptr;
                    return LT_FAIL;
                }
                cout << *argtypename << endl;
                cout << *argname << endl;
            }

            if(parsecharacter(')') == LT_FAIL) {
                ptr = oldptr;
                return LT_FAIL;
            }

            int* cindent;
            *cindent = 0;

            if(parsenewline(indent, cindent) == LT_FAIL) {
                ptr = oldptr;

                return LT_FAIL;
            }
            cout << *cindent << endl;
            return LT_FUNCTIONDECLARATION;
        }
    }
    ptr = oldptr;
    return LT_FAIL;
}

linetype Compiler::parsecode(void* lineret) {
    void* line;
    linetype lt;
    if((lt = parsefunctiondeclaration((functiondeclarationnode*)line, 0)) != LT_FAIL) {
        lineret = line;
        return lt;
    } else return LT_FAIL;
}

void Compiler::compile(std::istream* codestream, std::ofstream* out) {
	using namespace std;

    ptr = -1;
    code.assign(std::istreambuf_iterator<char>(*codestream), std::istreambuf_iterator<char>());

    void* id;
    linetype lt;
    if((lt = parsecode(id)) != LT_FAIL) {
        cout << "OK" << endl;
    }

    /*for(std::vector<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it) {
        Token tok = *it;
        cout << "type: " << tok.type << endl;
        cout << "strval: " << tok.strval << endl;
        cout << "intval: " << tok.intval << endl;
        cout << "-----" << endl;
    }*/
}
