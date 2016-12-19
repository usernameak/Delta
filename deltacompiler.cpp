#include "deltacompiler.h"

#include <cstdint>
#include <iostream>
#include <string>
#include <sstream>
#include <deque>
#include <fstream>
#include <vector>
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

void Compiler::compile(std::istream* code, std::ofstream* out) {
	using namespace std;
	//string line;
	//istringstream* linestream;

	/*while(getline(*code, line)) {
		string* oppart = new string;
		deque<string*>* opparts = new deque<string*>;
		linestream = new istringstream(line);
		char c;
		while(linestream->get(c)) {
			if(c != ' ') {
				*oppart += c;
				//cout << *oppart << endl;
			} else if(oppart->compare("") != 0) {
				opparts->push_back(oppart);
				oppart = new string;
			}

		}
		if(oppart->compare("") != 0) {
			opparts->push_back(oppart);
			oppart = new string;
		}

		if(!opparts->empty()) {
			int32_t oc = mapStringToOpcode(*opparts->front());
			out->write((char*)&oc, 4);
			opparts->pop_front();
			while(!opparts->empty()) {
				oc = stoi(*opparts->front());
				out->write((char*)&oc, 4);
				opparts->pop_front();
			}
		}
	}*/
	char c;
    TokenType curtok = TOK_NONE;
    string curtokidentifier;
    string curtokstring;
    string curtoknumber;
    vector<Token>* tokens = new vector<Token>;
    while(code->get(c)) {
        if(curtok == TOK_IDENTIFIER && isIdentifierChar(c)) {
            curtokidentifier += c;
        } else if(curtok == TOK_INT && isDigitChar(c)) {
            curtoknumber += c;
        } else {
            if(curtok == TOK_IDENTIFIER) {
                Token idtok;
                idtok.type = TOK_IDENTIFIER;
                idtok.strval = curtokidentifier;
                tokens->push_back(idtok);
                curtok = TOK_NONE;
            } else if(curtok == TOK_INT) {
                Token numtok;
                numtok.type = TOK_INT;
                numtok.intval = stoi(curtoknumber);
                tokens->push_back(numtok);
                curtok = TOK_NONE;
            }
            if(curtok == TOK_STRING) {
                if(c == '"') {
                    Token strtok;
                    strtok.type = TOK_STRING;
                    strtok.strval = curtokstring;
                    tokens->push_back(strtok);
                    curtok = TOK_NONE;
                } else {
                    curtokstring += c;
                }
            } else if(isDigitChar(c)) {
                curtok = TOK_INT;
                curtoknumber = c;
            } else if(c == '"') {
                curtok = TOK_STRING;
                curtokstring = "";
            } else if(c == '(') {
                Token optok;
                optok.type = TOK_OPENPAREN;
                tokens->push_back(optok);
            } else if(c == ')') {
                Token cptok;
                cptok.type = TOK_CLOSEPAREN;
                tokens->push_back(cptok);
            } else if(isIdentifierStart(c)) {
                curtok = TOK_IDENTIFIER;
                curtokidentifier = c;
            } else if(c != ' ' && c != '\t' && c != '\r' && c != '\n') {
                cout << "Parse error: unknown character '" << c << "'" << endl;
            }
        }
    }
    char zeroint[1] = {0};
    for(std::vector<Token>::iterator it = tokens->begin(); it != tokens->end(); ++it) {
        Token tok = *it;
        out->write(tok.strval.c_str(), sizeof(char)*tok.strval.size());
        *out << (uint8_t)0;
        //*out << (char*)&tok;
    }
}
