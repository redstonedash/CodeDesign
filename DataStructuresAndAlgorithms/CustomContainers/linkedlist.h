#pragma once
template <typename T>
struct node {
	node<T>* next;
	T data;
};

template <typename T>
struct linkedItterator {
	node<T> startNode;
	node<T> currentNode;
	node<T> lastNode;
	
};

struct linkedList {

};

template <typename T>
T operator*(linkedItterator<T> i) {
	return i.current.data;
}