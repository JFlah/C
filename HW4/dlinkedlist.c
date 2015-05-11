/* 
 *
 *	dlinkedlist.c
 *
 *	Jack Flaherty
 *
 */
 
 #include "dlinkedlist.h"
/*
int main(){
	int a = 6, b = 25, c = 99, d = 102, e = 18;
	dlist dList = makeDList();
	
	addToEnd(dList, &a);
	addToEnd(dList, &b);
	addToEnd(dList, &c);
	addToEnd(dList, &d);
	addToEnd(dList, &e);
	
	puts("List");
	forwardTraverse(dList, toString);
	puts("List backwards");
	reverseTraverse(dList, toString);
	
	del(dList, 3);
	
	puts("List element 3 deleted");
	forwardTraverse(dList, toString);

	integerAt(dList, 2);
	integerAt(dList, 1);
}
*/

dlist makeDList(void)
{
	dlist dList = (dlist)malloc(sizeof(dlist_t));
	
	dList->head = NULL;
	dList->tail = NULL;
	
	return dList;
}

node_t * createNode(void * item)
{
	node_t * nodeNew = (node_t *) malloc(sizeof(node_t));
	
	nodeNew->prev = NULL;
	nodeNew->next = NULL;
	nodeNew->item = item;
	
	return nodeNew;
}

void addToEnd(dlist dList, void * item)
{
	node_t * nodeNew = createNode(item);
	
	if (isEmpty(dList)==1){
		puts("Nothing currently in list, adding now");
		dList->head = nodeNew;
		dList->tail = nodeNew;
		
		return;
	}
	
	dList->tail->next = nodeNew;
	nodeNew->prev = dList->tail;
	dList->tail = nodeNew;
}

void forwardTraverse(dlist dList, void (* print)(void * val))
{
	node_t * current = dList->head;
	
	printf("[");
	
	while (current != NULL)
	{
		print(current->item);
		current = current->next;
		if (current != NULL){
			printf(", ");
		}
	}
	printf("]\n");
}

void * del(dlist dList, int element)
{
	int i=0;
	
	node_t * travNode = dList->head; // the temporary traversal node for moving along the list
	node_t * previous; // node to hold node before the node we are deleting
	node_t * next; // node to hold node after node we are deleting
	
	// traverses along the list while we still have not reached the given element
	while (i < element && travNode != NULL)
	{
		travNode = travNode->next;
		i++;
	}
	
	// checks if we have accidentally traversed to a null node (out of bounds)
	if (travNode == NULL)
	{
		puts("Index given is too big");
		return;
	}
	
	// logic to break the deleted node off of the list
	next = travNode->next;
	previous = travNode->prev;
	
	void * data = travNode->item;
	
	if (previous == NULL && next == NULL){
		dList->head = NULL;
		dList->tail = NULL;
	}
	else if (previous == NULL && next != NULL){
		dList->head = next;
		next->prev = NULL;
	}
	
	else if (previous != NULL && next == NULL){
		dList->tail = previous;
		previous->next = NULL;
	}
	
	else {
		previous->next = next;
		next->prev = previous;
	}
	
	free(travNode);
	return data;
}

void reverseTraverse(dlist dList, void (* print)(void * val))
{
	node_t * current; // traversal node
	
	printf("[");
	
	// loop starts at the tail to move backwards one each iteration
	for(current = dList->tail; current != NULL; current = current->prev)
	{
		print(current->item);
		
		if (current->prev != NULL) // sets up to continue the list if the next node to be printed exists
			printf(", ");
	}
	
	printf("]\n"); // ends list
}

void integerAt(dlist dList, int position){
	node_t * current = dList->head;
	int i = 0;
	
	while (i < position){
		current = current->next;
		i++;
	}
	void * item = current->item;
	
	printf("Int at position %d is %d\n", position, *((int *)item));

}

int isEmpty(dlist dList){
	if (dList->head == NULL && dList->tail == NULL)
	{
		return 1; // means empty
	}
	return 0; // means the head and tail were set, not empty
}

// because the items are void so there has to be some way to make them print as nice-looking ints
void toString(void * val){
	int * p = (int *) val;
	printf("%d", * p);
}
