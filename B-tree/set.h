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
	set(const set& source);
	~set() { clear(); };
	int count(const item& target);
	//postcondition : target�� ��ġ�ϴ� ���� set���ο� �����ϸ� 1, �׷��� ������ 0�� ��ȯ
	bool insert(const item& entry);
	//postcondition : entry�� �̹� set�� �����ϸ� false, �׷��� �ʴٸ� set������ ������ ���� �� true ��ȯ
	bool erase(const item& target);
	//postcondiotion : target�� set�� �����ؼ� ���� �����ϸ� ���� �� true, ���� ���� ������ false ��ȯ
	void show_contents(int depth);
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

	void clear();
	//postcondition : �Ҵ���� ������ �޸� û��
	bool is_leaf() { return (child_count == 0); }
};

//class member function ����

//public
template<class item>
set<item>::set() {
	data_count = 0;
	child_count = 0;
}

template<class item>
set<item>::set(const set& source) {
	data_count = source.data_count;
	child_count = source.child_count;
}

template<class item>
void set<item>::clear() {
	if (child_count != 0) {
		for (int i = 0; i < child_count; i++) {
			
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

	for (int j = 0; j < MINIMUM; j++) {
		ptr1->data[j] = subset[i]->data[j];
	}

	for (int j = MINIMUM + 1; j < MAXIMUM + 1; j++) {
		ptr2->data[j - (MINIMUM + 1)] = subset[i]->data[j];
	}

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

	int index = i;
	if (data_count != 0) {
		for (int j = data_count - 1; j >= index; j--) {
			data[j + 1] = data[j];
		}
	}

	if (child_count != 0) {
		for (int j = child_count; j > i + 1; j--) {
			subset[j] = subset[j - 1];
		}
	}

	data[i] = center_data;
	data_count++;

	subset[i] = ptr1;
	subset[i + 1] = ptr2;
	child_count++;

	
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
bool set<item>::insert(const item& entry) {
	if (!loose_insert(entry)) return false;
	
	if (data_count > MAXIMUM) {
		set<item>* new_set = new set<item>();
		for (int i = 0; i < data_count; i++) {
			new_set->data[i] = data[i];
		}
		for (int i = 0; i < child_count; i++) {
			new_set->subset[i] = subset[i];
		}
		new_set->data_count = data_count;
		new_set->child_count = child_count;

		subset[0] = new_set;
		child_count = 1;
		fill_n(data, data_count, 0);
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