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
  int freq;
}word_t;

typedef struct string{
  char *stng;
  int len;
}String;

typedef struct wordContainer{
  word_t *wd;
  struct wordContainer *next;
}wordContainer_t;

typedef struct stringContainer{
  String *str;
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
wordContainer_t *  insertWordIntoLinkedList(wordContainer_t * head, word_t * newWord);
void displayWordList(wordContainer_t * head);

