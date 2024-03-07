#include <stdio.h>
#include <stdlib.h>

typedef struct _list
{
	double x;
	struct _list *next;
	int num;
} list;

list *divideList(list *p)
{
	list *q, *start2;

	q = p->next->next;
	while (q != NULL && q->next != NULL)
	{
		p = p->next;
		q = q->next->next;
	}

	start2 = p->next;
	p->next = NULL;
	return start2;
}

list *merge(list *p1, list *p2)
{
	list *startM, *pM;

	if (p1->x < p2->x)
	{
		startM = p1;
		p1 = p1->next;
	}
	else
	{
		startM = p2;
		p2 = p2->next;
	}
	pM = startM;
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->x < p2->x)
		{
			pM->next = p1;
			pM = pM->next;
			p1 = p1->next;
		}
		else
		{
			pM->next = p2;
			pM = pM->next;
			p2 = p2->next;
		}
	}
	if (p1 == NULL)
	{
		pM->next = p2;
	}
	else
	{
		pM->next = p1;
	}
	return startM;
}

list *mergeSort(list *start)
{
	list *start1, *start2, *startM;

	if (start == NULL || start->next == NULL)
	{
		return start;
	}

	start1 = start;
	start2 = divideList(start);
	start1 = mergeSort(start1);
	start2 = mergeSort(start2);
	startM = merge(start1, start2);
	return startM;
}

int main()
{
	list *nums = NULL;
	list *x;

	double a;
	int count = 1;

	while (scanf("%lf", &a) == 1)
	{
		list *new = malloc(sizeof(list));
		*new = (list){a, nums, count};
		nums = new;
		count++;
	}
	nums = mergeSort(nums);
	for (x = nums; x != NULL; x = x->next)
	{
		printf("%lf %i\n", x->x, x->num);
	}
	return 0;
}