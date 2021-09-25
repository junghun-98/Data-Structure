#include "tree.h"
#include <iostream>

using namespace std;

/*이진 검색트리
  1.노드를 기준으로 왼쪽 노드의 모든 값은 작고 오른쪽 노드의 모든 값은 큼
  2. 중복을 허용하지 않는다.*/

//생성자, 루트노드 생성
tree::tree() {

}

//검색 함수
bool tree::search() {
	return true;
}

//노드 추가 함수
void tree::add() {

}

//노드 제거 함수
void tree::remove() {

}
//tree출력함수
void tree::print() {

}

//tree 제거 함수
void tree::clear() {

}
//tree 소멸자
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