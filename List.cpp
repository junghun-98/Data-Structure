#include <iostream>
#include <vector>
using namespace std;

class Linkedlist{
private:
	class Node {
		int data;
		Node* next;
	};
	
	Node* head;
	Node* choose;
	
public:
	Linkedlist();
	~Linkedlist();

	void search(); 
	void insert(); 
	void remove(); 
	void clear();  
	void printdata();
	void printalldata();
};
