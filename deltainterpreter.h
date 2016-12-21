#pragma once

#include <vector>
#include <cstdint>
#include <stack>


class Interpreter {
private:
	uint32_t ptr;
	std::vector<int32_t>* bytecode;
public:
	std::stack<int32_t>* istack;
	void addOp();
	void subOp();
	void mulOp();
	void divOp();
	void pushOp();
	void interpretOp();
	void interpret(std::vector<int32_t>*);
};
