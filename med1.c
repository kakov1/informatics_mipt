#include<stdio.h>
#include<stdlib.h>

typedef struct _List {
	double x;
	struct _List* next;
} List;

int print(List* nums) {
	List* k;
	for (k = nums; k != NULL; k = k->next) {
		printf("%lf\n", k->x);
	}
	return 0;
}

double find_elem(List* list, int n) {
	while (n != 0) {
		list = list->next;
		n--;
	}
	return list->x;
}

int main() {
	List* nums = NULL;
	List* prev = NULL;
	List* new = NULL;
	double num;
	int count = 0;
	while (scanf("%lf", &num) == 1) { 
		new = malloc(sizeof(List));
		*new = (List) { num, nums};
		nums = new;
		prev = NULL;
		List* buf;
		while (new->next != NULL && new->x < new->next->x) {
			if (prev != NULL) {
				prev->next = new->next;
			}
			else {
				nums = new->next;
			}
			prev = new->next;

			buf = new->next->next;
			new->next->next = new;
			new->next = buf;

		}
		count++;
	}
	printf("Медиана:");
	if (count % 2) {
		printf("%lf\n", find_elem(nums, count / 2));
	}
	else {
		printf("%lf\n", (find_elem(nums, count / 2) + find_elem(nums, (count - 1) / 2))/2);
	}
	return 0;
}