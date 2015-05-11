#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <ctype.h>

#include <sys/wait.h>
#include <sys/types.h>


#define SEQEND "eof"
#define SEQENDLENGTH 4

#define MAX_LINE 80


// Text manipulation
void caseSwitch(char *line);
int isChar(char c);

// The processes
void p1();
void p2();
void p3();

// File stuff/demo code
int test_eol(char a);
int test_eof(char a);
char * returnLine(FILE *fp);

// This closes all existing pipes
void closeAllPipes();