#include "mystring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 81

enum Statetype {IN, OUT};

void getarray(char **txt);
char * findMatch(String *text, String *pattern);

int main() {
	String *pattern, *text;
	char *p, *txt, *match;
	
	printf("Input pattern: ");
	getarray(&p);
	pattern = build_string(p);
	free(p);
	
	printf("Input text to check: ");
	getarray(&txt);
	text = build_string(txt);
	free(txt);
	
	printf("The string: %s\thas size: %d\n", text->chars, text->len);
	
	match = findMatch(text, pattern);
	if (match == NULL)
		puts("No match.");
	else
		printf("match: %s\n", match);
	

}

void getarray(char **txt) {

	char b, *t;
	t = (char *)malloc(sizeof(char)*MAXCHAR);
	int size=0, arySize=MAXCHAR;
	b=getchar();
	while (b != '\n') {
	
		if (size>=arySize) {
			arySize *= 2;
			t = realloc(t, arySize);
		}
	
		*(t+size) = b; // size=0 first loop
		
		size++;
		b = getchar();
	}
	if (size>=arySize) {
		arySize++;
		t = realloc(t, arySize); // adds 1 more, resizes to arySize
	}
	*(t+size)='\0';
	*txt = t;
}

char * findMatch(String *text, String *pattern) {
	int i=0, j=0, len, start;
	char *t=text->chars, *p=pattern->chars;
	enum Statetype state = OUT;
	while(*(t+i)!='\0'){
		switch(state){
			case OUT:
				if(*(t+i)==*p){
					start = i;
					j=0;
					state = IN;
				} else {
					i++;
				}
				break;
			case IN:
				//printf("%c\t%c\n", *(t+i), *(p+j));
				if(*(t+i)==*(p+j)){
					j++;
					if(*(p+j) == '\0'){
						return 	(t+start);
					}
				}
				else{
					i = start; 
					state = OUT;
				}
				i++;
				break;
			
		}
	}
	return NULL;
}
