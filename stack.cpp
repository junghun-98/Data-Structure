#include "stack.h"
#include <string>

template<typename T> stack<T>::stack(){
	this->size = 0;
	this->head = NULL;
}

template<typename T> void stack<T>::push(T d) {
	if (head == NULL) {
		head = new node;
		head->data = d;
		head->next = NULL;
	}
	else {
		node* ptr = head;
		head = new node;
		head->data = d;
		head->next = ptr;		
	}

	size++;
}
template<typename T> T stack<T>::pop() {
	if (head == NULL) {
		cout << "We don't have data\n";
	}
	else {
		node* popnode = head;
		T popdata = head->data;
		head = popnode->next;

		delete popnode;
		size--;
		return popdata;
	}
}
template<typename T> void stack<T>::peek() {
	if (head == NULL) {
		cout << "We don't have data\n";
	}
	else{
		cout << "Next pop data : " << head->data << endl;
	}
}
template<typename T> void stack<T>::clear(){
	node* ptr = head;
	node* deleteptr = head;
	while (ptr->next != NULL) {
		ptr = deleteptr->next;
		delete deleteptr;
		deleteptr = ptr;
	}
	head = NULL;
	size = 0;
}
template<typename T> bool stack<T>::is_empty(){
	if (head == NULL) return true;
	else return false;
}
template<typename T> bool stack<T>::search(T d) {
	node* ptr = head;

	while (ptr->data != d) {
		ptr = ptr->next;
		if (ptr == NULL) return false;
	}
 
	return true;
}

template<typename T> void stack<T>::print() {
	node* ptr = head;
	if (ptr == NULL) {
		cout << "We don't have data\n";
		return;
	}
	for (int i = 1; i <= size; i++)
	{
		cout << "[" << i << "] " << ptr->data << "\n";
		ptr = ptr->next;
	}
	
	cout << endl;
}

template<typename T> stack<T>::~stack() {
	clear();
}

int main() { }