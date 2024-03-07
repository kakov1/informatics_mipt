#include<stdio.h>

int skip(char waitfor) {
    if (waitfor == '\n') return 'f';
    else if (waitfor != '"') return skip(getchar());
    return getchar();
}

int check(char waitfor) {
	int a = getchar();
    if (a == '"') {
        a = skip(' ');
    }
	switch(a) {
	case 'f': return 0;
	case '[': return check(']') && check(waitfor);
	case '(': return check(')') && check(waitfor);
	case '<': return check('>') && check(waitfor);
	case '{': return check('}') && check(waitfor);
	case '}': case '>': case ')': case ']': case '\n': return a == waitfor;
	}										
}

int main() {
	printf("%s\n", check('\n')?"OK":"FALSE");
}