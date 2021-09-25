#include <iostream>
#include <algorithm>
#include <iostream>
#include "Bag.h"

using namespace std;

template <typename T> bag<T>::bag(const int init_capacity){
	data = new T[init_capacity];
	capacity = init_capacity;
	used = 0;
}
template <typename T> bag<T>::bag(const bag& source) {
	data = new T[source.capacity];
	capacity = source.capacity;
	used = source.used;
	copy(source.data, source.data + used, data);
} //copy constructor.

template <typename T> 
void bag<T>::reserve(int new_size) {
	if (new_size <= capacity)
		return;
	
	T* new_data = new T[new_size];
	copy(data, data + used, new_data);
	delete[] data;
	capacity = new_size;
	data = new_data;
} //Modify the memory size.

template <typename T> 
void bag<T>::insert(T new_data){
	if (capacity == used) {
		reserve(capacity * 2);
	}
	data[used] = new_data;
	used++;
}

template <typename T>
void bag<T>::remove(T remove_data){
	int i = 0;
	while (data[i] != remove_data && i < used) {
		i++;
	}
	if (i == used) return;
	data[i] = data[used - 1];
	used--;
}

template <typename T>
void bag<T>::printdata(){
	for (int i = 0; i < used; i++)
	{
		cout << data[i] << " ";
	}
	cout << endl;
}

template <typename T>
void bag<T>::operator=(const bag& source){
	T* new_data;
	if (this == &source)
		return;
	if(this->capacity != source.capacity){
		new_data = new T[source.capacity];
		delete[] data;
		this->data = new_data;
		this->capacity = source.capacity; 
	}

	this->used = source.used;
	copy(source.data, source.data + used, this->data);
}

//Test case
int main() {
	bag<int> b1(10);
	for (int i = 0; i < 8; i++)
	{
		b1.insert(i);
	}
	
	bag<int> b2(b1);
	bag<int> b3 = b2;

	cout << b1.size() << endl;
	
	cout << "b1: "; b1.printdata();
	cout << "b2: "; b2.printdata();
	cout << "b3: "; b3.printdata();

	b1.insert(5);
	cout << "b1: "; b1.printdata();

	b2.remove(0);
	cout << "b2: "; b2.printdata();

	cout << "b1 size: " << b1.size() << endl;
	cout << "b2 size: " << b2.size() << endl;
	cout << "b3 size: " << b3.size() << endl;

	return 0;
}