#include <stdio.h>

int main() {
	int space = 0;
	int other = 0;
	int digits[10];
	int i;
	char x1[100] =
		"The 25 quick brown foxes jumped over the 27 lazy dogs 17 times.";
	int *pointer1 = digits;
	char *pointer2 = x1;
	for (i = 0; i < 10; i++) {
		*(pointer1 + i) = 0;
	}
	pointer1 = digits;
	while (*pointer2 != '\0') {
		char c = *pointer2;
		if (c >= '0' && c <= '9') ++*(pointer1 + (c - '0'));
		if (c == ' ' || c == '\n' || c == '\t') {
			space++;
		}
		else {
			other++;
		}
		pointer2++;
	}

	pointer1 = digits;
	printf("Problem2 method2.\n\n");
	printf("Input: The 25 quick brown foxes jumped over the 27 lazy dogs 17 times.\n\n\n");

	printf("Output: there were %d space and %d other char in the sentence\n\n", space, other);

	printf("#### count of digits #### \n\n");
	printf("    | digit | count |\n");
	printf("    +---------------+\n");
	for (i = 0; i < 10; i++) {
		printf("    |   %d   |   %d   |\n", i, *pointer1);
		printf("    +---------------+\n");
		pointer1++;
	}
	return 0;
}
