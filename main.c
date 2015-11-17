    This file is part of 'Mathbuddy' project.

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

