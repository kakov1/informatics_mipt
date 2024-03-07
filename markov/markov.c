#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TAPE 2048
#define MAX_RP 128
#define MAX_LINE 256

typedef struct _rule {
	char lhs[MAX_RP];
	char rhs[MAX_RP];
	int final;
	struct _rule* next;
} Rule;

Rule* rules = NULL;
char* tape = "";

int eval(Rule* r) {
	if ( !r ) return -1;
	char *pos = strstr(tape, r->lhs);
	if ( !pos ) return eval(r->next);
	char* newtape = malloc(MAX_TAPE);
	snprintf(newtape, MAX_TAPE, "%.*s%s%s", (int)(pos-tape), tape, r->rhs, pos+strlen(r->lhs));
	tape = (free(tape), newtape);
	if ( r->final ) return printf("Finished\n");
	return 0;
}
char copy_upto(char* d, char** s, char* sep) {
	for(; **s && !strchr(sep, **s); d++, (*s)++) *d = **s;
	*d = 0;
	return *((*s)++);
}

int read_rule(char* l, Rule** r, int n) {
	char s;
	*r = calloc(sizeof(Rule), 1);
	s = copy_upto((*r)->lhs, &l, "|@");
	if (!s) return (free(*r), -printf("Incomplete rule at line %d\n", n));
	copy_upto((*r)->rhs, &l, "\n");
	(*r)->final  = s=='@';
	printf("Rule '%s' %c => '%s'\n", (*r)->lhs, s, (*r)->rhs);
	return 0;
}

int read_rules(FILE* f){
	char line[MAX_LINE];
	Rule **n; 
	int k;
	for(k = 0, n = &rules; fgets(line, MAX_LINE, f); n = &(*n)->next, k++)
		if( read_rule(line, n, k) ) return -1;
	return 0;
}	

void free_rules(Rule* r) {
	if(!r) return;
	Rule* n = r->next;
	free(r);
	free_rules(n);
}

int main(int argc, char* argv[]) {
	if ( argc > 2 ) {
		FILE *f = fopen(argv[1], "r");
		if ( !read_rules(f) ) {
			tape = strdup(argv[2]);
			while (!eval(rules)) printf("Tape: %s\n", tape);
			printf("Tape: %s\n", tape);
			free(tape);
			free_rules(rules);
		}
		fclose(f);
	}
}

