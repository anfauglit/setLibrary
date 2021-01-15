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

// define type with set elements types
typedef enum {
	int_t,
	opair_t	
} memberType;

typedef struct node {
	memberType type;	
	int key; //hash key
	union {
		int ival;
		struct {
			int x;
			int y;
		} pair;
	};
} Node;

typedef struct set {
	memberType type; // type of elements in a set
	Node** data; // array of pointers to Nodes
	int size; // maximum number of elements in set (capacity)
	int nOfElements; // number of elements currently stored in a set
	int step;
} Set;

// new set initialization
Set *newSet(const int size); 

// adding a single element to a set
//void addElement(Set *set, const int n); 

void addInt(Set *set, const int n);


void addPair(Set *set, const int x, const int y);

// printing a set
void printSet(const Set *set);

// test whether an element is in a set
int isElement(const int n, const Set *set);

// function tests whether one set is a subset of another
int isSubset(const Set *A, const Set *B);

// function tests two sets for equality
// it is possible to combine functions isSubset and isEqual into one function without any
// loss of functionality, but the general solution might become slower and the code
// using it less explicit
int isEqual(const Set *A, const Set *B);

// populating a set with n arbitrary integers in the range [min..max)
void populateSet(Set *set, const int n, const int min, const int max);
