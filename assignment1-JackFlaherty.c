// HW1 Jack Flaherty
// Program which recognizes comments /*comment*/ in a given string and will remove comment from string, return given string without comment

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getLine(char *line);
void printLine(char *line, int size);
void printFilter(char *line, int size);

enum StateType {BeforeCmt, BtwnBegin, InCmt, InStr, BtwnEnd};


int main() {
	char m[80];
	char *a;
	a=m;
	int i,size=0;
	printf("Give me a string : ");
	size = getLine(m);
	printLine(a, size);
	printFilter(a, size);

}

int getLine(char *line){
	char *a,b;
	int size=0;
	a=line;
	b=getchar();
	while (b != '\n' && size < 80) {
		*(a+size) = b; // size=0 first loop

		size++;
		b = getchar();
	}
	return size;
}

void printLine(char *line, int size) {
	int i;
	printf("You gave me: ");
	for (i=0; i < size; i++) {
		printf("%c", *(line+i));
	}
printf("\n");
}

void printFilter(char *line, int size) {
	int i=0;
	char ch,*a;
	a=line;
	enum StateType current = BeforeCmt;

	while (i<size) {
		ch = *(a+i);

		switch (current) {
			case BeforeCmt:
				if (ch=='/')
					current = BtwnBegin;
				else if (ch=='"') {
					current = InStr;
					printf("%c", ch);
				}
				else
					printf("%c", ch);
				break;
			case BtwnBegin:
				if (ch=='*')
					current = InCmt;
				else if (ch=='/')
					printf("/");
				else if (ch=='"') {
					current = InStr;
					printf("/%c", ch);
				}
				else {
					current = BeforeCmt;
					printf("/%c", ch);
				}
				break;
			case InCmt:
				if (ch=='*')
					current = BtwnEnd;
				break;
			case BtwnEnd:
				if (ch=='/') {
					current = BeforeCmt;
					printf(" ");
				}
				else if (ch=='*')
					current = current;
				else
					current = InCmt;
				break;
			case InStr:
				if (ch=='"')
					current = BeforeCmt;
				printf("%c", ch);

		}
		i++;
	}
	printf("\n");
	if (current == InCmt)
		printf("Error: Unterminated comment\n");
	else if (current == BtwnEnd)
		printf("Error: unterminated comment\n");
	else if (current == InStr)
		printf("Error: unterminated string\n");
}




