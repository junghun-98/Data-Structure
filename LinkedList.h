#pragma once

#include <iostream>

using namespace std;

class List {
private:
	class Node {
	public:
		int data;
		Node* next;
	};

	Node* head;
	Node* choose;

	int size;
public:
	List();
	~List();

	int listsize() { return size; }
	void add(int number);
	void setnode(Node* n, int setnum, Node* next);
	bool search(int data);
	void insert(int pre_data, int next_data, int insert_data);
	void remove(int node);
	void clear();
	void printalldata();
};
