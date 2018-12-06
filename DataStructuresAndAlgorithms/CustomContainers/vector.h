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

	void reserve(int i);

	bool empty();

	void resize(size_t);
	
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
Vector<T> & Vector<T>::operator=(Vector<T> & Vector){
	reserve(vec.capacity());
	arraySize = Vector.arraySize;

	for (int i = 0; i < Vector.arraySize; i++) {
		baseArray[i] = Vector.baseArray[i];
	}
	return *this;
}


template<typename T>
T & Vector<T>::operator[](size_t index){
	return baseArray[i];
}

template<typename T>
void Vector<T>::push_back(T & value){
	if (size + 1 <= capacity) {
		reserve(capacity * 2);
	}
	baseArray[size] = value;
	arraySize++;
}

template<typename T>
T & Vector<T>::at(size_t i){
	baseArray[i];
}

template<typename T>
void Vector<T>::pop_back(){
	arraySize--;
}

template<typename T>
void Vector<T>::clear(){
	arraySize = 0;
}

template<typename T>
void Vector<T>::reserve(int i){
	T temp[i] = new T[i];
	for (int i = 0; i < arraySize; i++) {
		temp[i] = baseArray[i];
	}
	baseArray = temp;
}

template<typename T>
bool Vector<T>::empty(){
	return arraySize;
}

template<typename T>
void Vector<T>::resize(size_t i)
{
	if (size > capacity) {
		reserve(size * 2);
	} else {

	}
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
