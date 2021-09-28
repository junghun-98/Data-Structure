#include "tree.h"
#include <iostream>
#include <set>

using namespace std;

int main()
{
    int a, b;
    printf("Enter two values including negative number to operate  : ");
    scanf_s("%d %d", &a, &b);

    if (b > 0) {
        while (b > 0) {
            a++;
            b--;
        }
    }
    if (b < 0) { // when 'b' is negative
        while (b < 0) {
            a--;
            b++;
        }
    }
    printf("a = %d", a);
    return 0;
}

