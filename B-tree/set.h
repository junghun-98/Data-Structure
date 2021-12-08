#pragma once
//B-tree�� �̿��� set�ڷᱸ���� ������ ��������Դϴ�.
#include <iostream>
#include <iomanip>

using namespace std;

/*

***** set class *****

*/
template<class item>
class set {
public:
	set();	
	~set() { clear(); }

	int count(const item& target);
	//postcondition : target�� ��ġ�ϴ� ���� set���ο� �����ϸ� 1, �׷��� ������ 0�� ��ȯ
	bool insert(const item& entry);
	//postcondition : entry�� �̹� set�� �����ϸ� false, �׷��� �ʴٸ� set������ ������ ���� �� true ��ȯ
	bool erase(const item& target);
	//postcondiotion : target�� set�� �����ؼ� ���� �����ϸ� ���� �� true, ���� ���� ������ false ��ȯ
	void show_contents(int depth = 0);
	//postcondition : set�� �����͸� B-tree �������� ���
private:
	//���� & ���
	static const size_t MINIMUM = 1;
	static const size_t MAXIMUM = 2 * MINIMUM;

	size_t data_count;
	item data[MAXIMUM + 1];
	
	size_t child_count;
	set* subset[MAXIMUM + 2];
	
	//�Լ�
	
	bool loose_insert(const item& entry);
	//postcondiotion : set�� B-tree�� ������ ��� �����ϸ鼭 �����͸� ���԰���
	void fix_excess(size_t i);
	//postcondiotion : MAXIMUM+1 �׸��� �ִ� ��带 ���� MINIMUM �׸��� ���Ե� �� ���� ���� ����,
	//				   ��� ��� ��ġ�� �����͸� �θ� ����� ������ �迭�� �ø�.
	
	bool loose_erase(const item& target);
	//postcondiotion : set�� B-tree�� ������ ��� �����ϸ鼭 �����͸� ���Ű���
	void fix_shortage(size_t i);
	//postcondiotion : MINIMUM-1 �׸��� �ִ� ��带 MINIMUM ���ǿ� �µ��� B-tree������ ����
	//				   1. �̿��� ����� �����Ϳ� �θ����� ������ ���� ����
	//				   2. �ΰ��� ��� ���� 
	void remove_biggest(item& removed_entry);
	//postcondition : B-tree�������� �ִ��� removed_entry�� ���� �� ����
	void to_zero(set* source) { source->data_count = 0; source->child_count = 0; }
	//�Ҹ��� ȣ���� �����ϰ� �����ϱ� ���� ���� �Լ�
	void clear();
	//postcondition : �Ҵ���� ������ �޸� û��
	bool is_leaf() { return (child_count == 0); }

	void copy_node(set* source);
	//postcondition : ��Ʈ����� ������ source�� ����
};

//class member function ����

//public
template<class item>
set<item>::set() {
	data_count = 0;
	child_count = 0;

	data[MAXIMUM + 1] = { 0, };
}

template<class item>
void set<item>::clear() {
	if (child_count != 0) {
		for (int i = 0; i < child_count; i++) {
			subset[i]->clear();
			
			to_zero(subset[i]);
			delete subset[i];
		}
	}
}

template<class item>
int set<item>::count(const item& target) {
	int i;
	if (data_count == 0) return 0;

	for (i = 0; i < data_count; i++) {
		if (data[i] >= target) break;
	}

	if (data[i] == target) return 1;

	else if (child_count == 0) return 0;

	else {
		return subset[i]->count(target);
	}
}

