#pragma once

#include "vector.h"

template <typename T>
class Stack
{
	Vector<T> vector;
public:
	Stack();
	Stack(size_t count, const T& value);

	void push(const T& value);
	T pop();
	T& back();
	size_t size() const;
};

template<typename T>
Stack<T>::Stack() {
}

template<typename T>
Stack<T>::Stack(size_t count, const T& value) {
	for (int i = 0; i < count; i++) {
		vector.pop_back(value);
	}
}
template<typename T>
void Stack<T>::push(const T& value) {
	vector.push_back(value);
}
template<typename T>
void Stack<T>::pop() {
	return vector.pop_back();
}
template<typename T>
T& Stack<T>::back() {
	vector.at(vector.size());
}
template<typename T>
size_t Stack<T>::size() const {
	return vector.size();
}