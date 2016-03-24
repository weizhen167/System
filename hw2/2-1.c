#include <stdio.h>

int main() {
	int space = 0;
	int other = 0;
	int digits[10];
	int i;
	char x1[100] =
		"The 25 quick brown foxes jumped over the 27 lazy dogs 17 times.";
	for (i = 0; i < 10; i++) {
		*(digits + i) = 0;
	}
	i = 0;
	while (*(x1 + i) != '\0') {
		char c = *(x1 + i);
		if (c >= '0' && c <= '9') ++*(digits + (c - '0'));
		if (c == ' ' || c == '\n' || c == '\t') {
			space++;
		}
		else {
			other++;
		}
		i++;
	}
	
	printf("Problem2 method1.\n\n");
	printf("Input: The 25 quick brown foxes jumped over the 27 lazy dogs 17 times.\n\n\n");

	printf("Output: there were %d space and %d other char in the sentence\n\n", space, other);

	printf("#### count of digits #### \n\n");
	printf("    | digit | count |\n");
	printf("    +---------------+\n");
	for (i = 0; i < 10; i++) {
		printf("    |   %d   |   %d   |\n", i, *(digits + i));
		printf("    +---------------+\n");
	}
	return 0;
}