template<class item>
void set<item>::fix_excess(size_t i) {
	set<item>* ptr1 = new set<item>();
	set<item>* ptr2 = new set<item>();
	set<item>* remove_ptr = subset[i];

	item center_data = subset[i]->data[MINIMUM];
	ptr1->data_count = MINIMUM;
	ptr2->data_count = MINIMUM;

	//data ����
	for (int j = 0; j < MINIMUM; j++) {
		ptr1->data[j] = subset[i]->data[j];
	}

	for (int j = MINIMUM + 1; j < MAXIMUM + 1; j++) {
		ptr2->data[j - (MINIMUM + 1)] = subset[i]->data[j];
	}

	//subset ����
	if (subset[i]->child_count != 0) {
		for (int j = 0; j <= MINIMUM; j++) {
			ptr1->subset[j] = subset[i]->subset[j];
		}

		for (int j = MINIMUM + 1; j < subset[i]->child_count; j++) {
			ptr2->subset[j - (MINIMUM+1)] = subset[i]->subset[j];
		}
		
		ptr1->child_count = MINIMUM + 1;
		ptr2->child_count = MINIMUM + 1;
	}

	//������ ������ ���� data[i]���� �ڿ� ��ġ�� �����͵��� �ڸ��� �Ű��ش�. 
	int index = i;
	if (data_count != 0) {
		for (int j = data_count - 1; j >= index; j--) {
			data[j + 1] = data[j];
		}
	}

	//subset node ������ ���� subset[i]���� �ڿ� ��ġ�� �����͵��� �ڸ��� �Ű��ش�. 
	if (child_count != 0) {
		for (int j = child_count; j > i + 1; j--) {
			subset[j] = subset[j - 1];
		}
	}

	//data insert
	data[i] = center_data;
	data_count++;

	//child insert
	subset[i] = ptr1;
	subset[i + 1] = ptr2;
	child_count++;

	//remove node
	to_zero(remove_ptr);
	delete remove_ptr;
}

template<class item>
bool set<item>::loose_insert(const item& entry) {
	int i;
	if (data_count == 0) {
		data[0] = entry;
		data_count++;
		return true;
	}

	for (i = 0; i < data_count; i++) {
		if (data[i] >= entry) break;
	}

	if (data[i] == entry) return false;

	else if (child_count == 0) {
		for (int j = data_count - 1; j >= i; j--) {
			data[j + 1] = data[j];
		}
		data[i] = entry;
		data_count++;

		return true;
	}

	else {
		bool b = subset[i]->loose_insert(entry);

		if (subset[i]->data_count > MAXIMUM) {
			fix_excess(i);
		}

		return b;
	}
}

template<class item>
void set<item>::copy_node(set* source) {
	for (int i = 0; i < data_count; i++) {
		source->data[i] = data[i];
	}
	for (int i = 0; i < child_count; i++) {
		source->subset[i] = subset[i];
	}
	source->data_count = data_count;
	source->child_count = child_count;
}

template<class item>
bool set<item>::insert(const item& entry) {
	if (!loose_insert(entry)) return false;
	
	if (data_count > MAXIMUM) {
		set<item>* new_set = new set<item>();
		copy_node(new_set);

		subset[0] = new_set;
		child_count = 1;
		fill_n(data, MAXIMUM + 1, 0);
		data_count = 0;
		fix_excess(0);
	}

	return true;
}


template<class item>
void set<item>::show_contents(int depth) {
	
	if (data_count != 0) {
		for (int i = data_count; i >= 0; i--) {
			if (child_count != 0) {
				subset[i]->show_contents(depth + 1);
			}
			if (i != 0) {
				cout << setw(4 * depth) << data[i - 1] << endl;
			}
		}
	}
}

template<class item>
bool set<item>::erase(const item& target) {
	if (!loose_erase(target)) return false;

	if (data_count == 0 && child_count == 1) {
		for (int i = 0; i < subset[0]->data_count; i++) {
			data[i] = subset[0]->data[i];
		}
		data_count = subset[0]->data_count;

		set<item>* temp = subset[0];
		for (int i = 0; i < subset[0]->child_count; i++) {
			subset[i] = temp->subset[i];
		}
		child_count = temp->child_count;
		
		to_zero(temp);
		delete temp;
	}

	return true;
}

template<class item>
bool set<item>::loose_erase(const item& target) {
	int i;
	if (data_count == 0) return false;

	for (i = 0; i < data_count; i++) {
		if (data[i] >= target) break;
	}

	if (child_count == 0 && i == data_count) return false;

	if (child_count == 0 && data[i] == target) {
		for (int j = i; j < data_count - 1; j++) {
			data[j] = data[j + 1];
		}
		data_count--;
		return true;
	}

	else {
		if (i == data_count || data[i] != target) {
			bool b = subset[i]->loose_erase(target);
			if (!b) return false;

			if (subset[i]->data_count < MINIMUM) {
				fix_shortage(i);
				return true;
			}
		}

		else if (data[i] == target) {
			subset[i]->remove_biggest(data[i]);

			if (subset[i]->data_count < MINIMUM) {
				fix_shortage(i);
			}
			return true;
		}
	}
}

