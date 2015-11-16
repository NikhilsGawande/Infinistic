#include "num.h"

typedef struct node {
	Number a;
	struct node *next;
}node;
typedef struct numstack{
	node *head;
	node *tail;
	int i;
}numstack;
void numinit(numstack *s);
void numpush(numstack *s, Number x);
Number numpop(numstack *s);
int numempty(numstack *s);
int numfull(numstack *s);
void printnumstack(numstack *s);
