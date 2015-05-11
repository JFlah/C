/*
 *  definitions.h
 *  
 *
 *  Created by SIGNORILE,ROBERT P on 2/15/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

/* a potential node definition */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define TRUE 1
#define FALSE 0

typedef struct word{
  char *w;
  int length;
  int *lines;
  int LC;
  int frq;
  struct word *next;
}word_t;

typedef struct string{
  char *strg;
  int len;
}String;

typedef struct wordContainer{
  word_t *wd;
  struct wordContainer *next;
}wordContainer_t;

typedef struct stringContainer{
  String *strg;
  struct stringContainer *next;
}stringContainer_t;


//functions for reading from a file
int test_eol(char a);
int test_eof(char a);
char * returnLine(FILE *fp);  //returns line or NULL (if at end of file)
void printLine(char *line);

//functions for creating a  String
String *makeString(char * s);
void printString(String *s);
int stringLength(String *s);
stringContainer_t *  insertStringIntoLinkedList(stringContainer_t * head, String * newString);
void displayStringList(stringContainer_t * head);

//functions for creating a word
word_t * createWord(char * w);
void printWord(word_t *m);
//wordContainer_t *  putWordLinkedList(wordContainer_t * head, word_t * newWord);
void displayWordList(word_t * head);

word_t * processLine(word_t *head, String *str, int line);
word_t * putWordLinkedList(word_t *head, word_t *newWord, int line);
void addLine(word_t **word, int line);
word_t * findMostFrequent(word_t *head);
int hasLine(word_t *word, int line);
void printLines(int *lines, int LC);


