#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include "num.h"
void printmenu() {
	printf("0.create \n1. add :\n");
	printf("2. sub :\n");
	printf("3. mul :\n5. create frm string \n6.compare \n7. copy\n8. createint\n9. Div");

}
int main() {
 	Number a, b , c;
 	int choice, k;
 	char *str;
	//printmenu();
	while(1) {
		str = infixgetstring();
		c = infix(str);
		printf("ans");PrintNumber(c);	
	}
	return 0;
	
}

