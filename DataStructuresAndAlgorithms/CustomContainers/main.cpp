#include <iostream>
#include "vector.h"
int main() {
	Vector<const char*>* test = &(Vector<const char*>());
	test->push_back("alpha");
	test->clear();
	test->empty();
	test->pop_back();
	test->reserve(7);
	test->resize(77);
	test->size();
	test->capacity();
	test->push_back("alpha");
	std::cout << test->at(77);
	return 0;
}