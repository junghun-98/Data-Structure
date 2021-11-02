//Doubly Linked List�� �̿��� ������ stack template class
//stack�� ����� �����ʹ� ���� �ʰ� ����� �����ͺ��� ����ȴ�.

//stack�� ����� �����͸� ��� doubly node
#include <iostream>
#include <string>

using namespace std;

template<class item>
class dnode {
public:
	dnode(const item& data = item(), dnode<item>* init_forelink = NULL, dnode* init_backlink = NULL) {
		data_field = data;
		link_fore = init_forelink;
		link_back = init_backlink;
	}

	void set_data(const item& new_data) { data_field = new_data; }

	void set_forelink(dnode<item>* new_link) { link_fore = new_link; }
	void set_backlink(dnode<item>* new_link) { link_back = new_link; }

	item get_data() const { return data_field; }

	dnode<item>* get_forelink() { return link_fore; }
	dnode<item>* get_backlink() { return link_back; }

	const dnode<item>* get_forelink() const { return link_fore; }
	const dnode<item>* get_backlink() const { return link_back; }
private:
	item data_field;
	dnode<item>* link_fore;
	dnode<item>* link_back;
};

//stack class
template<class item>
class stack {
public:
	stack(dnode<item>* ptr = NULL) { //constructor
		top_ptr = ptr;
		size = 0;
	}
	stack(const stack<item>& source); //copy constructor

	void push(const item& entry);
	//postcondition: stack�� ���ο� ������ �߰�

	void pop();
	//precondition: stack is not empty
	//postcondition: stack�� ���ο� ������ �߰�

	item top() const;
	//precondition: stack is not empty
	//postcondition: stack�� top��ġ ������ ��ȯ

	bool empty();
	//postcondition: stack�� ������� �Ǻ��ϰ� boolean�� ��ȯ
	void show();
	size_t get_size() const { return size; }
private:
	dnode<item>* top_ptr;
	size_t size;
};

template<class item>
void list_head_insert(dnode<item>*& head_ptr, const item& entry);
// postcondition: ���ڷ� ���޵� head_ptr�� ����Ű�� list�� head �κп� data�� ���� entry�� ���� node�� ����

template<class item>
void list_head_remove(dnode<item>*& head_ptr);
// postcondition: ���ڷ� ���޵� head_ptr�� ����Ű�� list�� head node�� ����

template<class item>
void list_copy(const dnode<item>* source_ptr, dnode<item>*& head_ptr, dnode<item>*& tail_ptr);
// postcondition: source_ptr�� ����Ű�� �ִ� list�� head_ptr�� tail_ptr�� ����

class evaluator {
public:
	string read_expression();
	//postcondition: a string for infix expression has been returned

	string convert_to_postfix(string s);
	// precondition: s is a well-formed infix arithmetic expression where the following conditions are met :
	//				(1) all operators(+, -, *, and / ) are binary,
	//				(2) operands are numbers or variables, and
	//				(3) parentheses are allowed in the expression, but not every operation needs to be fully parenthesized
	//postcondition: a string for postfix expression converted from s has been returned and the postfix
	//				string should have at least one blank space between operands / operators

	double evaluate_postfix(string s);
	// precondition: string s is a well-formed postfix arithmetic expression
	//				in which variables are allowed
	// postcondition: the evaluation result for s has been returned
private:
	stack<char> token;
};