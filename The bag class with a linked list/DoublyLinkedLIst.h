#pragma once
#include <iostream>

using namespace std;

/*Doubly Linked List를 이루는 기본 단위 class dnod */
class dnode {
public:
	typedef double value_type;

	dnode() {
		//Data initialize
		data_field = value_type();
		link_fore = NULL;
		link_back = NULL;
	}
	void set_data(const value_type& new_data) { data_field = new_data; }
	
	void set_forelink(dnode* new_link) { link_fore = new_link; }
	void set_backlink(dnode* new_link) { link_back = new_link; }

	value_type data() const { return data_field; }
	
	const dnode* get_forelink() const { return link_fore; }
	dnode* get_forelink() { return link_fore; }
	
	const dnode* get_backlink() const { return link_fore; }
	dnode* get_backlink() { return link_back; }

private:
	value_type data_field;
	dnode* link_fore;
	dnode* link_back;
};

size_t list_length(const dnode* head_ptr);

void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry);
void list_insert(dnode* previous_ptr, const dnode::value_type& entry);

dnode* list_search(const dnode* head_ptr, const dnode::value_type& target);
const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target);

dnode* list_locate(dnode* head_ptr, size_t position);
const dnode* list_locate(const dnode* head_ptr, size_t position);
// precondition: position > 0

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr);

void list_head_remove(dnode*& head_ptr);
void list_remove(dnode* previous_ptr);

void list_clear(dnode*& head_ptr);

class bag {
public:
	typedef std::size_t size_type;
	typedef double value_type;
	bag();
	bag(const bag& source);
	~bag();
	
	void operator =(const bag& source);
	void operator +=(const bag& addend);

	bool erase_one(const value_type& target);
	size_type count(const value_type& target) const;
	value_type grab();
	void insert(const value_type& entry);
private:
	dnode* head_ptr;
	size_type many_nodes;
};