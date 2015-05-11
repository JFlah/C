// HW 2 Jack Flaherty
// Program which recognizes a pattern GCAG in a given string, how many matches, whether or not they were contiguous or non-contiguous matches

#include <stdio.h>
#include <stdlib.h>
#define MAXCHAR 81

void getarray(char **txt);
char * findMatchC(char *t);
char * findMatchNC(char *t);
void printIt(char *ptr);
int matchCount(char *t);

enum State {S, G, C, A};

int main() {
	char *text, *pattern;
	char *p,*q,*r;
	int n,m,x,y;
	getarray(&text);

	printIt(text);

	findMatchC(text);
	findMatchNC(text);
	printf("You have %d matches\n", matchCount(text));

	free(text);
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

void printIt(char *ptr) {
	char c=*ptr;
	int i=0;

	while(c!='\0'){
		printf("%c", c);
		i++;
		c=*(ptr+i);
	}
	printf("\n");
}

char * findMatchC(char *t) {

	enum State current = S;
	char ch=*t;
	int i=0, matchLocation;

	while(ch!='\0') {
		switch(current) {
			case S:
				if (ch=='G')
					current=G;
				break;
			case G:
				if (ch=='G')
					current=G;
				else if (ch=='C')
					current=C;
				else
					current=S;
				break;
			case C:
				if (ch=='G')
					current=G;
				else if (ch=='A')
					current=A;
				else
					current=S;
				break;
			case A:
				if (ch=='G') {
					matchLocation = (i-3);
					printf("Contiguous match starts at: %d \n", matchLocation);
					return t+matchLocation; // gives location of match beginning
				} else
					current=S;
				break;
		}
		i++;
		ch=*(t+i);
	}

	printf("No contiguous match\n");
	return NULL;

}

char * findMatchNC(char *t) {

	enum State current = S;
	char ch=*t;
	int i=0, matchLocation;
	int skippedChars=0;

	while(ch!='\0') {
		switch(current) {
			case S:
				if (ch=='G') {
					current=G;
					matchLocation=i;
				}
				break;
			case G:
				if (ch=='C')
					current=C;
				else
					skippedChars++;
				break;
			case C:
				if (ch=='A')
					current=A;
				else
					skippedChars++;
				break;
			case A:
				if (ch=='G') {
					printf("Non-contiguous match starts at: %d \n", matchLocation);
					if (skippedChars>10)
						printf("Not accurate because skipped %d chars \n", 								skippedChars);
					else
						printf("Had to skip %d chars \n", skippedChars);
					return t+matchLocation; // gives location of match beginning
				}
				else
					skippedChars++;
				break;
		}
		i++;
		ch=*(t+i);
	}

	printf("No non-contiguous match\n");
	return NULL;

}

int matchCount(char *t) {

	enum State current = S;
	char ch=*t;
	int i=0, numMatches=0;

	while(ch!='\0') {
		switch(current) {
			case S:
				if (ch=='G')
					current=G;
				break;
			case G:
				if (ch=='G')
					current=G;
				else if (ch=='C')
					current=C;
				else
					current=S;
				break;
			case C:
				if (ch=='G')
					current=G;
				else if (ch=='A')
					current=A;
				else
					current=S;
				break;
			case A:
				if (ch=='G') {
					current=G;
					numMatches++;
					//return t+matchLocation; // gives location of match beginning
				} else
					current=S;
				break;
		}
		i++;
		ch=*(t+i);
	}
	return numMatches;
}
