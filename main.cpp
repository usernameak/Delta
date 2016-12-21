#include <iostream>
#include <fstream>
#include <cstdint>
#include <sstream>
#include <vector>
#include <chrono>
#include "deltacompiler.h"
#include "deltainterpreter.h"

using namespace std;

/*static chrono::nanoseconds getCurrentTime() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(system_clock::now().time_since_epoch());
}*/

int main() {
	ifstream* code = new ifstream("test.delta", ios_base::in);
	ofstream*
    out = new ofstream("test.out", ios_base::out | ios_base::trunc | ios_base::binary);

    Compiler* cp = new Compiler;
	cp->compile(code, out);

	code->close();
	out->close();
	ifstream* bcin = new ifstream("test.out", ios_base::in | ios_base::binary);
	vector<int32_t>* bc = new vector<int32_t>;
	while(true) {
		int32_t b;
		bcin->read((char*)&b, 4);
		if(!bcin->good()) break;
		bc->push_back(b);
		//cout << b << endl;
	}
	/*//chrono::nanoseconds start = getCurrentTime();
	Interpreter* ip = new Interpreter;
	ip->interpret(bc);
	//chrono::nanoseconds finish = getCurrentTime();
	//cout << (finish-start).count() << endl;
	cout << ip->istack->top() << endl;*/
	return 0;
}
