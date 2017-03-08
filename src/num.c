/*    This file is part of 'Mathbuddy' project.

    Mathbuddy is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h>
#include<ctype.h>
#include <limits.h>
#include "../lib/numstack.h"
void initNumber(Number *a) {
	a->sign = '+';
	a->integer = NULL;
	a->fraction = NULL;
}
char *getstring() {
	char *str;
	str = NULL;
	char d;
	int SIZE = 16, count = 0;
	str = (char *)malloc(SIZE);
	int i = 0;
	while(scanf("%c", &d) != EOF ) {
		str[count] = d;
		count++;
		if(count == SIZE) {
			SIZE *= 2;
			str = (char *)realloc(str, SIZE);
			if(str == NULL) {
				printf("Failed for %d\n", SIZE);
				exit(1);
			}
		}
	}
	str[count] = '\0';	
	return str;
}

char *infixgetstring() {
	char *str;
	str = NULL;
	char d;
	int c = 0;
	int SIZE = 16, count = 0;
	str = (char *)malloc(SIZE);
	int i = 0;
	while(1) {
		scanf("%c",&d);
		if(d == '\n' && c == 1) {
			str[count] = '\0';	
			return str;
		}
		str[count] = d;
		count++;
		if(c == 0 && d == '\n') 
			count--;
		if(count == SIZE) {
			SIZE *= 2;
			str = (char *)realloc(str, SIZE);
			if(str == NULL) {
				printf("Failed for %d\n", SIZE);
				exit(1);
			}
		}
		c = 1;
	}

}
Number CreateIntNumber(int anum) {
	char *temp;
	temp = (char *)malloc(11);
	sprintf(temp, "%d" , anum);
	Number a;
	initNumber(&a);
	a = CreateNumberFromString(temp);
	return a;
}
		
Number CreateNumber(Number num) {
	char *str, *a ;
	int ssize;
	str = NULL;
	printf("Please enter Number:");
	str = getstring();
	ssize = strlen(str);
	a =(char *)malloc(strlen(str) + 1);
	strcpy(a, str);
	free(str);
	int space = 0, i, asize, sign = 0;
	initNumber(&num);
	for(i = 0;  i < ssize; i++) {
		if(a[i] == ' ') {
			if (space == 2) {
				printf("Invalid"); 
				initNumber(&num);
				return num;
			}
			space = 1;
		}
		else if (a[i] == '+') {
			if(space == 2 || sign == 1 ) {
				printf("Invalid"); 
				initNumber(&num);
				return num;
			}
			else { 
				num.sign = '+';
				sign = 1;
			}
		}
		else if (a[i] == '-') {
			if(space == 2 || sign == 1) {
				printf("Invalid"); 
				initNumber(&num);
				return num;
			}
			else { 
				num.sign = '-';
				sign = 1;
			}
		}
		
		else if(isalnum(a[i]) && (space == 1 || space == 0)) { 
			num.integer = &a[i];
			space = 2;
		}
		else if (a[i] == '.') 	
			num.fraction  = &a[i];
/*		else {
			printf("Invalid"); 
			return NULL;
		}
*/	}
	if(num.fraction == NULL) {
		num.fraction = &a[i];
	}

	if(sign == 0) 
		num.sign = '+';
	printf("\n");
	return num;
}
void PrintNumber(Number a) {
//	printf("\n Number :");
	printf("%c" , a.sign);
	printf("%s" , a.integer);
//	printf("\n fraction :");
//	printf("%s\n" , a.fraction);

}
Number CreateNumberFromString(char *str) {
	Number a;
	initNumber(&a);
	int i = 0, space = 1;
	char *temp;
	temp = str;
	int n = strlen(temp);
	while(1) {
		if(str[i] == ' ') { 
			i++;
			space = 1;
		}
		else if(str[i] == '+') {
			a.sign = '+';
			temp++;
			break;
		}
		else if (str[i] == '-') {
			a.sign = '-';
			temp++;
			break;
		}
		else if (isdigit(str[i]) && space == 1){
			a.sign = '+';
			break;
		}
		else 
			i++;
	}
	a.integer = &temp[i];
	for(; i < n; i++) 
		if(temp[i] == '.') 
			a.fraction = &temp[i];
	if(a.fraction == NULL) {
		i = strlen(temp);
		a.fraction = &temp[i];
	}
	return a;
	
}

