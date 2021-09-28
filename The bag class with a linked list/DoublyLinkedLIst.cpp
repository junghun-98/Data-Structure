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
	if (head_ptr == NULL) { //Insert data to empty list
		head_ptr = new dnode(entry);
	}
	else{
		dnode* temp_ptr;

		temp_ptr = head_ptr;
		head_ptr = new dnode(entry, head_ptr, NULL);
		temp_ptr->set_backlink(head_ptr);
	}
}

void list_insert(dnode* previous_ptr, const dnode::value_type& entry) {
	dnode* insert_ptr = new dnode(entry, previous_ptr->get_forelink(), previous_ptr);

	previous_ptr->set_forelink(insert_ptr);

	if (insert_ptr->get_forelink() != NULL) { //Insert data between two dnodes
		insert_ptr->get_forelink()->set_backlink(insert_ptr);
	}
	//else NULL -> Insert data between tail dnodes
}

dnode* list_search(dnode* head_ptr, const dnode::value_type& target) {
	dnode* cursor = head_ptr;

	while (cursor != NULL)
	{
		if (cursor->get_data() == target)
			return cursor;
		cursor = cursor->get_forelink();
	}
	return NULL;
}

const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target) {
	const dnode* cursor = head_ptr;

	while (cursor != NULL)
	{
		if (cursor->get_data() == target)
			return cursor;
		cursor = cursor->get_forelink();
	}
	return NULL;
}

dnode* list_locate(dnode* head_ptr, size_t position) {
	dnode* cursor = head_ptr;
	assert(position > 0);

	for (size_t i = 1; (cursor != NULL && i < position); i++)
	{
		cursor = cursor->get_forelink();
	}
	return cursor;
}

const dnode* list_locate(const dnode* head_ptr, size_t position) { // precondition: position > 0
	const dnode* cursor = head_ptr;
	assert(position > 0);
	
	for (size_t i = 1; (cursor != NULL && i < position); i++)
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
	
	head_ptr = head_ptr->get_forelink();
	if(head_ptr != NULL) head_ptr->set_backlink(NULL);
	
	delete remove_ptr;
}

void list_remove(dnode* previous_ptr) {
	if (previous_ptr == NULL) return;

	dnode* remove_ptr = previous_ptr->get_forelink();

	if (remove_ptr->get_forelink() != NULL) { //Remove dnode between other dnodes (not tail dnodes)
		remove_ptr->get_forelink()->set_backlink(previous_ptr);
		previous_ptr->set_forelink(remove_ptr->get_forelink());
	}
	
	delete remove_ptr;
}

void list_clear(dnode*& head_ptr) {
	while (head_ptr != NULL) {
		list_head_remove(head_ptr);
	}
}

bag::bag(){
	head_ptr = NULL;
	tail_ptr = NULL;
	many_nodes = 0;
}

bag::bag(const bag& source) {
	list_copy(source.head_ptr, head_ptr, tail_ptr);
	many_nodes = source.many_nodes;
}

bag::~bag() {
	list_clear(head_ptr);
	many_nodes = 0;
}

void bag::operator =(const bag& source){
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

		if (head_ptr == NULL) {
			head_ptr = copy_head_ptr;
			tail_ptr = copy_tail_ptr;
		}
		else {
			copy_tail_ptr->set_forelink(head_ptr);
			head_ptr->set_backlink(copy_tail_ptr);

			head_ptr = copy_head_ptr;
		}
		many_nodes += addend.many_nodes;
	}
}

bool bag::operator ==(const bag& source){
	dnode* fore_bag;

	fore_bag = head_ptr;

	if (many_nodes != source.many_nodes) return false;

	while (fore_bag != NULL)
	{
		value_type target = fore_bag->get_data();

		if (count(target) != source.count(target)) {
			return false;
		}
		fore_bag = fore_bag->get_forelink();
	}

	return true;
}

bool bag::operator !=(const bag& source){
	dnode* fore_bag;

	fore_bag = head_ptr;

	if (many_nodes != source.many_nodes) return true;

	while (fore_bag != NULL)
	{
		value_type target = fore_bag->get_data();

		if (count(target) != source.count(target)) {
			return true;
		}
		fore_bag = fore_bag->get_forelink();
	}

	return false;
}

bag operator +(bag& addend1, bag& addend2){
	bag temp;

	temp += addend2;
	temp += addend1;

	return temp;
}

bool bag::erase_one(const bag::value_type& target){
	dnode* target_ptr;

	target_ptr = list_search(head_ptr, target);
	if (target_ptr == NULL) return false;

	target_ptr->set_data(head_ptr->get_data());
	list_head_remove(head_ptr);
	many_nodes--;
	
	return true;
}

bag::size_type bag::count(const bag::value_type& target) const{
	size_type answer = 0;
	const dnode* cursor;
	cursor = list_search(head_ptr, target);
	while (cursor != NULL) {
		answer++;
		cursor = cursor->get_forelink();
		cursor = list_search(cursor, target);
	}
	return answer;
}

bag::value_type bag::grab(){
	srand(time(NULL));

	size_type i;
	const dnode* cursor;

	assert(size() > 0);

	i = (rand() % size()) + 1;
	cursor = list_locate(head_ptr, i);

	return cursor->get_data();
}

void bag::show_content(){
	if (head_ptr == NULL) return;
	dnode* ptr = head_ptr;

	while (true) {
		cout << ptr->get_data();
		if ((ptr = ptr->get_forelink()) == NULL) break;
		cout << " <=> ";
	}
	cout << endl;
}

void bag::show_content_reverse() {
	if (tail_ptr == NULL) return;
	dnode* ptr = tail_ptr;
	
	while (true) {
		cout << ptr->get_data();
		if ((ptr = ptr->get_backlink()) == NULL) break;
		cout << " <=> ";
	}
	cout << endl;
}

void bag::insert(const bag::value_type& entry){
	list_head_insert(head_ptr, entry);

	if (many_nodes == 0) { //insert data to empty list
		tail_ptr = head_ptr;
	}

	many_nodes++;
}

void bag::sort(){
	dnode* temp_ptr;
	dnode* compare_ptr = head_ptr;
	value_type temp;

	while (compare_ptr != NULL) {
		temp_ptr = compare_ptr->get_forelink();
		while (temp_ptr != NULL)
		{
			if (compare_ptr->get_data() > temp_ptr->get_data()) { //data swap
				temp = compare_ptr->get_data();
				compare_ptr->set_data(temp_ptr->get_data());
				temp_ptr->set_data(temp);
			}
			temp_ptr = temp_ptr->get_forelink();
		}
		compare_ptr = compare_ptr->get_forelink();
	}
}