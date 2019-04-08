#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct node {
	struct node *next;
	int value;
};

void print_list(struct node *h)
{
	int max_len = 10;
	int i;
	for (i = 0; h!=NULL && i < max_len; h=h->next, i++)	{
		printf("%4d", h->value);
	}
	printf("\n");
}

struct node *merge_list(struct node *h1, struct node *h2)
{
	struct node *k1, *p1, *k2, *p2, *h;
	if (h1 == NULL)	return h2;
	if (h2 == NULL)	return h1;
	
	p1 = k1 = h1;
	p2 = k2 = h2;
	if (h1->value <= h2->value)	{
		h = h1;
	} else {
		h = h2;
	}
	// keep p1->next = k1; p2->next = k2;
	while (1)	{
		print_list(h1);
		print_list(h2);
		print_list(h);
		sleep(1);
		while (k1 != NULL && k1->value <= k2->value)	{
			p1 = k1;
			k1 = k1->next;
		}
		if (k1 == NULL)	{
			p1->next = k2;
			return h;
		} else {	// k1->value > k2->value, shoule be p1, k2, ... k1
			p1->next = k2;
			// k2 try to move to right
			while (k2 != NULL && k2->value <= k1->value)	{
				p2 = k2;
				k2 = k2->next;
			}
			if (k2 == NULL)	{
				p2->next = k1;
				return h;
			} else {	// k2->value > k1->value, should be p2, k1, k2
				p2->next = k1;
				p1 = k1;
				p2 = k2;
			}
		}
	}
}

struct node * create_list(int data[], int len)
{
	struct node *h, *t, *r;
	int i;
	if (len < 1)	return NULL;
	h = r = malloc(sizeof(struct node));
	r->value = data[0];
	r->next = NULL;
	for (i = 1; i < len; i++)	{
		t = malloc(sizeof(struct node));
		t->value = data[i];
		t->next = NULL;
		r->next = t;
		r = t;
	}
	return h;
}

int main()
{
	int data1[1] = {1};
	int data2[1] = {23};
	struct node *h1, *h2;
	
	h1 = create_list(data1, sizeof(data1) / sizeof(data1[0]));
	h2 = create_list(data2, sizeof(data2) / sizeof(data1[0]));
	h1 = merge_list(h1, h2);
	print_list(h1);
	return 0;
}