Number AddNumber(Number pp, Number qq) {
	Number c; 
	initNumber(&c);
	if(pp.integer == NULL || qq.integer == NULL) 
		return c;		
	Number a, b;
	initNumber(&a);
	initNumber(&b);
	CopyNumber(pp, &a);
	CopyNumber(qq, &b);
	if(a.sign == '-' && b.sign == '+') {
		a.sign = '+';
		c = SubNumber(a, b);
		if(CompareNumber(a,b) > 0) 
			c.sign = '-';
		else if(CompareNumber(a,b) < 0) 
			c.sign = '+';
		else 
			c.sign = '+';
		return c;
	}
	else if(a.sign == '+' && b.sign == '-') {
		b.sign = '+';
		c = SubNumber(a,b);
		if(CompareNumber(a,b) > 0) 
			c.sign = a.sign;
		else if(CompareNumber(a,b) < 0) 
			c.sign = '-';
		else 	
			c.sign = '-';
		return c;
	}
			
	char *p, *q;
	int psize = 0, qsize = 0, i;
	char dot[2];
	dot [0] = '.';
	dot[1] = '\0';
	p = AddInteger(a, b);	
	q = AddFraction(pp, qq);
	if(q) {
		psize = strlen(p);
		qsize = strlen(q);
		p = (char *)realloc(p , (psize + qsize + 4));
		strcat(p, dot);
		strcat(p, q);
		psize = strlen(p);
		for(i = 0; i < psize;  i++) {
			if(p[i] == '.' ) 
				c.fraction = &p[i];
		}
	}
	c = CreateNumberFromString(p);
	if(a.sign == '+' && b.sign == '+') 
		c.sign = '+';
	else 
		c.sign = '-';
	return c;
}
char* AddInteger(Number a , Number b) {
	int x, y, z, carry, k, i, j;
	x = y = z = carry = 0;
	int asize = 0 , bsize = 0;
	char *p , *q, *sum;
	Number temp;
	asize = strlen(a.integer);
	bsize = strlen(b.integer);
	if(asize < bsize) {
		temp = b;
		b = a;
		a = temp;
	}
	p = a.fraction;
	q = b.fraction;
	*p = '\0' ;
	*q = '\0';
	sum = (char *)malloc(1);
	*sum = '\0';	
	while((q - b.integer) > 4) {
		*p = '\0';
		*q = '\0';
		p = p - 4;
		q = q - 4;
		x = atoi(p);
		y = atoi(q);
		z = x + y + carry;
		carry = z / 10000;
		if((z % 10000) > 999) {
			sum = appendleft(z % 10000,  sum);
		}
		else{
			for(i = 0; i < 4; i++) {
				if(z > 0) {
					sum = appendleft(z % 10, sum);
					z = z / 10;
				}
				else 
					sum = appendleft(0, sum);
			}
		}
	} 
	if(q != b.integer) {
		*p = '\0';
		*q = '\0';
		k = 1;
		for(i = 0; i < (q - b.integer); i++) {
			k = k * 10;
		}
		p = p - (q - b.integer) ;
		q = b.integer;
		x = atoi(p);
		y = atoi(q);
		z = x + y + carry;
		carry = z / k;
		for(j = 0; j < i; j++) {
				if(z > 0) {
					sum = appendleft(z % 10, sum);
					z = z / 10;
				}
				else 
					sum = appendleft(0, sum);
		}
	}
	while((p - a.integer) > 4) {
		*p = '\0';
		p = p - 4;
		x = atoi(p);
		z = x + carry ;
		if((z % 10000) > 999) {
			sum = appendleft(z % 10000,  sum);
			carry = z / 10000;
		}
		else{
			k = 10;
			for(i = 0; i < 4; i++) {
				if(z) {
					sum = appendleft(z % k, sum);
					z = z / 10;
				}
				else 
					sum = appendleft(0, sum);
			}
			carry = 0;
		}
		
	}
	if(p != a.integer) {
		*p = '\0';
		p = a.integer;
		x = atoi(p);
		sum = appendleft((x + carry), sum);
	}
	else {
		sum = appendleft(carry, sum);
	}
	return sum;
}
char* AddFraction(Number pp, Number qq) {
	Number a, b;
	initNumber(&a);
	initNumber(&b);
	CopyNumber(pp, &a);
	CopyNumber(qq, &b);
	char *p , *q, *m, *n, *sum;
	int x, y, z, i;
	char zero = '0', null ='\0';
	m = a.fraction;
	n = b.fraction;
	if(*m == '\0' && *n != '\0') {
		n++;
		return n;
	}
	else if(*n == '\0' && *m != '\0') {
		m++;
		return m;
	}
	else if(*m == '\0' && *n == '\0') {
		return NULL;
	}
	m++;
	n++;
	x = strlen(m);
	y = strlen(n);
	p = (char *)malloc(x + 1);
	strcpy(p, m);
	q = (char *)malloc(y + 1);
	strcpy(q, n);	
	if(x < y) {
		z = y - x;
		p =(char *)realloc(p, (strlen(p) + z + 1));
		for(i = 0; i < z; i++) 
			strcat(p , &zero);
		strcat(p , &null);
	}
	else if(y < x) {
		z = x - y;
		q =(char *)realloc(q, (strlen(q) + z + 1));
		for(i = 0; i < z; i++) 
			strcat(q , &zero);
		strcat(q , &null);
	}	
	a.integer = p;
	b.integer = q;
	x = strlen(p);
	a.fraction = &p[x];
 	b.fraction = &q[x];
	sum = AddInteger(a, b);
	return sum;
}
void CopyNumber(Number pp , Number *a){
	int n = strlen(pp.integer);
	char* astr;
	astr = (char *)malloc(n + 1);
	strcpy(astr, pp.integer);
	*a = CreateNumberFromString(astr);
	a->sign = pp.sign;
}
 
