#include "StackApp.h"
#include <cassert>
#include <ctype.h>

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
void stack<item>::pop() {
	assert(!empty());
	list_head_remove(top_ptr);
	size--;
}

template<class item>
bool stack<item>::empty() {
	return (top_ptr == NULL);
}

template<class item>
item stack<item>::top() const {
//	assert(!empty());
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

//evaluator

//우선순위 판단
bool is_lower(char newc, char old) {
	//newc < oldc -> true
	if ((newc == '+' || newc == '-') && (old == '*' || old == '/')) return true;
	else if ((newc == '+' || newc == '-') && (old == '+' || old == '-')) return true;
	else return false;
}

//스택 데이터를 문자열에 저장
void write_string(string& s, stack<char>& b) {
	s.push_back(b.top());
	s.append(" ");
	b.pop();
}

string evaluator::read_expression() {
	string exp;
	getline(cin, exp); //input infix notation

	return exp;
}

string evaluator::convert_to_postfix(string s) {
	//assert(string s is infix);
	string postfix;
	
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			token.push(s[i]);
		}

		else if (isdigit(s[i]) || isalpha(s[i]) || s[i] == '.') {
			//숫자가 아닐때 까지
			while(isdigit(s[i]) || isalpha(s[i]) || s[i] == '.'){
				postfix.push_back(s[i]);
				i++;
				if (i == s.length()) break;
			}
			postfix.append(" ");
			i--;
		}

		else if (strchr("+-*/", s[i]) != NULL) {
			//우선순위
			if (token.empty()) token.push(s[i]);

			else {
				while (!token.empty() && token.top() != '(' && is_lower(s[i], token.top())) {
					write_string(postfix, token);
				}
				token.push(s[i]);
			}
		}

		else if (s[i] == ')') {
			while (token.top() != '(') {
				write_string(postfix, token);
			}
			token.pop(); //pop '('
		}
	}
	
	//나머지 스택 출력
	while (!token.empty()) {
		write_string(postfix, token);
	}

	return postfix;
}

double evaluator::evaluate_postfix(string s) {
	//assert(string s is postfix);

	return 0;
}