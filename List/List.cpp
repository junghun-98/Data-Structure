#include "LinkedList.h"
#include <time.h>

template<typename T> List<T>::List(){
	this->head = NULL;
	this->choose = NULL;
	this->size = 0;
}

template<typename T> List<T>::~List(){
	clear();
}

template<typename T> void List<T>::setnode(Node* n, T setdata, Node* next){
	n->data = setnum;
	n->next = next;
}

template<typename T> void List<T>::add(T data) {
	if (head == NULL) {
		head = new Node;
		head->data = data;
		head->next = NULL;
	}
	else {
		Node* ptr = head;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = new Node;
		setnode(ptr->next, data, NULL);
	}
	this->size++;
}

template<typename T> void List<T>::insert(int pre_loc, int next_loc, T insert_data){
	Node* ptr = head;
	for (int i = 0; i < pre_loc - 1; i++)
	{
		ptr = ptr->next;
	}
	
	if (ptr->next == NULL) {
		//insert data to last node
		add(insert_data);
	}
	else if (pre_loc - next_loc != -1) {
		cout << "Each nodes are not neighboring!\n";
		return;
	}
	else {
		Node* newnode = new Node;
		setnode(newnode, insert_data, ptr->next);
		ptr->next = newnode;
		this->size++;
	}		
}

template<typename T> void List<T>::remove(int node){
	Node* ptr = head;
	
	if (node > size || node < 0) {
		cout << "Wrong node!\n";
		return;
	}

	else if (node == 1) {
		head = ptr->next;
		delete ptr;
	}

	else{
		Node* pre = head;
		for (int i = 1; i < node; i++)
		{
			pre = ptr;
			ptr = choose = ptr->next;
		}
		pre->next = ptr->next;
		delete ptr;
		this->size--;
	}
}
template<typename T>
bool List<T>::search(T data) {
	Node* ptr = head;
	while (ptr != NULL) {
		if (ptr->data == data) return true;
		else ptr = ptr->next;
	}
	return false;
}

template<typename T> void List<T>::clear(){
	for (int i = this->size; i > 0; i--)
	{
		remove(i);
	}
	this->size = 0;
}

template<typename T> void List<T>::printalldata(){
	Node* ptr = head;

	if (head == NULL) {
		cout << "No data. Pleas add data\n";
		return;
	}

	do{
		cout << ptr->data; 
		ptr = ptr->next;
		cout << "->";
	} while (ptr != NULL);
	cout << "NULL" << endl;
}