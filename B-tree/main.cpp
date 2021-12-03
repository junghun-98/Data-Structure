#include "set.h"

int main() {
	set<int> s;

	s.insert(6);
	s.insert(10);
	s.insert(8);
	s.insert(2);
	s.insert(4);
	s.insert(3);
	s.insert(0);
	s.insert(1);
	s.insert(5);
	s.insert(7);
	s.insert(9);
	s.insert(14);
	s.insert(12);
	s.insert(11);
	s.insert(15);
	s.insert(16);
	s.insert(13);

	s.show_contents(0);
	

	
	return 0;
}