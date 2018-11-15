#include <iostream>
#include "vector.h"
#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
int main() {
	linkedList<const char*> l = linkedList<const char*>();
	linkedItterator<const char*> i = linkedItterator<const char*>(&l);
	l.insert(&i,"alpha");
	std::cout << *i;
	
	return 0;
}