#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "setLib.h"

static int hashValue(const int n, const int tableSize) {
	return n % tableSize;
}

static Node *newNode(int key, int value) {
	Node *node = malloc(sizeof(*node));

	node->value = value;
	node->key = key;

	return node;
}

Set *newSet(const int size) {
	Set *set = malloc(sizeof(*set));

	set->data = calloc(size, sizeof(*set->data));
	set->size = size;
	set->nOfElements = 0;

	return set;
}

void addElement(Set *set, const int n) {
	const int step = 2;

	int hash = hashValue(n, set->size);

	while (set->data[hash] != NULL) {
		if (set->data[hash]->value == n)
			return;
		hash = (hash + step) % set->size;
	}

	Node* node = newNode(n, n);
	set->data[hash] = node;
	set->nOfElements++;
}

void printSet (const Set *set) {
	for (int i = 0; i < set->size; ++i) {
		if (set->data[i] != NULL)
			printf("%i ", set->data[i]->value);
	}
}
