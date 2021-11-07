#include "StackApp.h"
#include <cassert>
#include <ctype.h>

//**** stack 구현 ****

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

//**** evaluator class 구현 ****

//우선순위 판단 함수
bool is_lower(char new_op, char old_op) {
	if ((new_op == '+' || new_op == '-') && (old_op == '*' || old_op == '/')) return true;
	else if ((new_op == '+' || new_op == '-') && (old_op == '+' || old_op == '-')) return true;
	else return false;
}

//연산자 스택 데이터를 문자열에 저장
void write_string(string& s, stack<char>& b) {
	s.push_back(b.top());
	s.append(" ");
	b.pop();
}

string evaluator::read_expression() {
	string exp;
	cout << "Enter infix notation: ";
	cin.ignore(); //ignore new line
	getline(cin, exp); //input infix notation

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
			while(isdigit(s[i]) || s[i] == '.'){
				postfix.push_back(s[i]);
				i++;
				if (i == s.length()) break;
			}
			postfix.append(" ");
			i--; //for문을 반복 하기전에 i값을 줄여줌
		}

		else if (strchr("+-*/", s[i]) != NULL) {
			if (token.empty()) token.push(s[i]); //stack이 비어있다면 push

			else {
				while (!token.empty() && token.top() != '(' && is_lower(s[i], token.top())) { //우선순위를 고려해서 postfix에 output
					write_string(postfix, token);
				}
				token.push(s[i]); //스택에 연산자 추가
			}
		}

		else if (s[i] == ')') {
			while (token.top() != '(') {
				write_string(postfix, token);
			}
			token.pop(); //pop '('
		}
	}
	
	//스택에 남아 있는 연산자 pop & write
	while (!token.empty()) {
		write_string(postfix, token);
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
			string temp; //숫자인 문자열을 저장할 임시 string
			while (isdigit(s[i]) || s[i] == '.') {
				temp.push_back(s[i]);
				i++;
				if (i == s.length()) break;
			}
			number.push(stod(temp)); //string을 double로 변환 후 push
			i--;
		}
		else if (strchr("+-*/", s[i]) != NULL) { //계산
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

		else if (isalpha(s[i])) { //수식에 변수가 존재할 경우 대입 값을 입력받고 push한다.
			double num;
			cout << "Enter a value to substitute for " << s[i] << ": ";
			cin >> num;
			number.push(num);
		}
		i++;
	}
	
	re = number.top();
	number.pop();
	return re;
}