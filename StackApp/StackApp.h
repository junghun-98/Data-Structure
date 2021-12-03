//Doubly Linked List�� �̿��� ������ stack template class
//stack�� ����� �����ʹ� ���� �ʰ� ����� �����ͺ��� ����ȴ�.
//template�� ����ϸ� �ش� �ش����Ͽ��� ������ �Լ����� �ٸ� *.cpp ���Ͽ��� ���� �Ұ��ϱ� ������ ���� ���Ͽ� �Լ� ���ǵ��� �����߽��ϴ�.

#include <iostream>
#include <string>

using namespace std;

//stack�� ����� �����͸� ��� doubly node
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
	//postcondition: stack�� top��ġ ������ ����

	item top() const;
	//precondition: stack is not empty
	//postcondition: stack�� top��ġ ������ ��ȯ

	bool empty();
	//postcondition: stack�� ������� �Ǻ��ϴ� ����ȯ
	
	void show();
	//postcondition: stack�� data��Ȳ ���
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
	stack<char> token; //������ ��ȯ �Ҷ� ������ token���� �о�� char�� stack
	stack<double> number; //������ ��� �� �� ����� double�� stack
};

bool compare_priorities(char new_op, char old_op);
//postcondition: new_op�� old_op�� ������ �켱������ �Ǵ��ؼ� new_op�� �켱������ old_op���� ���ų� ���ٸ� true, ������ false��ȯ 

void write_string_operator(string& s, stack<char>& b);
//postcondition: ���� top�� ����Ǿ� �ִ� �����ڸ� ���ڿ� s�� �߰��ϰ� �߰��� �����ڴ� stack���� pop

#include <cassert>
#include <ctype.h>

//**** list node toolkit ���� ****
template<class item>
void list_head_insert(dnode<item>*& head_ptr, const item& entry) {
	if (head_ptr == NULL) { //Insert data to empty list
		head_ptr = new dnode<item>(entry);
	}
	else {
		dnode<item>* temp_ptr;

		temp_ptr = head_ptr;
		head_ptr = new dnode<item>(entry, head_ptr, NULL);
		temp_ptr->set_backlink(head_ptr);
	}
}

template<class item>
void list_head_remove(dnode<item>*& head_ptr) {
	dnode<item>* remove_ptr = head_ptr;

	head_ptr = head_ptr->get_forelink();
	if (head_ptr != NULL) head_ptr->set_backlink(NULL);

	delete remove_ptr;
}

template<class item>
void list_copy(const dnode<item>* source_ptr, dnode<item>*& head_ptr, dnode<item>*& tail_ptr) {
	head_ptr = NULL, tail_ptr = NULL;

	if (source_ptr == NULL) return;

	list_head_insert(head_ptr, source_ptr->get_data());

	tail_ptr = head_ptr;
	source_ptr = source_ptr->get_forelink();

	while (source_ptr != NULL) {
		list_insert(tail_ptr, source_ptr->get_data());

		tail_ptr = tail_ptr->get_forelink();
		source_ptr = source_ptr->get_forelink();
	}
}

//**** stack class���� ****

template<class item>
stack<item>::stack(const stack<item>& source) {
	dnode<item>* tail_ptr;
	list_copy(source.top_ptr, top_ptr, tail_ptr);
	size = source.size;
}

template<class item>
void stack<item>::push(const item& entry) {
	list_head_insert(top_ptr, entry);
	size++;
}

template<class item>
void stack<item>::show() {
	if (top_ptr == NULL) return;
	dnode<item>* ptr = top_ptr;

	while (true) {
		cout << ptr->get_data();
		if ((ptr = ptr->get_forelink()) == NULL) break;
		cout << " <=> ";
	}
	cout << endl;
}

template<class item>
bool stack<item>::empty() {
	return (top_ptr == NULL);
}

template<class item>
void stack<item>::pop() {
	assert(top_ptr != NULL);
	list_head_remove(top_ptr);
	size--;
}

template<class item>
item stack<item>::top() const {
	assert(top_ptr != NULL);
	return top_ptr->get_data();
}

