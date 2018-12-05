#pragma once
template <typename T>
class Vector {
	T* baseArray;
	size_t arraySize;
	size_t arrayCapacity;
public:
	Vector();
	~Vector(); 

	Vector(Vector &vector);

	Vector& operator=(Vector &Vector);

	T& operator[](size_t index);

	void push_back(T &value);

	T &at(size_t i);

	void pop_back();

	void clear();

	void reserve();

	bool empty();

	void resize();
	
	size_t size();
	size_t capacity();

};

template<typename T>
Vector<T>::Vector() {
	baseArray = new T[1];
	arrayCapacity = 1;
	arraySize = 0;
}

template<typename T>
Vector<T>::~Vector(){ //https://stackoverflow.com/questions/2425728/delete-vs-delete-operators-in-c
	delete[] baseArray;
}

template<typename T>
Vector<T>::Vector(Vector & otherVector){
	reserve(otherVector.capacity());
	size_t otherSize = otherVector.size();
	arraySize = otherSize;
	for (int i = 0; i < otherSize; i++) {
		baseArray[i] = otherVector[i];
	}
}

template<typename T>
Vector & Vector<T>::operator=(Vector & Vector)
{
	
}


template<typename T>
T & Vector<T>::operator[](size_t index){
	return baseArray[i];
}

template<typename T>
void Vector<T>::push_back(T & value){
	if (size + 1 <= capacity) {
		resize(capacity * 2);
	}
	baseArray[size] = value;
	size++;
}

template<typename T>
T & Vector<T>::at(size_t i){
	
}

template<typename T>
void Vector<T>::pop_back()
{
}

template<typename T>
void Vector<T>::clear()
{
}

template<typename T>
void Vector<T>::reserve()
{
}

template<typename T>
bool Vector<T>::empty()
{
	return false;
}

template<typename T>
void Vector<T>::resize()
{
}

template<typename T>
size_t Vector<T>::size()
{
	return size_t();
}

template<typename T>
size_t Vector<T>::capacity()
{
	return size_t();
}
