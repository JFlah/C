#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mt1.h"

void main(){
	String_t *string1 = makeString("Hello World");
	printf("%s\n", string1->letters);
	
	String_t *head = NULL; // cuz we check if null
	head = addStrLink(head, "Hey");
	head = addStrLink(head, "Hello");
	printf("Head: %s\n", head->letters);
	
	printList(head);
	
	printf("Len is %d\n", totalLen(head));
	
	String_t *pattern = makeString("llop");
	
	char *match = findMatch(pattern, string1);
	if (match != NULL) {
		printf("Match: %s\n", match);
	}
	else{
		puts("No match"); // implies \n
	}
}

String_t * makeString(char *letters){
	String_t *str = (String_t *)malloc(sizeof(String_t));
	int len = strlen(letters);
	str->len = len; // equiv (*str).len = len;
	char * heapLetters = (char *)malloc(len+1); // + 1 cuz strings have /0 at end
	strcpy(heapLetters, letters);
	str->letters = heapLetters;
	str->nextStr = NULL;
	return str;
}

char * findMatch(String_t *pattern, String_t *text){
	enum StateType state = OUT;
	char *c = text->letters;
	char *p = pattern->letters;
	int posText = 0;
	int posPatt = 0;
	
	while (*(c+posText) != '\0'){
		switch (state){
				case OUT:
					if (*(c+posText)==*p){
						state = IN;
						posPatt++;
					}
					else {
						posText++;
					}
					
					break;
					
				case IN:
					if (*(c+posText+posPatt)!=*(p+posPatt)){
						state = OUT;
						posText++;
						posPatt = 0;
					}
					else{
						posPatt++;
						if (*(p+posPatt) == '\0'){
							return c+posText;
						}
					}
		}
	}
	return NULL; // no match found
	
}


int totalLen(String_t *head){
	String_t *temp = head;
	int length = 0;
	while (temp != NULL){
		length += temp->len;
		temp = temp->nextStr;
	}
	return length;
}

String_t * addStrLink(String_t *head, char *letters){
	String_t *str = makeString(letters);
	String_t *temp = head;
	
	if (head == NULL){
		return str;
	}
	
	while (temp->nextStr != NULL){
		temp = temp->nextStr;
	}
	temp->nextStr = str;
	
	return head;
}

void printList(String_t *head){
	String_t *current = head;
	while (current != NULL){
		printf("%s\n", current->letters);
		current = current->nextStr;
	}

}