char *appendleft(int a, char *str) {
	int i, k;
	i = 0;
	k = 1;
	while(a / k != 0 ) {
		i++;
		k = k * 10;
	}
	if(a == 0) {
		i++;
	}
	str = (char *)realloc(str , (strlen(str) + i + 1));
	if(str == NULL) {	
		printf("Error");
		exit(1);
	}
	char *temp;
	temp = (char *)malloc(strlen(str) + 1) ;
	strcpy(temp, str);
	*str = '\0';
	sprintf(str, "%d", a);
	str[i] = '\0';
	strcat(str, temp);
	free(temp);
	return str;
}
int CompareNumber(Number a, Number b) {
	int aa, bb;
	if(a.sign == '-' && b.sign == '-') {
		aa = -1;
		bb = 1;
	}
	else if (a.sign == '+' && b.sign == '+') {
		aa = 1;
		bb = -1;
	}
	else if(a.sign == '-') 
		return -1;
	else 
		return 1;
	
	char *p, *q;
	p = a.integer;
	q = b.integer;
	while(*p == '0') 
		p++;
	while(*q == '0') 
		q++;
	if((a.fraction - p) > (b.fraction - q)) {
		return aa;
	}
	else if((a.fraction - p) < (b.fraction - q)) 
		return bb;
	else {
		while(*p != '\0' && *q != '\0') {
			if(*p > *q) 
				return aa;
			else if(*p < *q)
				return bb;
			else {
				p++;
				q++;
			}
		}
	}
	return 0;
}
Number SubNumber(Number pp, Number qq) {
	Number c, ttemp;
	initNumber(&c);
	if(pp.integer == NULL || qq.integer == NULL) 
		return c;
	Number a, b;
	initNumber(&a);
	initNumber(&b);
	CopyNumber(pp, &a);
	CopyNumber(qq, &b);
	if(a.sign == '-' && b.sign == '+') {
		a.sign = '+';
		c = AddNumber(a, b);
		c.sign = '-';
		return c;
	}
	else if(a.sign == '+' && b.sign == '-') {
		b.sign = '+';
		c = AddNumber(a, b);
		c.sign = '+';
		return c;
	}

	char * temp, *p, *q;
	int x, y, i, j, borrow, z;
	x = y = i = j = borrow = 0;
	initNumber(&ttemp);
	int mm, m, n, o;
	if(a.sign == '-' && b.sign == '-') {
		a.sign = '+';
		b.sign = '+';
	}
	mm = CompareNumber(a, b) ;
	if(mm < 0) {
		ttemp = a;
		a = b;
		b = ttemp;
	}
	else if (mm == 0) {
		c = CreateIntNumber(0);
		return c;
	}
	p = a.integer;
	q = b.integer;
	x = strlen(p);
	y = strlen(q);
	p = p + x;
	q = q + y;
	if(x > y) 
		temp = (char* )malloc(x + 1);
	else 
		temp = (char* )malloc(y + 1);
	m = p - a.fraction;
	n = q - b.fraction;
	p--;
	q--;
	if(m > n) {
		o = m - n ;
		for(i = 0; i < o; i++) {
			temp[j++] = *p;
			p--;
		}
	}
	else if (m < n) {
		o = n - m ;
		for(i = 0; i < o; i++) {
			temp[j++] = *q;
			q--;
		}	
	}
	mm = (q - b.integer);
	for(i = 0; i < mm + 1; i++) {
		if(*p < *q) {
			z = 10 + *p - *q - borrow ;	
			z = '0' + z;
			temp[j++] = z;
			borrow = 1;
		}
		else if  (*p > *q) {
			z = *p - *q - borrow;	
			z = '0' + z;
			temp[j++] = z;
			borrow = 0;
		}
		else if(*p == '.') {
			temp[j++] = '.';
		}	
		else {
			if(borrow) {
				temp[j++] = '9';	
				borrow = 1;
			}
			else {
				temp[j++] = '0';
				borrow = 0;
			}
		}
		if(q != b.integer) {
			p--;
			q--;
		}
	}	
	mm = p - a.integer;
	p--;
	if(borrow) 
		(*p)--;
	for(i = 0; i < mm; i++) {
		temp[j++] = *p;
		p--;
	}
	temp[j] = '\0';
	int stemp = strlen(temp);
	char *str;
	str =(char *)malloc(strlen(temp) +1);
	for (i = 0 ; i < stemp; i++) {
		str[i] = temp[stemp - 1 - i];
	}
	str[i] = '\0';
	c = CreateNumberFromString(str);
	if(pp.sign == '+' && qq.sign == '+') {
		if(CompareNumber(pp ,qq) > 0) 
			c.sign = '+';
		else if(CompareNumber(pp ,qq) < 0) 
			c.sign = '-';
		else {
			c = CreateIntNumber(0);
			return c;
		}
	}
	else if(pp.sign == '-' && qq.sign == '-') {
		if(CompareNumber(pp ,qq) > 0) 
			c.sign = '+';
		else if(CompareNumber(pp ,qq) < 0) 
			c.sign = '-';
		else {
			c = CreateIntNumber(0);
			return c;
		}
	}		
	return c;
}
Number MulNumber(Number ppt , Number qq) {
	Number temp, c, an, bn;
	initNumber(&c);
	if(ppt.integer == NULL || qq.integer == NULL) 
		return c;
	Number a, b;
	initNumber(&a);
	initNumber(&b);
	CopyNumber(ppt, &a);
	CopyNumber(qq, &b);
	if(*a.integer == '0') 
		a.integer++;
	if(*b.integer == '0') 
		b.integer++;
	numstack *nc;
	nc = (numstack *)malloc(sizeof(numstack));
	numinit(nc);
	int x, y,z, carry = 0, n, i , k, j, pp = 0, zero= 0;
	char *p, *q , *mul;
	
	x = strlen(a.integer);
	y = strlen(b.integer);
	if(x < y) {
		temp = a;
		a = b;
		b = temp;
	}
	q = b.integer;
	y = strlen(q);
	q = q + y;
	q--;
	char mn[x + 1];
	for(i = 0; i < y; i++) {
		pp = 0;
		carry = 0;
		if(*q == '.') {
			i++;
			q--;
		}	
		mul = (char *)malloc(1 + i);
		*mul ='\0';

		for(j = 0; j < zero; j++) {
			mul[pp++] = '0';
		}
		zero++;
		mul[pp] ='\0';
		strcpy(mn, a.integer);
		c = CreateNumberFromString(mn);
		p = c.integer;
		x = strlen(p);
		p = p + x;
		k = 1;
		while(p != c.fraction) {
			*p = '\0';
			if((p - c.fraction) > 4) { 
				p = p - 4;
				n = atoi(p);
				n = n * (*q - '0') + carry;
				carry = n/ 10000;
				if((n % 10000) > 999) {
					mul = appendleft(n % 10000,  mul);
				}
				else{
					for(z = 0; z < 4; z++) {
						if(n > 0) {
							mul = appendleft(n % 10, mul);
							n = n / 10;
						}
						else 
						mul = appendleft(0, mul);
					}
				}
			}	
			else {
				z = p - c.fraction;
				z--;
				p = c.fraction;
				p++;
				n = atoi(p);
				n = n * (*q - '0');
				k = 1;
				for(j = 0; j < z; j++) {
					k = k * 10;
				}
				pp = (n % k) + carry;
				carry = n / k;
				for(j = 0; j < z; j++) {
					if(pp> 0) {
						mul = appendleft(pp % 10, mul);
						pp = pp / 10;
					}
					else 
						mul= appendleft(0, mul);
				}
				p--;
			}
		}
		k = 1;
		*p = '\0';
		while(p != c.integer) {
			*p = '\0';
			k = 1;
			if((p - c.integer) > 4) { 
				p = p - 4;
				n = atoi(p);
				n = n * (*q - '0') + carry;
				carry = n/ 10000;
				if((n % 10000) > 999) {
					mul = appendleft(n % 10000,  mul);
				}
				else{
					for(z = 0; z < 4; z++) {
						if(n > 0) {
							mul = appendleft(n % 10, mul);
							n = n / 10;
						}
						else 
						mul = appendleft(0, mul);
					}
				}
			}	
			else {
				p = c.integer;
				n = atoi(p);
				n = n * (*q - '0');
				k = 1;
				z = 0;
				pp = n  + carry;
				mul = appendleft(pp, mul);
			}
		}
		q--;

		initNumber(&temp);
		temp = CreateNumberFromString(mul);
		numpush(nc, temp);
	}
	an = numpop(nc);
	y = strlen(b.integer);
	if(*a.fraction == '.')
		y = y - 2;
	else 
		y--;
	for(i = 0; i < y; i++) {
		bn = numpop(nc);
		an = AddNumber(an, bn);
	}
	initNumber(&c);
	y = strlen(an.integer);
	c.integer = (char *)malloc(y + 2);
	strcpy(c.integer, an.integer);
	q = c.integer;
	q = q + y;
	if(*ppt.fraction != '.' && *qq.fraction != '.') {
		c.fraction = q;
		return c;
	}	
	x = strlen(ppt.fraction);
	y = strlen(qq.fraction);
	if(*ppt.fraction != '.') 
		x = 1;
	else if(*qq.fraction != '.') 
		y = 1;
	x = x + y - 1;
	for(i = 0; i < x; i++)  {
		q[1] = q[0];
		q--;
	}
	q++;
	*q = '.';
	c.fraction = q; 
	if(ppt.sign == qq.sign) 
		c.sign = '+';
	else 
		c.sign = '-';
	return c;
}
Number ModNumber(Number pp, Number qq) {
	Number a, b, c;
	initNumber(&a);
	initNumber(&b);
	initNumber(&c);
	if(pp.sign != '+' && qq.sign != '+')
		return c;
	CopyNumber(pp, &a);
	CopyNumber(qq, &b);
	c = DivNumber(a, b);
	c = MulNumber(c, b);
	c = SubNumber(a, c);
	c.sign = '+';
	return c;
}
Number DivNumber(Number pp, Number qq) {
	Number c, zero;
	initNumber(&c);
	zero = CreateIntNumber(0);
	Number a, b, d , nf, fctr, nfctr, one ,ten, two, f, temp1;
	initNumber(&a);
	initNumber(&b);
	CopyNumber(pp, &a);
	CopyNumber(qq, &b);
	a.sign = '+';
	b.sign = '+';
	if(CompareNumber(qq, zero) == 0) 
		return c;
	if(CompareNumber(a, b) < 0) {
		printf("here");
		return zero;
	}
	if(pp.integer == NULL || qq.integer == NULL) 
		return c;
	int sb,bs, i, j ,k;
	two = CreateIntNumber(2);
	one = CreateIntNumber(1);
	ten = CreateIntNumber(10);
	f = CreateIntNumber(1);
	sb = a.fraction - a.integer;
	bs = b.fraction - b.integer;
	sb = sb - bs;
	if (sb > 1) {
		for(i = 1; i < sb; i++) {
			k = 1;
			for(j = 0; j < 8 && i < sb; j++) {
				k = k * 10;
				i++;
			}
			temp1 = CreateIntNumber(k);
			f = MulNumber(f, temp1);
		}
	}				
	d = MulNumber(b , f);
	CopyNumber(a, &c);
	fctr = CreateIntNumber(1);	
	fctr = subdiv(c, d, one);
	CopyNumber(f, &nf);
	f = MulNumber(f, fctr);
	divideten(&nf);
	while(*nf.integer != '\0') {
		fctr = MulNumber(fctr , d);
		c = SubNumber(c, fctr);
		d = MulNumber(b, nf);
		fctr = subdiv(c, d, one);
		nfctr = MulNumber(fctr , nf);
		f = AddNumber(f, nfctr);
		divideten(&nf);
	}
	if(pp.sign == qq.sign)
		f.sign = '+';
	else 
		f.sign = '-';								
	return f;
}
void divideten(Number *nf) {
	char *p;
	p = nf->fraction;
	p--;
	*p = '\0';
	nf->fraction = p;
} 
Number subdiv(Number c, Number d, Number fctr){
	int mm;
	Number g, one , two;
	fctr = CreateIntNumber(2);
	two = CreateIntNumber(2);
	one = CreateIntNumber(1);
	while(1) {
		g = MulNumber(d, fctr);
		mm = CompareNumber(g, c);
		if(mm < 0) 
			fctr = AddNumber(fctr , two);
		else if(mm > 0) { 	
			fctr = SubNumber(fctr, one);
			g = MulNumber(d , fctr);
			mm = CompareNumber(g, c);
			if(mm < 0) 
				return fctr;
			else if(mm > 0) {
				fctr = SubNumber(fctr, one);
				return fctr;
			}
			else 
				return fctr;
		}
		else 
			return fctr;
	}
}
#define OPERAND 	1
#define OPERATOR 	2
#define INVALID		3
#define SIZE 128
typedef struct cstack {
	char c[SIZE];
	int j;
}cstack;
void cinit(cstack *s) {
	s->j = 0;
}
void cpush(cstack *s, char x) {
	s->c[s->j] = x;
	(s->j)++;
}
char cpop(cstack *s) {
	char x = s->c[(s->j - 1)];
	(s->j)--;	
	return x;
}
int cempty(cstack *s) {
	return s->j == 0;
}
int cfull(cstack *s) {
	return s->j == SIZE - 1;
}

