#pragma once

#include <iostream>

using namespace std;

template<typename T>
class List {
private:
	class Node {
	public:
		T data;
		Node* next;
	};

	Node* head;
	Node* choose;

	int size;
public:
	List();
	~List();

	int listsize() { return size; }
	void add(T data);
	void setnode(Node* n, T setdata, Node* next);
	bool search(T data);
	void insert(int pre_data, int next_data, T insert_data);
	void remove(int node);
	void clear();
	void printalldata();
};
