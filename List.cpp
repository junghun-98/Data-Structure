#include "LinkedList.h"

List::List(){
	this->head = NULL;
	this->choose = NULL;
	this->size = 0;
}
List::~List(){
	clear();
}

void List::setnode(Node* n, int setnum, Node* next){
	n->data = setnum;
	n->next = next;
}
void List::add(int number) {
	if (head == NULL) {
		head = new Node;
		head->data = number;
		head->next = NULL;
	}
	else {
		Node* ptr = head;
		while (ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = new Node;
		setnode(ptr->next, number, NULL);
	}
	this->size++;
}

void List::insert(int pre_data, int next_data, int insert_data){
	Node* ptr = head;
	while (ptr->data != pre_data) {
		ptr = ptr->next;
	}

	if (ptr->next->data != next_data) {
		cout << "Unable to insert!\n";
		return;
	}
	else {
		Node* newnode = new Node;
		setnode(newnode, insert_data, ptr->next);
		ptr->next = newnode;
		this->size++;
	}		
}

void List::remove(int node){
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
bool List::search(int data) {
	Node* ptr = head;
	while (ptr != NULL) {
		if (ptr->data == data) return true;
		else ptr = ptr->next;
	}
	return false;
}
void List::clear(){
	for (int i = this->size; i > 0; i--)
	{
		remove(i);
	}
	this->size = 0;
}
void List::printalldata(){
	Node* ptr = head;

	if (head == NULL) {
		cout << "No data. Pleas add data\n";
		return;
	}

	while (1) {
		cout << ptr->data; 
		ptr = ptr->next;
		if (ptr == NULL) break;
		cout << "->";
	}
	cout << endl;
}

int main() {
	return 0;
}