typedef struct token {
	int type;
	union data {
		Number num;
		char operator;
	}d;
}token;


enum states {SPC, NUM, OPR, END, ERROR};
int j;
char *pp, *qp;
int currstate , nextstate;
token *getnext(char *string) {
	int done = 0, k;
	char *a;
	token *p = (token *)malloc(sizeof(token));
	if(p == NULL)
		return NULL;
	int i;
	while(1) {
		switch(string[j]) {
			case '1': case'2': case '3': case '4':
			case '5': case'6': case '7': case '8':
			case '9': case'0': case '.':
				nextstate = NUM;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')' :
				nextstate = OPR;
				break;
			case '\0':
				nextstate = END;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERROR;
				break;
		}
		switch(currstate) {
			case SPC:
				switch(nextstate){
					case SPC:
						/* Do nothing */
						break;
					case NUM:
						pp = &string[j];	
						break;
					case OPR:
						/* Do nothing */
						break;
					case END:
						break;
					case ERROR:
						break;
					default:
						break;
				}
				break;
			case NUM:
				switch(nextstate){
					case SPC:
						/* Num completed */
						p->type = OPERAND;
						qp = &string[j];
						k = qp - pp;
						a =(char*)malloc(k +1);
						for(i = 0; i < k ; i++) {
							a[i] = *pp;
							pp++;
						}
						a[i] = '\0'; 
						p->d.num = CreateNumberFromString(a);
						done = 1;
						break;
					case NUM:
							
						break;
					case OPR:
						p->type = OPERAND;
						qp = &string[j];
						k = qp - pp;
						a =(char*)malloc(k + 1);
						for(i = 0; i < k ; i++) {
							a[i] = *pp;
							pp++;
						}
						a[i] = '\0'; 
						p->d.num = CreateNumberFromString(a); 
						done = 1;
						break;
					case END:
						p->type = OPERAND;
						qp = &string[j];
						k = qp - pp;
						a =(char*)malloc(k +1);
						for(i = 0; i < k ; i++) {
							a[i] = *pp;
							pp++;
						}
						a[i] = '\0'; 
						p->d.num = CreateNumberFromString(a); 
						done = 1;
						break;
					case ERROR:
						p->type = OPERAND;
						qp = &string[j];
						k = qp - pp;
						a =(char*)malloc(k +1);
						for(i = 0; i < k ; i++) {
							a[i] = *pp;
							pp++;
						}
						a[i] = '\0'; 
						p->d.num = CreateNumberFromString(a); 
						done = 1;
						break;
					default:
						break;
				}
				break;
			case OPR:
				switch(nextstate){
					case SPC:
						p->type = OPERATOR;
						p->d.operator = string[j - 1];
						done = 1;
						break;
					case NUM:
						p->type = OPERATOR;
						p->d.operator = string[(j - 1)];
						pp = &string[j];
						done = 1;
						break;
					case OPR:
						p->type = OPERATOR;
						p->d.operator = string[j - 1];
						done = 1;
						break;
					case END:
						p->type = OPERATOR;
						p->d.operator = string[j - 1];
						done = 1;
						break;
					case ERROR:
						p->type = OPERATOR;
						p->d.operator = string[j];
						done = 1;
						break;
					default:
						break;
				}
				break;
			case END:
				nextstate = END;
				done = 1;
				p = NULL;
				break;
			case ERROR:
				nextstate = ERROR;
				p->type = INVALID;
				done = 1;
				break;
			default:
				break;
		}
		currstate = nextstate;
		j++;
		if(done == 1)
			return p;
	}
	return NULL;	
}
int precedence(char op) {
	if(op == '*' || op == '/')
		return 30;
	else if(op == '+' || op == '-')
		return 20;
	else if(op == '%')
		return 10;
	else if(op == '(' || op == ')')
		return 5;

	else	
		return 0;
}
char ctop(cstack *cs) {
	
	char x = '!';
	if(!cempty(cs)) {
		x = cpop(cs);
		cpush(cs, x);
	}
	return x;
}
Number infix(char *string) {
	int i;
	j = 0;
	currstate = SPC;
	numstack *s; 
	Number error;
	s =(numstack *)malloc(sizeof(numstack));
	numinit(s);
	initNumber(&error);
	cstack cs;
	cinit(&cs);
	token *t;
	Number x, y, z;
	initNumber(&x);
	initNumber(&y);
	initNumber(&z);		
	char ch,prevop;
	while((t = getnext(string)) != NULL) {
		if(t->type == OPERAND) {
			numpush(s, t->d.num); 
		}
		else if(t->type == OPERATOR) {
			prevop = ctop(&cs);
			while((precedence(t->d.operator) <= precedence(prevop)) && ((t->d.operator) != '(') && (prevop != '(')) {
				ch = cpop(&cs);
				x  = numpop(s);
				y  = numpop(s);
				switch(ch) {
					case '+':
						z = AddNumber(x, y);
						break;
					case '-':
						z = SubNumber(y, x);
						break;
					case '*':
						z = MulNumber(x, y);
						break;
					case '/':
						z = DivNumber(y, x);
						break;
					case '%':
						z = ModNumber(y, x);
						break;
					default:
						return error;
						break;
				}
				numpush(s,z);
				prevop = ctop(&cs);
			}
			if((t->d.operator) != ')')
				cpush(&cs,(t->d.operator));
			else if(!cempty(&cs))
				cpop(&cs);
		}
		else if(t->type == INVALID)
			return error;
		free(t);	
	}
	while(!cempty(&cs)) {
		ch = cpop(&cs);
		x  = numpop(s);
		y  = numpop(s);
		switch(ch) {
			case '+':
				z = AddNumber(x, y);
				break;
			case '-':
				z = SubNumber(y, x);
				break;
			case '*':
				z = MulNumber(x, y);
				break;
			case '/':
				z = DivNumber(y, x);
				break;
			case '%':
				z = ModNumber(y, x);
				break;
			default:
				return error;
				break;
		}		
		numpush(s,z);
	}
	if(!numempty(s)) {
		x = numpop(s);
		if(numempty(s))	
			return x;	
		else
			return error;
	}
	else
		return error;
}
			
			
