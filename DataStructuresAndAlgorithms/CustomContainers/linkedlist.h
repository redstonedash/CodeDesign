#pragma once
#include <iostream>
template <typename T>
struct node {
	node(T data) {
		this->data = data;
	}
	node<T>* next = NULL;
	T data;
};

template <typename T>
class linkedItterator;

template <typename T>
class linkedList {
public:
	linkedList(){
		start = NULL;
		end = NULL;
	}
	~linkedList() {
		if (start) {
			node<T>* n = start;
			while (n->next) {
				node<T>* temp = n;
				n = n->next;
				delete temp;
			}
		}
	}
	node<T>* start;
	node<T>* end;
	void push_front(const T& data) {

	}
	void pop_front() {

	}
	void insert(linkedItterator<T> *i, T data) {
		if (i->list != this) {
			throw "attempted to use foreign itterator";
		}
		node<T>* n = new node<T>(data);
		if (start) {
			if (i->current->next) {
				n->next = i->current->next;
			}
			i->current->next = n;
		} else {
			start = n;
			end = n;
			i->current = start;
			std::cout << i->current;
		}
	}
};


template <typename T>
class linkedItterator {
	node<T>* current;
public:
	friend class linkedList<T>;
	linkedList<T>* list;
	linkedItterator(linkedList<T>* l) {
		list = l;
		current = l->start;
	}
	void Start() {
		current = list->start;
	}
	void End() {
		current = list->end;
	}
	linkedList<T>* getList() {
		return list;
	}
	void Forward() {
		if (!current->next) {
			throw "Attempted to access a null index";
		}
		current = current.next;
	}
	T& operator*() {
		return current->data;
	}
	void operator++() {
		Forward();
	}
	bool operator==(linkedItterator<T> i) {
		return i.current == current; 
	}
	bool operator!=(linkedItterator<T> i) {
		return i.current != current;
	}
};