#pragma once
#include <iostream>
#include <cassert>
#include <time.h>
#include <algorithm>

using namespace std;

/*Doubly Linked List�� �̷�� �⺻ ���� dnode */
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
// postcondition: ���ڷ� ���޵� �����Ͱ� ����Ű�� ����Ʈ�� node���� ��ȯ

void list_head_insert(dnode*& head_ptr, const dnode::value_type& entry);
// postcondition: ���ڷ� ���޵� head_ptr�� ����Ű�� list�� head �κп� data�� ���� entry�� ���� node�� ����

void list_insert(dnode* previous_ptr, const dnode::value_type& entry);
// postcondition: ���ڷ� ���޵� previous_ptr ���� �ڸ��� data�� ���� entry�� ���� node�� ����

const dnode* list_search(const dnode* head_ptr, const dnode::value_type& target);
dnode* list_search(dnode* head_ptr, const dnode::value_type& target);
// postcondition: ���ڷ� ���޵� head_ptr�� ����Ű�� �ִ� list�� �˻��Ͽ� target�� ��ġ�ϴ� data�� ���� ���θ�
//				  �Ǵ��ϰ� ���� �Ѵٸ� �ش� node�� �����͸� ��ȯ (��, �������� ������ NULL ������ ��ȯ)

const dnode* list_locate(const dnode* head_ptr, size_t position);
dnode* list_locate(dnode* head_ptr, size_t position);
// precondition: position > 0
// postcondition: head_ptr�� ����Ű�� list���� ���ڷ� ���޵� position�� �ش��ϴ� ��ġ�� node pointer ��ȯ
//				  (��, �������� ������ NULL ������ ��ȯ)

void list_copy(const dnode* source_ptr, dnode*& head_ptr, dnode*& tail_ptr);
// postcondition: source_ptr�� ����Ű�� �ִ� list�� head_ptr�� tail_ptr�� ����

void list_head_remove(dnode*& head_ptr);
// postcondition: ���ڷ� ���޵� head_ptr�� ����Ű�� list�� head node�� ����

void list_remove(dnode* previous_ptr);
// postcondition: ���ڷ� ���޵� previous_ptr�� ����Ű�� node ���� node ����

void list_clear(dnode*& head_ptr);
// postcondition: list clear, �������� �Ҵ�� recource(nodes) ��ȯ


//Doubly Linked List�� �̿��� data�� �����ϴ� bag class
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
    // postcondition: �� bag class�� �����ϰ� �ִ� data�� ���ϴ� ������
	//				  (data�� ������ ������� �ʴ´�.)

	bool erase_one(const value_type& target);
	// postcondition: bag class�� ����� data�� �����Ͽ� target���� ���� data�� ����
	//				 node�� �߰��ϴ� ��� ���� �� head node�� data�� ��ü

	size_type size() { return many_nodes; }
	size_type count(const value_type& target) const;
	// postcondition: bag class�� ����� data�� �����Ͽ� target���� ���� data�� ����
	//				 node�� ���� ��ȯ

	value_type grab();
	// precondition: size() > 0
	// postcondition: bag class�� ����� data�� �� �������� �ƹ� data�� ��ȯ

	void show_content();
	// postcondition: bag class�� ����� data�� head���� tail���� ���
 	
	void show_content_reverse();
	// postcondition: bag class�� ����� data�� tail���� head���� ���

	void insert(const value_type& entry);
	// postcondition: ���ڷ� ���޵� entry�� ���� data�� ���� node�� head�� ����

	void sort();
	// postcondition: bag class�� data�� ������������ ���� 
private:
	dnode* head_ptr;
	dnode* tail_ptr;
	size_type many_nodes;
};