#include "tree.h"
#include <iostream>

using namespace std;

/*���� �˻�Ʈ��
  1.��带 �������� ���� ����� ��� ���� �۰� ������ ����� ��� ���� ŭ
  2. �ߺ��� ������� �ʴ´�.*/

//������, ��Ʈ��� ����
tree::tree() {

}

//�˻� �Լ�
bool tree::search() {
	return true;
}

//��� �߰� �Լ�
void tree::add() {

}

//��� ���� �Լ�
void tree::remove() {

}
//tree����Լ�
void tree::print() {

}

//tree ���� �Լ�
void tree::clear() {

}
//tree �Ҹ���
tree::~tree() {
	clear();
}

struct MyStruct
{
	char name[10];
	int age;
	int weight;
};
int main() {
	MyStruct m;
	cout << sizeof(m);
	return 0;
}