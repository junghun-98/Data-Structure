#include <iostream>

using namespace std;

template<typename T>
class stack {
private:
	class node {
	public:
		T data;
		node* next;
	};

	int size;
	node* head;

public:
	stack();
	void push(T d);
	T pop();
	void peek();
	void clear();
	int stack_size() { return size; }
	bool is_empty();
	bool search(T d);
	void print();
	~stack();
};