#include "deltainterpreter.h"

#include <vector>
#include <cstdint>
#include <stack>
#include "opcodes.h"

using namespace std;

void Interpreter::addOp() {
	int32_t a = istack->top();
	istack->pop();
	int32_t b = istack->top();
	istack->pop();
	istack->push(b+a);
}

void Interpreter::subOp() {
	int32_t a = istack->top();
	istack->pop();
	int32_t b = istack->top();
	istack->pop();
	istack->push(b-a);
}
void Interpreter::mulOp() {
	int32_t a = istack->top();
	istack->pop();
	int32_t b = istack->top();
	istack->pop();
	istack->push(b*a);

}
void Interpreter::divOp() {
	int32_t a = istack->top();
	istack->pop();
	int32_t b = istack->top();
	istack->pop();
	istack->push(b/a);
}

void Interpreter::pushOp() {
	ptr++;
	int32_t val = bytecode->at(ptr);
	istack->push(val);
}

void Interpreter::interpretOp() {
	OpCodes opcode = (OpCodes)bytecode->at(ptr);
	switch(opcode) {
		case OP_ADD:
			addOp();
		break;
		case OP_SUB:
			subOp();
		break;
		case OP_MUL:
			mulOp();
		break;
		case OP_DIV:
			divOp();
		break;
		case OP_PUSH:
			pushOp();
		break;
	}
}

void Interpreter::interpret(std::vector<int32_t>* bc) {
	ptr = 0;
	bytecode = bc;
	istack = new stack<int32_t>;
	while(ptr < bytecode->size()) {
		interpretOp();
		ptr++;
	}
}
