#include "numstack.h"
#include <stdio.h>
#include <stdlib.h>
void numinit(numstack *s) {
	s->head = NULL;
	s->tail = NULL;
	s->i = 0;
}
void numpush(numstack *s, Number x) {
	node *temp;
	temp = (node *)malloc(sizeof(node));
	initNumber(&(temp->a));
	temp->a = x;
	if(s->head == NULL) {
		s->head = temp;
		s->tail = temp;
		temp->next = NULL;
	}
	else {
		s->tail->next = temp;
		s->tail = temp;
		temp->next = NULL;
	}
	(s->i)++;
}
Number numpop(numstack *s) {
	int j = 0 ;
	(s->i)--;
	Number a;
	initNumber(&a);
	a = s->tail->a;
	node *temp;
	temp = s->tail;
	
	s->tail = s->head;	
	(s->i)--;
	for(j = 0; j < ((s->i)); j++) 
		s->tail = s->tail->next;
	if(s->head == s->tail && s->i == -1) 
		numinit(s);
	else {
		s->tail->next = NULL;
		(s->i)++;		
	}
	temp = NULL;
	return a;
}
int numempty(numstack *s) {
	return s->i == 0;
}
void printnumstack(numstack *s) {
	node *p;
	p = s->head ;
	int i;
	for(i = 0; i < s->i; i++) {
		printf("#");PrintNumber(p->a);
		p = p->next;
	}
}




