#include <iostream>
#include <vector>

template <typename T>
void sort(T* arr, int length) {
	bool unsorted = true;
	while (unsorted) {
		unsorted = false;
		for (int i = 0; i < length - 1; i++) {
			if (arr[i] < arr[i + 1]) {
				std::swap(arr[i], arr[i + 1]);
				unsorted = true;
			}
		}
	}
}

template <typename T>
int minInArr(T* arr, int start, int length) {
	if (start == length) {
		return start;
	}
	auto min = arr[start];
	int minI = start;
	for (int i = start+1; i < length; i++) {
		if (arr[i] < min) {
			min = arr[i];
			minI = i;
		}
	}
	return minI;
}

template <typename T>
void iSort(T* arr, int length) {
	for (int i = 0; i < length; i++) {
		int tempI = minInArr(arr, i, length);
		std::swap(arr[tempI], arr[i]);
	}
}

template <typename T>
std::vector<int> qSort(T* arr, int length) {
	std::vector<int> left = *new std::vector<int>;
	std::vector<int> right = *new std::vector<int>;
	for (int i = 0; i < length; i++) {
		if (arr[i] <= rand()%length) {
			left.push_back(arr[i]);
		}
		else {
			right.push_back(arr[i]);
		}
	}
	qSort(&left[0], left.size());
	qSort(&right[0], right.size());
	left.insert(std::end(left), std::begin(right), std::end(right));
	return left;
}

int main() {
	int arr[] = { 
		3,7,2,4,3,8,1,37,5
	};
	iSort(arr, 9);
	for (int i = 0; i < 9; i++) {
		std::cout << arr[i] << ", ";
	}
	return 0;
}