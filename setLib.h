/* C library for working with sets
 * Author: Alexander Chekalin
 * Created: 12.01.2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// hash table for implementing set will be using open addressing scheme
// that's the most convient approch for a simple library IMHO

typedef struct node {
	int key;
	int value;
} Node;

typedef struct set {
	Node** data; // array of pointers to Nodes
	int size; // maximum number of elements in set (capacity)
	int nOfElements; // number of elements currently stored in a set
} Set;

// new set initialization
Set *newSet(const int size); 

// adding a single element to a set
void addElement(Set *set, const int n); 

// printing a set
void printSet (const Set *set);
