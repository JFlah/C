#include "definitions.h"

//functions for reading from a file
int test_eol(char a){
  if (a == '\n')
    return TRUE;
  else
    return FALSE;
}
int test_eof(char a){
  if (a == EOF)
    return TRUE;
  else
    return FALSE;
}

char * returnLine(FILE *fp){  //returns line or NULL (if at end of file)
  char c;
  char *line;
  int size=0;
  line = NULL;
  line = realloc(line,sizeof(char));
  c = fgetc(fp);  //read in first char of first line of the file
  if (test_eof(c))  //at end of the file
    return NULL;
  while (!test_eol(c)){//read the line
    *(line+size) = c;
    size++;
    line = realloc(line,sizeof(char)* (size+1));
    c = fgetc(fp);
  }
  *(line+size) = '\0';
  return line;
}


void printLine(char *line){
  int i=0;
  while (*(line+i) != '\0'){
    printf("%c",*(line+i)); //no end of line
    i++;
  }
  printf("\n");
}


//functions for creating a String
String * makeString(char * s) //pass in a pointer to a block of chars
{
  String *new = (String *) malloc (sizeof(String)); //create memory for String
  new->strg = (char *) malloc(sizeof(char) * strlen(s)); //create memory for chars in String
  strcpy(new->strg,s);  //copy the passsed chars to field in String
  new->len = strlen(new->strg);
  return new; //return filled in Sreing struct
}

void printString(String *s){
  char * c;
  int i=0;
  c = s->strg;  //point to the start of the chars in the String struct
  
  while (*(c+i) != '\0'){
    printf("%c",*(c+i)); //no end of line
    i++;
  }
  printf("\n");
}


int stringLength(String *s)
{
  return s->len;
}

stringContainer_t * insertStringIntoLinkedList(stringContainer_t * head, String * newString){
  //insert new Sting at the end of list
  stringContainer_t *q;
  stringContainer_t * newContainer;
  newContainer = (stringContainer_t *) malloc(sizeof(stringContainer_t *));
  newContainer->strg = newString;
  newContainer->next = NULL;
  if (head == NULL){
    head = newContainer;
    return head;
  }
  q = head;
  while (q->next != NULL){
    q=q->next;
  }
  q->next = newContainer;
  return head;
}

word_t * findMostFrequent(word_t *head){
    word_t *tmp=head, *mstFrq=head;
    while (tmp!=NULL)
    {
        if (mstFrq->frq < tmp->frq){
            mstFrq = tmp;
        }
        tmp=tmp->next;
    }
    return mstFrq;
}

void displayStringList(stringContainer_t * head){
  String *r;
  stringContainer_t * tmp;
  if (head == NULL){
    printf("No strings in list\n");
    return;
  }
  tmp = head;
  /*
   no need to reserve memory here, r will point to
   memory locations that are reserved for the linked list
   */
  
  printf("list of lines:\n");
  while (tmp != NULL){
    r = tmp->strg;
    printString(r);  //see above function
    tmp=tmp->next;
  }
  //printf("\n");
  return;
}


//functions for creating a word
word_t * createWord(char * w){
  word_t * tmp;
  int size = strlen(w);
  tmp = malloc(sizeof(word_t));
  tmp->frq = 1;
  tmp->next = NULL;
  tmp->lines = NULL;
  tmp->LC = 0;
  tmp->length = size;
  tmp->w = (char *) malloc(sizeof(char)*tmp->length+1);
  strcpy(tmp->w, w);
  return tmp;
}

void printWord(word_t *m){
  int i=0;
  char *c;
  c = m->w; //point to the start of the chars in the word struct
  
  while (*(c+i) != '\0'){
    printf("%c",*(c+i)); //no end of line
    i++;
  }
  printf("\n");
  return;
}


void displayWordList(word_t * head){
  word_t *r=head;
  if (head == NULL){
    printf("No words in list\n");
    return;
  }
  /*
   no need to reserve memory here, r will point to
   memory locations that are reserved for the linked list
  */
  
  printf("the list of words:\n");
  while (r != NULL){
    printWord(r);  //see above function
    printf("\tFreq: %d\tLinesNum: %d\t Lines: ", r->frq, r->LC);
    printLines(r->lines, r->LC);
    printf("\n");
    r=r->next;
  }
  printf("\n");
  return;
}

word_t * processLine(word_t *head, String *str, int line){
  int i = 0;
  word_t *tmp;
  char *wd= str->strg;
  char *strng= str->strg; 
	
  while(*(strng+i) != '\0'){  // string -> word containers
    if(*(strng+i) == ' '){
    	*(strng+i) = '\0';
      	tmp=createWord(wd);
      	wd = (strng+i+1);
      	
// puts word container in linked list
      	
        head = putWordLinkedList(head, tmp, line);
    } 
  i++;
  }
  
  tmp=createWord(wd);
  wd = (strng+i+1);
 // puts word container in linked list
  head = putWordLinkedList(head, tmp, line);
  return head;
}

void addLine(word_t **word, int line) {
    (*word)->LC++;
    (*word)->lines = (int *)realloc((*word)->lines, (*word)->LC);
    *((*word)->lines + (*word)->LC-1)=line;
}

word_t * putWordLinkedList(word_t *head, word_t *newWord, int line){
  word_t *tmp=head;
  if (head==NULL){
  	head = newWord;
    addLine(&head, line);
    return head;
  }
  while( tmp->next != NULL){ // check for words in list
    if(strcmp(tmp->w,newWord->w)==0){
    	tmp->frq++;
      	if (tmp->lines==NULL || hasLine(tmp, line)==0){
              addLine(&tmp, line);
        }
    return head;
    } 
  //move tmp forward 1
    tmp = tmp->next;
  }
  if(strcmp(tmp->w,newWord->w)==0){ //check words are same
    	tmp->frq++;
      	if (tmp->lines==NULL || hasLine(tmp, line)==0){
              addLine(&tmp, line);
        }
        return head;
  }
  tmp->next = newWord;
  addLine(&newWord, line);
  return head;
}

void printLines(int *lines, int LC){
    int i=0;
    while (i<LC)
    {
        printf("%d ", *(lines+i));
        i++;
    }
}

int hasLine(word_t *word, int line) {
    int i=0, *l = word->lines;
    while (i < word->LC)
    {
        if (*(l+i)==line)
          return 1;
        i++;
    }
    return 0;
}
