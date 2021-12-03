//Doubly Linked List를 이용해 구현한 stack template class
//stack에 저장된 데이터는 가장 늦게 저장된 데이터부터 추출된다.
//template을 사용하면 해당 해더파일에서 정의한 함수들을 다른 *.cpp 파일에서 구현 불가하기 때문에 같은 파일에 함수 정의들을 구현했습니다.

#include <iostream>
#include <string>

using namespace std;

//stack에 저장될 데이터를 담는 doubly node
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
	//postcondition: stack에 top위치 데이터 추출

	item top() const;
	//precondition: stack is not empty
	//postcondition: stack에 top위치 데이터 반환

	bool empty();
	//postcondition: stack이 비었는지 판별하는 값반환
	
	void show();
	//postcondition: stack의 data현황 출력
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
	stack<char> token; //수식을 변환 할때 수식을 token으로 읽어올 char형 stack
	stack<double> number; //수식을 계산 할 때 사용할 double형 stack
};

bool compare_priorities(char new_op, char old_op);
//postcondition: new_op와 old_op의 연산자 우선순위를 판단해서 new_op의 우선순위가 old_op보다 낮거나 같다면 true, 높으면 false반환 

void write_string_operator(string& s, stack<char>& b);
//postcondition: 스택 top에 저장되어 있는 연산자를 문자열 s에 추가하고 추가한 연산자는 stack에서 pop

#include <cassert>
#include <ctype.h>

//**** list node toolkit 구현 ****
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

//**** stack class구현 ****

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

//**** evaluator class 구현 ****

//우선순위 판단 함수
bool compare_priorities(char new_op, char old_op) {
	if ((new_op == '+' || new_op == '-') && (old_op == '*' || old_op == '/')) return true;
	else if ((new_op == '+' || new_op == '-') && (old_op == '+' || old_op == '-')) return true;
	else return false;
}

//스택에 저장된 연산자 데이터를 문자열에 저장
void write_string_operator(string& s, stack<char>& b) {
	s.push_back(b.top());
	s.append(" ");
	b.pop();
}

string evaluator::read_expression() {
	string exp;
	cout << "Enter infix notation: ";
	cin.ignore(); //ignore new line '\n' (main.cpp에서 옵션을 입력받을 때 입력한 개행문자를 무시합니다.)
	getline(cin, exp); //input infix notation
	cout << endl << "The infix notaion you entered : " << exp << endl;

	return exp;
}

string evaluator::convert_to_postfix(string s) {
	//assert(string s is infix);

	string postfix; //변환하여 반환할 문자열 (output)

	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			token.push(s[i]);
		}

		else if (isalpha(s[i])) { //변수
			postfix.push_back(s[i]);
			postfix.append(" ");
		}

		else if (isdigit(s[i]) || s[i] == '.') {
			//숫자가 아닐때 까지 반복해서 postfix에 output
			while (isdigit(s[i]) || s[i] == '.') {
				postfix.push_back(s[i]);
				i++;
				if (i == s.length()) break; //end of string
			}
			postfix.append(" ");
			i--; //for문을 반복 하기전에 i값을 줄여줌
		}

		else if (strchr("+-*/", s[i]) != NULL) {
			if (token.empty()) token.push(s[i]); //stack이 비어있다면 push

			else {
				while (!token.empty() && token.top() != '(' && compare_priorities(s[i], token.top())) { 
					//우선순위를 고려해서 postfix에 output
					write_string_operator(postfix, token);
				}
				token.push(s[i]); //while문의 조건을 만족하지 않는 다면 스택에 연산자 추가
			}
		}

		else if (s[i] == ')') {
			while (token.top() != '(') {
				write_string_operator(postfix, token);
			}
			token.pop(); //pop '('
		}
	}

	//스택에 남아 있는 연산자 pop & write
	while (!token.empty()) {
		write_string_operator(postfix, token);
	}

	return postfix;
}

double evaluator::evaluate_postfix(string s) {
	//assert(string s is postfix);

	int i = 0; //string s를 순회할 인덱스
	double re; //반환할 결과 값을 저장하는 변수

	while (i < s.length()) {
		double oper1 = 0, oper2 = 0; //피연산자

		if (isdigit(s[i]) || s[i] == '.') {
			string temp; //숫자형태의 문자열을 저장할 임시 string
			while (isdigit(s[i]) || s[i] == '.') {
				temp.push_back(s[i]);
				i++;
				if (i == s.length()) break; //end of string
			}
			number.push(stod(temp)); //string을 double로 변환 후 push
			i--;
		}
		else if (strchr("+-*/", s[i]) != NULL) { //연산자에 따라 계산
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
			//수식에 변수가 존재할 경우 대입 값을 입력받고 그 값을 stack에 push한다.
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