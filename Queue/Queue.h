#pragma once
#include <iostream>

using namespace std;

template<typename T>
class queue {
private:
	class node {
	public:
		T data;
		node* next;
	};
	
	node* head;
	node* tail;
	int size;

public:
	queue();
	void enque(T d);
	T deque();
	T peek();
	void clear();
	int quesize() { return size; }
	bool is_empty();
	bool search(T d);
	void print();
	~queue();
};