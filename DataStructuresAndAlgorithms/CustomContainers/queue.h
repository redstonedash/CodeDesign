#pragma once

#include "vector.h"

template <typename T>
class Queue
{
	Vector<T> vector;
public:
	Queue();
	Queue(size_t count, const T& value);

	T push(const T& value);
	T pop();
	T& front();
	size_t size() const;
};

template<typename T>
Queue<T>::Queue() {
}

template<typename T>
Queue<T>::Queue(size_t count, const T& value) {
	for (int i = 0; i < count; i++) {
		vector.pop_back(value);
	}
}
template<typename T>
void Queue<T>::push(const T& value) {
	vector.push_back(value);
}
template<typename T>
T Queue<T>::pop() {
	if (vector.size() == 0) {
		Vector.clear();
		return vector[0];
	}
	T* temp = vector[0];
	for (int i = 0; i < vector.size() - 1; i++) {
		vector[i] = vector[i + 1];
		vector.resize(vector.size() - 1);
	}
	return *temp;
}
template<typename T>
T& Queue<T>::front() {
	vector.at(vector.size());
}
template<typename T>
size_t Queue<T>::size() const {
	return vector.size();
}