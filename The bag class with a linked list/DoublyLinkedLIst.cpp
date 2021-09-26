//dnode Class를 사용한 함수(list류 함수들) 구현 파일
//bag Class의 멤버 함수 구현 파일

#include "DoublyLinkedLIst.h"

size_t list_length(const dnode* head_ptr){
	size_t size = 0;
	const dnode* cursor = head_ptr;
	
	while (cursor != NULL) {
		cursor = cursor->get_forelink();
		size++;
	}
	return size;
}

void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry) {
	head_ptr = new dnode(entry, head_ptr, NULL);
}

void list_insert(dnode* previous_ptr, const dnode::value_type& entry) {
	dnode* insert_ptr = new dnode(entry, previous_ptr->get_forelink(), previous_ptr);
	previous_ptr->set_forelink(insert_ptr);
}

const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target) {
	const dnode* cursor = head_ptr;

	while (cursor != NULL)
	{
		if (cursor->get_data() == target)
			return cursor;
	}
	return NULL;
}

const dnode* list_locate(const dnode* head_ptr, size_t position) { // precondition: position > 0
	const dnode* cursor = head_ptr;
	assert(position > 0);
	
	for (size_t i = 0; cursor != NULL && i < position; i++)
	{
		cursor = cursor->get_forelink();
	}
	return cursor;
}

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr) {
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

void list_head_remove(dnode*& head_ptr) {
	dnode* remove_ptr = head_ptr;
	
	if (head_ptr == NULL) return;

	head_ptr = head_ptr->get_forelink();
	if(head_ptr != NULL) head_ptr->set_backlink(NULL);
	
	delete remove_ptr;
}

void list_remove(dnode* previous_ptr) {
	if (previous_ptr == NULL) return;

	dnode* remove_ptr = previous_ptr->get_forelink();

	remove_ptr->get_forelink()->set_backlink(previous_ptr);
	previous_ptr->set_forelink(remove_ptr->get_forelink());
	
	delete remove_ptr;
}

void list_clear(dnode*& head_ptr) {
	while (head_ptr != NULL) {
		list_head_remove(head_ptr);
	}
}

bag::bag(){
	head_ptr = NULL;
	many_nodes = 0;
}

bag::bag(const bag& source){
	dnode* tail_ptr;
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

bag::~bag() {
	list_clear(head_ptr);
	many_nodes = 0;
}

void bag::operator =(const bag& source){
	dnode* tail_ptr;
	if (this == &source) return;

	list_clear(head_ptr);
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

void bag::operator +=(const bag& addend){
	dnode* copy_head_ptr;
	dnode* copy_tail_ptr;
	if (addend.many_nodes > 0) {
		list_copy(addend.head_ptr, copy_head_ptr, copy_tail_ptr);

		copy_tail_ptr->set_forelink(head_ptr);
		head_ptr->set_backlink(copy_tail_ptr);

		head_ptr = copy_head_ptr;
		many_nodes += addend.many_nodes;
	}
}

//bool bag::operator ==(const bag& source){}
//bool bag::operator !=(const bag& source){}
void operator +(const bag& source){}

//bool bag::erase_one(const bag::value_type& target){}

//bag::size_type bag::count(const bag::value_type& target) const{}
//bag::value_type bag::grab(){}

void bag::show_content(){
	dnode* ptr = head_ptr;
	while (true) {
		cout << ptr->get_data();
		if ((ptr = ptr->get_forelink()) == NULL) break;
		cout << "<=>";
	}
	cout << endl;
}

void bag::insert(const bag::value_type& entry){
	list_head_insert(head_ptr, entry);
	many_nodes++;
}

void bag::sort(){}

int main() {
	bag b1;
	b1.insert(1.5);
	b1.insert(1.5);
	b1.insert(1.5);
	b1.insert(1.5);
	b1.insert(1.5);
	b1.show_content();
	bag b2(b1);
	b2.show_content();
	bag b3 = b2;
	b3.show_content();
}