#pragma once
template <typename T>
class Vector {
	T* baseArray;
	size_t arraySize = 0;
	size_t arrayCapacity = 1;
public:
	Vector();
	~Vector(); 

	Vector(Vector<T> &vector);

	Vector(const Vector<T> &vector);

	Vector<T>& operator=(const Vector<T> &Vector);

	T& operator[](size_t index);

	void push_back(const T &value);

	T &at(const size_t i);

	T pop_back();

	void clear();

	void reserve(const int i);

	bool empty();

	void resize(const size_t);
	
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
Vector<T>::Vector(const Vector<T> & otherVector){
	reserve(otherVector.capacity());
	size_t otherSize = otherVector.size();
	arraySize = otherSize;
	for (int i = 0; i < otherSize; i++) {
		baseArray[i] = otherVector[i];
	}
}

template<typename T>
Vector<T>::Vector(Vector<T> & otherVector) {
	reserve(otherVector.capacity());
	size_t otherSize = otherVector.size();
	arraySize = otherSize;
	for (int i = 0; i < otherSize; i++) {
		baseArray[i] = otherVector[i];
	}
}

template<typename T>
Vector<T> & Vector<T>::operator = (const Vector<T> & Vector){
	reserve(vec.capacity());
	arraySize = Vector.size();

	for (int i = 0; i < Vector.size(); i++) {
		baseArray[i] = Vector.at(i);
	}
	return *this;
}


template<typename T>
T & Vector<T>::operator[](const size_t index){
	return baseArray[index];
}

template<typename T>
void Vector<T>::push_back(const T & value){
	if (arraySize + 1 > arrayCapacity) {
		reserve(arrayCapacity * 2);
	}
	baseArray[arraySize] = value;
	arraySize++;
}

template<typename T>
T & Vector<T>::at(const size_t i){
	return baseArray[i];
}

template<typename T>
T Vector<T>::pop_back(){
	if(arraySize>0)
		arraySize--;
	return baseArray[arraySize + 1];
}

template<typename T>
void Vector<T>::clear(){
	arraySize = 0;
}

template<typename T>
void Vector<T>::reserve(int cap){
	T * temp = new T[cap];
	arrayCapacity = cap;
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
void Vector<T>::resize(size_t i){
	if (i > arrayCapacity) {
		reserve(i * 2);
	}
	arraySize = i;
}

template<typename T>
size_t Vector<T>::size(){
	return(arraySize);
}

template<typename T>
size_t Vector<T>::capacity()
{
	return arrayCapacity;
}
