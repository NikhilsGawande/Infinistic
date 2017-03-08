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