//**** evaluator class ���� ****

//�켱���� �Ǵ� �Լ�
bool compare_priorities(char new_op, char old_op) {
	if ((new_op == '+' || new_op == '-') && (old_op == '*' || old_op == '/')) return true;
	else if ((new_op == '+' || new_op == '-') && (old_op == '+' || old_op == '-')) return true;
	else return false;
}

//���ÿ� ����� ������ �����͸� ���ڿ��� ����
void write_string_operator(string& s, stack<char>& b) {
	s.push_back(b.top());
	s.append(" ");
	b.pop();
}

string evaluator::read_expression() {
	string exp;
	cout << "Enter infix notation: ";
	cin.ignore(); //ignore new line '\n' (main.cpp���� �ɼ��� �Է¹��� �� �Է��� ���๮�ڸ� �����մϴ�.)
	getline(cin, exp); //input infix notation
	cout << endl << "The infix notaion you entered : " << exp << endl;

	return exp;
}

string evaluator::convert_to_postfix(string s) {
	//assert(string s is infix);

	string postfix; //��ȯ�Ͽ� ��ȯ�� ���ڿ� (output)

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			token.push(s[i]);
		}

		else if (isalpha(s[i])) { //����
			postfix.push_back(s[i]);
			postfix.append(" ");
		}

		else if (isdigit(s[i]) || s[i] == '.') {
			//���ڰ� �ƴҶ� ���� �ݺ��ؼ� postfix�� output
			while (isdigit(s[i]) || s[i] == '.') {
				postfix.push_back(s[i]);
				i++;
				if (i == s.length()) break; //end of string
			}
			postfix.append(" ");
			i--; //for���� �ݺ� �ϱ����� i���� �ٿ���
		}

		else if (strchr("+-*/", s[i]) != NULL) {
			if (token.empty()) token.push(s[i]); //stack�� ����ִٸ� push

			else {
				while (!token.empty() && token.top() != '(' && compare_priorities(s[i], token.top())) { 
					//�켱������ ����ؼ� postfix�� output
					write_string_operator(postfix, token);
				}
				token.push(s[i]); //while���� ������ �������� �ʴ� �ٸ� ���ÿ� ������ �߰�
			}
		}

		else if (s[i] == ')') {
			while (token.top() != '(') {
				write_string_operator(postfix, token);
			}
			token.pop(); //pop '('
		}
	}

	//���ÿ� ���� �ִ� ������ pop & write
	while (!token.empty()) {
		write_string_operator(postfix, token);
	}

	return postfix;
}

double evaluator::evaluate_postfix(string s) {
	//assert(string s is postfix);

	int i = 0; //string s�� ��ȸ�� �ε���
	double re; //��ȯ�� ��� ���� �����ϴ� ����

	while (i < s.length()) {
		double oper1 = 0, oper2 = 0; //�ǿ�����

		if (isdigit(s[i]) || s[i] == '.') {
			string temp; //���������� ���ڿ��� ������ �ӽ� string
			while (isdigit(s[i]) || s[i] == '.') {
				temp.push_back(s[i]);
				i++;
				if (i == s.length()) break; //end of string
			}
			number.push(stod(temp)); //string�� double�� ��ȯ �� push
			i--;
		}
		else if (strchr("+-*/", s[i]) != NULL) { //�����ڿ� ���� ���
			oper2 = number.top();
			number.pop();
			oper1 = number.top();
			number.pop();

			switch (s[i])
			{
			case '+': number.push(oper1 + oper2); break;
			case '-': number.push(oper1 - oper2); break;
			case '*': number.push(oper1 * oper2); break;
			case '/': number.push(oper1 / oper2); break;
			}
		}

		else if (isalpha(s[i])) { 
			//���Ŀ� ������ ������ ��� ���� ���� �Է¹ް� �� ���� stack�� push�Ѵ�.
			double num;
			cout << "Enter a value to substitute for " << s[i] << ": ";
			cin >> num;
			number.push(num);
			cout << endl;
		}
		i++;
	}

	re = number.top();
	number.pop(); //stack clear
	return re;
}