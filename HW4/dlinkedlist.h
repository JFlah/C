/* 
 *
 *	dlinkedlist.h
 *
 *	Jack Flaherty
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <string.h>

typedef struct node{
	void * item;
	struct node * next;
	struct node * prev;
} node_t;

typedef struct dlist
{
	node_t *head;
	node_t *tail;
} dlist_t;

typedef dlist_t * dlist;

dlist makeDList(void);

node_t * createNode(void *item);

void addToEnd(dlist dList, void * item);

void forwardTraverse(dlist dList, void (*print)(void *val));

void forwardTraverseP(dlist dList, void (* print)(void * val, int price), int value);

void * del(dlist dList, int element);

void reverseTraverse(dlist dList, void (*print)(void *val));

void integerAt(dlist dList, int position);

int isEmpty(dlist dList);

void toString(void *val);
