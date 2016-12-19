#include "opcodes.h"

#include <string>

OpCodes mapStringToOpcode(std::string str) {
	if(!str.compare("add")) {
		return OP_ADD;
	} else if(!str.compare("push")) {
		return OP_PUSH;
	} else if(!str.compare("sub")) {
		return OP_SUB;
	} else if(!str.compare("mul")) {
		return OP_MUL;
	} else if(!str.compare("div")) {
		return OP_DIV;
	}
	return OP_NONE;
}
