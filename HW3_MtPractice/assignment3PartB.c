
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "definitions.h"

  
int main() {
  char *line;
  String *S;
  stringContainer_t *scHead = NULL;
  String * newString;
  word_t * W;
  FILE *fp;
  
  /* opening file for reading */
  fp = fopen("poem.txt" , "r");
  if(fp == NULL) {
    perror("Error opening file");
    return(-1);
  }
  
  line = returnLine(fp); //now you have a nice line, so play with it
  while(line != NULL){
    //printLine(line);
    newString = makeString(line);
    //printString(newString);
    scHead = insertStringIntoLinkedList(scHead, newString);
    line = returnLine(fp);//now you have a nice line, so play with it
  }
  fclose(fp);
  displayStringList(scHead);
  return 0;
}
