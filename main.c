/* Testing program for setLib
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "setLib.h"

int main (int argc, char **argv) {
	Set *set = newSet(30);

	for (int i = 0; i < 10; ++i) {
		addElement(set, i * 20);
	}

	printf("%i\n", set->nOfElements);	

	addElement(set, 60);
	addElement(set, 40);
	addElement(set, 20);
	
	printf("%i\n", set->nOfElements);	

	printSet(set);
	
	return 0;
}

