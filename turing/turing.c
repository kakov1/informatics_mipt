#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TAPE 2048
#define MAX_LINE 1024

typedef struct _rule {
	char read;
	char state;
	char write;
	char newstate;
	char dir;
	struct _rule* next;
} Rule;

Rule* rules;
char tape[MAX_TAPE];
int pos;
char state;

#define UPOS(p) (p<0?(-p)*2-1:p*2)
int print_tape() {
	for (int p = pos-10; p < 40; p++ ) (p ==pos?putchar('>'):1) && putchar(tape[UPOS(p)]);
	return !putchar('\n');
}
int step(Rule* r) {
	state =  r->newstate;
	tape[UPOS(pos)]  = r->write;
	pos += r->dir == '>'?1:-1;
	print_tape();
	if (2*pos > MAX_TAPE || -2*pos > MAX_TAPE)  return -printf("Pos %d Out of tape\n", pos);
	return 0;
}

int find(Rule* r, char s) {
	if ( !r )  return -printf("No rule found for '%c' and state '%c'\n", s, state);
	if ( r->read == s && state == r->state) return step(r);
	return find(r->next, s);
}

void copy_tape(char* d, char* s) {
	for ( ;*s && *s != '\n'; s++, d+=2  ) *d = *s;
}
void read_pos(char* s, int* p) {
	for(*p = 0; *s && *s != '\n'; s++, (*p)++) if ( *s == '^' ) return ;
	*p = 0;
}

int parse_tape(FILE* f) {
	char tp[MAX_TAPE];
	if ( !fgets(tp, MAX_TAPE, f) ) return -printf("At least one line should present\n");
	copy_tape(tape, tp);
	if ( fgets(tp, MAX_TAPE, f) ) read_pos(tp, &pos);
	return 0;	
}

int read_tape(char* fname) {
	FILE* f = fopen(fname, "r");
	if ( !f ) return -printf("Cannot open tape file %s\n", fname);
	int err = parse_tape(f);
	fclose(f);
	return err;
}

int parse_prog(FILE* f) {
	char line[MAX_LINE];
	while (fgets(line, MAX_LINE, f)) {
		if (line[0] == '#') continue;
		Rule* r  = malloc(sizeof(Rule));
		*r = (Rule){line[0], line[1], line[2], line[3], line[4], rules};
		rules = r;
		if(!state) state = line[1]; 
	}
	if (!rules) return -printf("Empty list of rules!\n");
	return 0;
}

int read_prog(char* fname) {
	FILE* f = fopen(fname, "r");
	if ( !f ) return -printf("Cannot open file %s\n", fname);
	int err = parse_prog(f);
	fclose(f);
	return err;
}

int interp() {
	return find(rules, tape[UPOS(pos)]) || interp();
}

int main(int argc, char* argv[]) {
	pos = 0;
	rules = NULL;
	state = 0;
	memset(tape, ' ', sizeof(tape));
	if ( argc < 3 ) return -printf("Usage: %s <tapefile> <progfile>\n", argv[0]);
	if ( !read_tape(argv[1]) && ! read_prog(argv[2]) && !interp() ) return print_tape();
	return -1;
}
