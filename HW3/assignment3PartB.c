
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "definitions.h"

  
int main() {
  char *line;
  String *S;
  int lineNum=0;
  stringContainer_t *scHead = NULL, *scTemp;
  String * newString;
  word_t * W, *wdHead=NULL, *mstFrq;
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
  scTemp=scHead;
  while(scTemp!=NULL){
  	wdHead = processLine(wdHead, scTemp->strg, lineNum);
  	scTemp = scTemp->next;
  	lineNum++;
  }
  displayWordList(wdHead);
  mstFrq = findMostFrequent(wdHead);
  printf("Most Frequent: %s\n", mstFrq->w);
  return 0;
}
