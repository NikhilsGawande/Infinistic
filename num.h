typedef struct Number {
	char sign;
	char *integer;
	char *fraction;
}Number;

void initNumber(Number *a);
Number CreateNumber(Number num); 		/*creates a number from user*/
Number CreateNumberFromString(char *str);	/*creates number from string */
Number CreateIntNumber(int a);			/*creates Number from int */
void CopyNumber(Number pp , Number *a);		/* copy Number */
void PrintNumber(Number );			/*print */

Number AddNumber(Number a , Number b);
char* AddInteger(Number a , Number b);
char* AddFraction(Number a, Number b) ;
char *appendleft(int a, char *str);

Number SubNumber(Number a , Number b);
int CompareNumber(Number a, Number b) ;


Number MulNumber(Number a , Number b);
Number power(Number a , Number b);

Number DivNumber(Number a , Number b);
Number subdiv(Number c,Number d,Number fctr);
void divideten(Number *nf);

Number ModNumber(Number pp, Number qq);

Number infix(char *string);
//char ctop(cstack *cs);
