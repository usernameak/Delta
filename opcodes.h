#ifndef OPCODES_H
#define OPCODES_H

#include <string>

enum OpCodes {
	OP_NONE = 0,
	OP_ADD,
	OP_PUSH,
	OP_SUB,
	OP_MUL,
	OP_DIV
};

OpCodes mapStringToOpcode(std::string);

#endif
