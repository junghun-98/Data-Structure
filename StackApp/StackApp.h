//Doubly Linked List를 이용해 구현한 stack template class
//stack에 저장된 데이터는 가장 늦게 저장된 데이터부터 추출된다.

//stack에 저장될 데이터를 담는 doubly node
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
	//postcondition: stack에 새로운 데이터 추가

	void pop();
	//precondition: stack is not empty
	//postcondition: stack에 새로운 데이터 추가

	item top() const;
	//precondition: stack is not empty
	//postcondition: stack에 top위치 데이터 반환

	bool empty();
	//postcondition: stack이 비었는지 판별하고 boolean값 반환
	void show();
	size_t get_size() const { return size; }
private:
	dnode<item>* top_ptr;
	size_t size;
};

template<class item>
void list_head_insert(dnode<item>*& head_ptr, const item& entry);
// postcondition: 인자로 전달된 head_ptr이 가리키는 list의 head 부분에 data의 값을 entry로 갖는 node를 삽입

template<class item>
void list_head_remove(dnode<item>*& head_ptr);
// postcondition: 인자로 전달된 head_ptr이 가리키는 list의 head node를 제거

template<class item>
void list_copy(const dnode<item>* source_ptr, dnode<item>*& head_ptr, dnode<item>*& tail_ptr);
// postcondition: source_ptr이 가리키고 있는 list를 head_ptr과 tail_ptr에 복사

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