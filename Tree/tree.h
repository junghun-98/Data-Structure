#pragma once

class tree {
private:
	class node {
	public:
		int data;
		node* right;
		node* left;
	};
public:
	tree();
	bool search();
	void add();
	void remove();
	void print();
	void clear();
	~tree();
};
