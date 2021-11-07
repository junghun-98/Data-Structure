#include "StackApp.h"
#include <cassert>
#include <ctype.h>

//**** stack ���� ****

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

//**** evaluator class ���� ****

//�켱���� �Ǵ� �Լ�
bool is_lower(char new_op, char old_op) {
	if ((new_op == '+' || new_op == '-') && (old_op == '*' || old_op == '/')) return true;
	else if ((new_op == '+' || new_op == '-') && (old_op == '+' || old_op == '-')) return true;
	else return false;
}

//������ ���� �����͸� ���ڿ��� ����
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
			while(isdigit(s[i]) || s[i] == '.'){
				postfix.push_back(s[i]);
				i++;
				if (i == s.length()) break;
			}
			postfix.append(" ");
			i--; //for���� �ݺ� �ϱ����� i���� �ٿ���
		}

		else if (strchr("+-*/", s[i]) != NULL) {
			if (token.empty()) token.push(s[i]); //stack�� ����ִٸ� push

			else {
				while (!token.empty() && token.top() != '(' && is_lower(s[i], token.top())) { //�켱������ ����ؼ� postfix�� output
					write_string(postfix, token);
				}
				token.push(s[i]); //���ÿ� ������ �߰�
			}
		}

		else if (s[i] == ')') {
			while (token.top() != '(') {
				write_string(postfix, token);
			}
			token.pop(); //pop '('
		}
	}
	
	//���ÿ� ���� �ִ� ������ pop & write
	while (!token.empty()) {
		write_string(postfix, token);
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
			string temp; //������ ���ڿ��� ������ �ӽ� string
			while (isdigit(s[i]) || s[i] == '.') {
				temp.push_back(s[i]);
				i++;
				if (i == s.length()) break;
			}
			number.push(stod(temp)); //string�� double�� ��ȯ �� push
			i--;
		}
		else if (strchr("+-*/", s[i]) != NULL) { //���
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

		else if (isalpha(s[i])) { //���Ŀ� ������ ������ ��� ���� ���� �Է¹ް� push�Ѵ�.
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