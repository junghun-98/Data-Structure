#include "StackApp.h"
#include <iostream>
#include <ctype.h>

using namespace std;

int main() {
	evaluator eva;
	string result = eva.read_expression();	
	result = eva.convert_to_postfix(result);
	cout << result;
	return 0;
}