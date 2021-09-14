#include <iostream>
#include <algorithm>
#include "Bag.h"

using namespace std;

template <typename T> bag<T>::bag(){}
template <typename T> bag<T>::bag(const int init_capacity){}
template <typename T> bag<T>::bag(const bag& source) {} //copy constructor.

template <typename T> 
void bag<T>::reserve(int new_size) {} //Modify the memory size.

template <typename T> 
void bag<T>::insert(T new_data){}

template <typename T>
void bag<T>::remove(T data){}

template <typename T>
void bag<T>::printdata(){}

template <typename T>
void bag<T>::operator=(const bag& source){}

template <typename T>
void bag<T>::operator+=(const bag& addend){}

int main() {

}