/* Testing program for setLib
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "setLib.h"

int main (int argc, char **argv) {
	
	srand(time(NULL));

	Set *setA = newSet(30);
	Set *setB = newSet(30);
	
	populateSet(setA, 10, 0, 20);
	addPair(setA, 10, 10);
	populateSet(setB, 10, 0, 20);
	addInt(setB, 200);
	printSet(setA);
	printf("\n");
	printSet(setB);
	printf("\n");

//	printf("Is setA equal to setB?: %i\n", isEqual(setA, setB));
//	printf("Is setA a subset of setB?: %i\n", isSubset(setA, setB));

	return 0;
}

