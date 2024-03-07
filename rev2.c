#include <stdio.h>

int print(int letter) {
	if (letter != ' ') {
		putchar(letter);
		print(getchar());
	}
	else {
		return 0;
	}
}

int reverse(int letter, int counter) {
	if (letter == '.') {
		ungetc(' ', stdin);
		return 0;
	}
	else {
		reverse(getchar(), counter + 1);
		if (letter == ' ' || counter == 0) {
			print(getchar());
			if (counter == 0) {
				putchar('.');
			}
			else {
				putchar(' ');
			}
			ungetc(' ', stdin);
		}
		else ungetc(letter, stdin);
	}
}

int main() {
	reverse(' ', 0);
	getchar();
	if (getchar()!= '\n') {
		putchar(' ');
		main();
	}
	putchar('\n');
	return 0;
}
