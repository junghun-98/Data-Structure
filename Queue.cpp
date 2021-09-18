#include "Queue.h"

template<typename T> queue<T>::queue() {
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}

template<typename T> void queue<T>::enque(T d){
	if (head == NULL) {
		head = tail = new node;
		head->next = tail->next = NULL;
		head->data = d;
	}
	else {
		tail->next = new node;
		tail = tail->next;
		tail->next = NULL;
		tail->data = d;
	}
	size++;
	cout << "Enque data!\n";
}

template<typename T> T queue<T>::deque(){
	node* ptr = head;
	int dequedata = ptr->data;
	head = ptr->next;

	delete ptr;
	size--;
	cout << "Deque data!\n";

	return dequedata;
}

template<typename T> T queue<T>::peek(){
	if (head == NULL) {
		cout << "We don't have data\n";
	}
	else {
		cout << "Peek data!\n";
		return head->data;
	}
}

template<typename T> void queue<T>::clear(){
	node* ptr = head;
	node* delptr;
	head = tail = NULL;
	size = 0;
	while (ptr != NULL) {
		delptr = ptr;
		ptr = ptr->next;
		delete delptr;		
	}
}

template<typename T> bool queue<T>::is_empty(){
	if (head == NULL) return true;
	else return true;
}

template<typename T> bool queue<T>::search(T d){
	node* ptr = head;

	while (ptr != NULL) {
		if (ptr->data == d) break;
		ptr = ptr->next;
	}

	if (ptr == NULL) return false;
	else return true;
}

template<typename T> void queue<T>::print(){
	if (head == NULL) {
		cout << "We don't have data\n";
		return;
	}
	int i = 1;
	node* ptr = head;
	while (ptr != NULL)
	{
		cout << "[" << i << "] " << ptr->data << endl;
		ptr = ptr->next;
		i++;
	}
}

template<typename T> queue<T>::~queue(){
	clear();
}