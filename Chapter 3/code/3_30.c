#include <stdio.h>
#include <stdlib.h>

int main() {
	int lv;
	int* gv;

	lv = 1;
	gv = (int*)malloc(0x4);
	*gv = 2;

	printf("lv is %d\n", lv);
	printf("gv is %d\n", *gv);

	return 0;

}