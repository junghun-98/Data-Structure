#include "DoublyLinkedLIst.h"
#include <vector>

bag operator +(bag& addend1, bag& addend2) {
	bag temp;

	temp += addend1;
	temp += addend2;

	return temp;
}

//Test case
int main() {
	//constructos
	cout << "*****Test constructors*****\n\n";

	bag b1;
	for (int i = 0; i < 4; i++)
	{
		b1.insert(i);
	}
	cout << "b1 : ";
	b1.show_content();

	bag b2(b1);
	cout << "b2 : "; 
	b2.show_content();

	bag b3 = b2;
	cout << "b3 : ";
	b3.show_content();
	cout << endl;

	//operator
	cout << "*****Test operators*****\n\n";

	b1 += b2;
	cout << "b1 += b2 : ";  
	b1.show_content();

	if (b1 != b2) cout << "b1 != b2\n";
	else cout << "b1 == b2\n";
	
	if (b2 == b3) cout << "b2 == b3\n";
	else cout << "b2 != b3\n";

	bag b4 = b2 + b3;
	cout << "b4 = b2 + b3: "; 
	b4.show_content();
	cout << endl;

	//fucntions
	cout << "*****Test fucntions*****\n\n";

	cout << "before insert data(9) b1 : "; 
	b1.show_content();
	b1.insert(9);
	
	cout << "after insert data(9) b1 : ";  
	b1.show_content();

	cout << endl;

	cout << "before remove data(0) b1 : "; 
	b1.show_content();
	
	b1.erase_one(0);
	cout << "after remove data(0) b1 : "; 
	b1.show_content();

	cout << endl;

	cout << "b1 : ";
	b1.show_content();
	cout << "b1 has 3 : " << b1.count(3) << endl;
	
	cout << "b2 : "; 
	b2.show_content();
	cout << "b2 has 2 : " << b2.count(2) << endl;
	
	cout << "b3 : "; 
	b3.show_content();
	cout << "b3 has 0 : " << b3.count(0) << endl;

	cout << endl;

	cout << "befor sort b1 : ";
	b1.show_content();
	b1.sort();
	cout << "after sort b1 : ";
	b1.show_content();

	cout << "print reverse : ";
	b1.show_content_reverse();

	cout << "grab() b1 :" << b1.grab() << endl;

	//실행 결과를 확인하기 위해 대기
	system("pause");
	
	return 0;
}