template<class item>
void set<item>::fix_shortage(size_t i) {
	if (i != 0 && subset[i - 1]->data_count > MINIMUM) {
		for (int j = subset[i]->data_count - 1; j >= 0; j--) {
			subset[i]->data[j + 1] = subset[i]->data[j];
		}

		subset[i]->data[0] = data[i - 1];
		data[i - 1] = subset[i - 1]->data[subset[i - 1]->data_count - 1];
		subset[i - 1]->data_count--;
		subset[i]->data_count++;

		if (subset[i - 1]->child_count != 0) {
			for (int j = subset[i]->child_count; j >= 0; j--) {
				subset[i]->subset[j + 1] = subset[i]->subset[j];
			}

			subset[i]->subset[0] = subset[i - 1]->subset[subset[i - 1]->child_count - 1];
			subset[i - 1]->subset[subset[i - 1]->child_count - 1] = NULL;
			subset[i - 1]->child_count--;
			subset[i]->child_count++;
		}
	}

	else if(i != data_count && subset[i + 1]->data_count > MINIMUM){
		subset[i]->data[subset[i]->data_count] = data[i];
		data[i] = subset[i + 1]->data[0];

		for (int j = 0; j < subset[i + 1]->data_count - 1; j++) {
			subset[i + 1]->data[j] = subset[i + 1]->data[j + 1];
		}
		
		subset[i + 1]->data_count--;
		subset[i]->data_count++;

		if (subset[i + 1]->child_count != 0) {
			
			subset[i]->subset[child_count] = subset[i + 1]->subset[0];
			
			for (int j = 0; j < subset[i + 1]->child_count; j++) {
				subset[i + 1]->subset[j] = subset[i + 1]->subset[j + 1];
			}
			
			subset[i + 1]->child_count--;
			subset[i]->child_count++;
		}
	}

	else if (i != 0 && subset[i - 1]->data_count == MINIMUM) {
		subset[i - 1]->data[subset[i - 1]->data_count] = data[i - 1];
		data_count--;
		subset[i - 1]->data_count++;

		for (int j = 0; j < subset[i]->data_count; j++) {
			subset[i - 1]->data[subset[i - 1]->data_count + j] = subset[i]->data[j];
		}
		subset[i - 1]->data_count += subset[i]->data_count;

		for (int j = 0; j < subset[i]->child_count; j++) {
			subset[i - 1]->subset[subset[i - 1]->child_count + j] = subset[i]->subset[j];
		}
		subset[i - 1]->child_count += subset[i]->child_count;

		to_zero(subset[i]);
		delete subset[i];
		child_count--;
	}

	else if (i != data_count && subset[i + 1]->data_count == MINIMUM) {
		subset[i]->data[subset[i]->data_count] = data[i];
		data_count--;
		subset[i]->data_count++;

		for (int j = 0; j < subset[i + 1]->data_count; j++) {
			subset[i]->data[subset[i]->data_count + j] = subset[i + 1]->data[j];
		}
		subset[i]->data_count += subset[i + 1]->data_count;

		for (int j = 0; j < subset[i + 1]->child_count; j++) {
			subset[i]->subset[subset[i]->child_count + j] = subset[i + 1]->subset[j];
		}
		subset[i]->child_count += subset[i + 1]->child_count;

		to_zero(subset[i + 1]);
		delete subset[i + 1];
		child_count--;
	}
}

template<class item>
void set<item>::remove_biggest(item& removed_entry) {
	if (child_count == 0) {
		removed_entry = data[data_count - 1];
		data_count--;
	}
	else {
		subset[child_count - 1]->remove_biggest(removed_entry);

		if (subset[child_count - 1]->data_count < MINIMUM) {
			fix_shortage(child_count - 1);
		}
	}
}