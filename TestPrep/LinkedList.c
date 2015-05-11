#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef struct LL {
	void * data;
	struct LL * next;
	void (*printMe)(void *data);
} ll_t;

ll_t * add(ll_t * list, void * item);
ll_t * makeNode(void * data);
void strPrint(void *data);
void printList(ll_t *list);
int myEquals(void * data1, void * data2);
ll_t * del(ll_t * list, void * item);

int main() {
	ll_t * head = makeNode("a");
	head = add(head, "b");
	printList(head);
	head = add(head, "lol");
	printList(head);
	head = del(head, "a");
	printList(head);

}

ll_t * makeNode(void * data){
	ll_t * node = (ll_t *)malloc(sizeof(ll_t));
	node->data = data;
	node->next = NULL;
	node->printMe = strPrint;
	return node;
}

void strPrint(void *data){
	char *ptr = (char *)data;
	printf("%s\n", ptr);
}

ll_t * add(ll_t * list, void * item){
	ll_t * head = list;
	ll_t *newNode = makeNode(item);

	if (list->next == NULL){
		list->next = newNode;
		return list;
	}
	while (head->next != NULL){
		head = head->next;
	}
	head->next = newNode;
	return list;
}

ll_t * del(ll_t * list, void * item){
	ll_t * head = list;

	char *toDelete = (char *)item;
	char *data = (char *)head->data;

	if (strcmp(toDelete, data) == 0){
		if (head->next != NULL){
			list = head->next;
			free(head);
		} else {
			free(head);
			return NULL;
		}
	}

	while (strcmp(toDelete, data) != 0){
		head = head->next;
		data = (char *)head->data;
	}

	if (head->next != NULL){
		list->next = head->next;
		free(head);
	} else {
		free(head);
		return list;
	}

	return list;
}

void printList(ll_t *list){
	ll_t * head = list;
	while (head != NULL){
		head->printMe(head->data);
		head = head->next;
	}
}


