#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "setLib.h"

/*	TODO
	* Add a linked list to hash table for fast iteration over
	* Destructors for sets
	* hash table resizing
	* add tests when adding elements (might not needed if there will automatic resizing of a set)
	* add memory allocation checks
	* maybe stick to sets with only one type of data but implementing set of sets would be great and beneficial
	* function comparing 2 nodes with the data of the same type
*/

// generating integers in the interval [min..max)
static int getRndInt(int min,  int max) {
	return ((rand() % max) + min) % max;
}

static int hashValue(const int n, const int tableSize) {
	return n % tableSize;
}

static int hashValuePair(const int x, const int y, const unsigned tableSize) {
	// Cantor pairing function for hashing ordered pairs
	return ((x + y) * (x + y + 1) / 2 + y) % tableSize;
}


static Node *newNode(memberType type) {
	Node *node = malloc(sizeof(*node));

	node->type = type;

	return node;
}

static Node *newInt(const int n) {
	Node *node = newNode(int_t);

	node->ival = n;

	return node;
}

static Node *newPair(const int x, const int y) {
	Node *node = newNode(opair_t);

	node->pair.x = x;
	node->pair.y = y;

	return node;
}

/*
static Node *newNode(int key, memberType type, int value) {
	Node *node = malloc(sizeof(*node));

	node->value = value;
	node->key = key;

	return node;
}
*/

Set *newSet(const int size) {
	Set *set = malloc(sizeof(*set));

	set->data = calloc(size, sizeof(*set->data));
	set->size = size;
	set->nOfElements = 0;
	set->step = 1;

	return set;
}

// populate a set with n random elements
void populateSet(Set *set, const int n, const int min, const int max) {
	if (n > set->size) {
		fprintf(stderr, "Not enought space in the set to add %i elements\n", n);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; ++i) {
		addInt(set, getRndInt(min, max));
	}
}

void addInt(Set *set, const int n) {

	int hash = hashValue(n, set->size);

	while (set->data[hash] != NULL) {
		if (set->data[hash]->ival == n)
			return;
		hash = (hash + set->step) % set->size;
	}
	
	Node* node = newInt(n);
	set->data[hash] = node;
	set->nOfElements++;
}

void addPair(Set *set, const int x, const int y) {

	int hash = hashValuePair(x, y, set->size);

	while (set->data[hash] != NULL) {
		if (set->data[hash]->pair.x == x && set->data[hash]->pair.y == y)
			return;
		hash = (hash + set->step) % set->size;
	}
	
	Node* node = newPair(x, y);
	set->data[hash] = node;
	set->nOfElements++;
}

void printSet (const Set *set) {
	for (int i = 0; i < set->size; ++i) {
		if (set->data[i] != NULL) {
			if (set->data[i]->type == int_t)
				printf("%i ", set->data[i]->ival);
			else if (set->data[i]->type == opair_t)
				printf("(%i,%i) ", set->data[i]->pair.x, set->data[i]->pair.y);
		}
	}
}

int isElement(const int n, const Set *set) {
	int hash = hashValue(n, set->size);

	while (set->data[hash] != NULL) {
		if (set->data[hash]->ival == n)
			return 1;
		hash = (hash + set->step) % set->size;
	}

	return 0;
}

int isSubset(const Set *setA, const Set *setB) {
	// Set with more elements cannot be a subset of a set with fewer elements (Small optimization)
	if (setA->nOfElements > setB->nOfElements)
		return 0;

	for (int i = 0; i < setA->size; ++i) {
		if (setA->data[i] == NULL)
			continue;
		else if (!isElement(setA->data[i]->ival, setB))
			return 0;
	}

	return 1;
}

int isEqual(const Set *setA, const Set *setB) {
	// scan through the set A and every time the match is found decrement
	// the number of elements in the set B
	// if all the elements of the set A are found within the set B, i.e. A is a subset of B
	// and all the elements of B are exhausted, i.e. counter decreased to 0
	// then the sets are equal

	if (setA->nOfElements != setB->nOfElements)
		return 0;

	int n = setB->nOfElements; // number n of elements in the set B that we haven't found yet

	for (int i = 0; i < setA->size; ++i) {
		if (setA->data[i] == NULL)
			continue;
		else if (!isElement(setA->data[i]->ival, setB))
			return 0;
		else
			--n;
	}

	return n ? 0 : 1; // if n is 0 then the sets are equal
}
