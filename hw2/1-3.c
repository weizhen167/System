#include <stdio.h>
#define IN   1  /* inside a word */
#define OUT  0  /* outside a word */

int main() {
	int line = 0;
	int word = 0;
	int characters = 0;
	int i;
	char x1[100] =
		"The quick brown fox jumped over the lazy dog.";
	char *pointer = x1;
	int state = OUT;
	i = 0;
	
	while (*pointer != '\0') {
		if (line == 0) line++;
		char c = *pointer;
		if ((c == ' ' || c == '\n' || c == '\t')) {
			state = OUT;
		}
		if (state == OUT) {
			state = IN;
			word++;
		}
		if (c == '\n') line++;
		characters++;
		pointer++;
	}

	printf("Problem1 method3.\n\n");
	printf("Input: The quick brown fox jumped over the lazy dog.\n\n\n");
	printf("Output: there were %d line(s), %d word(s) and %d character(s) in the sentence\n\n", line, word, characters);
	return 0;
}