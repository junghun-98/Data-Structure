#include "StackApp.h"
#include <iostream>
#include <ctype.h>

using namespace std;

int main() {

	while(1)
	{
		evaluator eva;
		string option;
		cout << "choose option 1 or 2(1 is start, 2 is exit):";
		cin >> option;
		if (option == "1") {
			cout << endl;
			string result = eva.read_expression();
			cout << endl;

			cout << "convert_to_postfix: ";
			result = eva.convert_to_postfix(result);
			cout << result << endl << endl;

			cout << endl << "result: " << eva.evaluate_postfix(result) << endl;
		}
		else {
			cout << "You input invalid option!\n";
		}
		cout << endl;
	} 

	return 0;
}
