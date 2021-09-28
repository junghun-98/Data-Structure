#pragma once
#include <iostream>
#include <cassert>
#include <time.h>
#include <algorithm>

using namespace std;

/*Doubly Linked List를 이루는 기본 단위 dnode */
class dnode {
public:
	typedef double value_type;
	
	//dnode's data initialize
	dnode(const value_type& data = value_type(), dnode* init_forelink = NULL, dnode* init_backlink = NULL ) {
		data_field = data;
		link_fore = init_forelink;
		link_back = init_backlink;
	}

	void set_data(const value_type& new_data) { data_field = new_data; }
	
	void set_forelink(dnode* new_link) { link_fore = new_link; }
	void set_backlink(dnode* new_link) { link_back = new_link; }

	value_type get_data() const { return data_field; }

	dnode* get_forelink() { return link_fore; }
	dnode* get_backlink() { return link_back; }

	const dnode* get_forelink() const { return link_fore; }
	const dnode* get_backlink() const { return link_back; }
private:
	value_type data_field;
	dnode* link_fore;
	dnode* link_back;
};

size_t list_length(const dnode* head_ptr);
// postcondition: 인자로 전달된 포인터가 가리키는 리스트의 node개수 반환

void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry);
// postcondition: 인자로 전달된 head_ptr이 가리키는 list의 head 부분에 data의 값을 entry로 갖는 node를 삽입

void list_insert(dnode* previous_ptr, const dnode::value_type& entry);
// postcondition: 인자로 전달된 previous_ptr 다음 자리에 data의 값을 entry로 갖는 node를 삽입

const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target);
dnode* list_search(dnode* head_ptr, const dnode::value_type& target);
// postcondition: 인자로 전달된 head_ptr이 가리키고 있는 list를 검색하여 target과 일치하는 data의 존재 여부를
//				  판단하고 존재 한다면 해당 node의 포인터를 반환 (단, 존재하지 않으면 NULL 포인터 반환)

const dnode* list_locate(const dnode* head_ptr, size_t position);
dnode* list_locate(dnode* head_ptr, size_t position);
// precondition: position > 0
// postcondition: head_ptr이 가리키는 list에서 인자로 전달된 position에 해당하는 위치의 node pointer 반환
//				  (단, 존재하지 않으면 NULL 포인터 반환)

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr);
// postcondition: source_ptr이 가리키고 있는 list를 head_ptr과 tail_ptr에 복사

void list_head_remove(dnode*& head_ptr);
// postcondition: 인자로 전달된 head_ptr이 가리키는 list의 head node를 제거

void list_remove(dnode* previous_ptr);
// postcondition: 인자로 전달된 previous_ptr이 가리키는 node 다음 node 제거

void list_clear(dnode*& head_ptr);
// postcondition: list clear, 동적으로 할당된 recource(nodes) 반환


//Doubly Linked List를 이용해 data를 저장하는 bag class
class bag {
public:
	typedef size_t size_type;
	typedef double value_type;

	bag();
	bag(const bag& source); //copy constructor
	~bag();
	
	void operator =(const bag& source); //assingment
	void operator +=(const bag& addend);

	bool operator ==(const bag& source);
	bool operator !=(const bag& source);
    // postcondition: 두 bag class가 저장하고 있는 data를 비교하는 연산자
	//				  (data의 순서를 고려하지 않는다.)

	bool erase_one(const value_type& target);
	// postcondition: bag class에 저장된 data를 조사하여 target값과 같은 data를 갖는
	//				 node를 발견하는 즉시 제거 후 head node의 data로 대체

	size_type size() { return many_nodes; }
	size_type count(const value_type& target) const;
	// postcondition: bag class에 저장된 data를 조사하여 target값과 같은 data를 갖는
	//				 node의 개수 반환

	value_type grab();
	// precondition: size() > 0
	// postcondition: bag class에 저장된 data를 중 무작위로 아무 data를 반환

	void show_content();
	// postcondition: bag class에 저장된 data를 head부터 tail까지 출력
 	
	void show_content_reverse();
	// postcondition: bag class에 저장된 data를 tail부터 head까지 출력

	void insert(const value_type& entry);
	// postcondition: 인자로 전달된 entry의 값을 data로 갖는 node를 head에 삽입

	void sort();
	// postcondition: bag class의 data를 오름차순으로 정렬 
private:
	dnode* head_ptr;
	dnode* tail_ptr;
	size_type many_nodes;
};