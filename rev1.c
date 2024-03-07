#include <stdio.h>

int reverse(int letter, int counter) {
	if (letter == '.') {
		return '.';
	}
	if (letter != '.' && letter != ' ') {
		if (reverse(getchar(), counter + 1) == '.') {
			putchar(letter);
			if (counter == 0) {
				putchar('.');
			}
			return '.';
		}
		putchar(letter);
		if (counter == 0) {
			putchar(' ');
			reverse(getchar(), 0);
		}
		return 0;
	}
}

int main() {
	reverse(getchar(), 0);
	if (getchar() != '\n') {
		putchar(' ');
		main();
	}
	putchar('\n');
	return 0;
}
