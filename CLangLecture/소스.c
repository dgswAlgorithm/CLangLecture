#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int fac(int n) {
	if (n == 0)
		return 1;
	else
		return n * fac(n - 1);
}
int main() {
	printf("%d", fac(10));
	return 0;
}