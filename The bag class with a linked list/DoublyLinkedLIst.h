#pragma once
#include <iostream>
#include <cassert>

using namespace std;

/*Doubly Linked List를 이루는 기본 단위 dnod */
class dnode {
public:
	typedef double value_type;

	dnode(const value_type& data = value_type(), dnode* init_forelink = NULL, dnode* init_backlink = NULL ) {
		//dnode's data initialize
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
//Postcondition : 인자로 전달된 포인터가 가리키는 리스트의 크기 반환

void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry);
void list_insert(dnode* previous_ptr, const dnode::value_type& entry);

const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target);
dnode* list_search(dnode* head_ptr, const dnode::value_type& target);

const dnode* list_locate(const dnode* head_ptr, size_t position);
dnode* list_locate(dnode* head_ptr, size_t position);
// precondition: position > 0

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr);

void list_head_remove(dnode*& head_ptr);
void list_remove(dnode* previous_ptr);

void list_clear(dnode*& head_ptr);

//Doubly Linked List를 이용해 data를 저장하는 bag class
class bag {
public:
	typedef size_t size_type;
	typedef double value_type;

	bag();
	bag(const bag& source);
	~bag();
	
	void operator =(const bag& source);
	void operator +=(const bag& addend);
	bool operator ==(const bag& source);
	bool operator !=(const bag& source);

	bool erase_one(const value_type& target);

	size_type size() { return many_nodes; }
	size_type count(const value_type& target) const;
	value_type grab();

	void show_content();
	void show_content_reverse();
	void insert(const value_type& entry);
	void sort(bag& source);
private:
	dnode* head_ptr;
	dnode* tail_ptr;
	size_type many_nodes;
};