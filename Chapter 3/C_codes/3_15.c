#include <stdio.h>

int main() {
	int lv=0;

	while (true) {
		if (lv == 2) break;

		printf("%x\n", lv);
		lv++;
	}
		return 0;

}