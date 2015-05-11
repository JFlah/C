#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mystring.h"

// allocate the requested space and check the result
void *mymalloc (int size) {
  void *result = malloc (size);

  // assert is a quick and dirty way to do error-checking
  assert (result != NULL);
  return result;
}

String *make_string()
{
	char *a,b;
	int i,size=0;
	String *new = (String *) malloc (sizeof(String));
	a = new->chars;//problem, only created space for struct not the dynamic array in struct
	b = getchar();
	puts("hyyyh");
	while( b != '\n' && size < MAX)
    {		
		*(a+size) = b;  //remember at this point size = 0
		puts("ttt");
		size++;
		b = getchar();
    }
	puts("hhh");
	*(a+size) = '\0';  //end of string marker so no need to return the size directly
	new->len = strlen(new->chars);
	return new;
}

void print_string(String *s)
{
  printf("%s\n", s->chars);
}

int string_length(String *s)
{
  return s->len;
}

char string_charAt(String *s, int index)
{
  assert(index>=0 && index<s->len);
  return s->chars[index];
}

String *string_concat(String *s1, String *s2)
{
  char *chars = (char *) malloc (string_length(s1) + string_length(s2) + 1);
  strcpy(chars, s1->chars);
  strcpy(chars+string_length(s1), s2->chars);
  return make_string(chars);
}

int string_indexOf(String *s, String *sub, int from)
{
  char *p = strstr(s->chars+from, sub->chars);
  if (p == NULL) {
    return -1;
  } else {
    return (int)p - (int)s->chars;
  } 
}

String *string_substring(String *s, int from, int to)
{
  int n = to - from;
  char *chars = (char *) malloc ((n+1) * sizeof(char));
  strncpy(chars, s->chars+from, n);
  chars[n] = '\0';
  return make_string(chars);
}

int string_split(String *s, String *delim, String **array, int n)
{
  int i = 0;
  int from = 0;
  int to;

  for(i=0; i<n; i++) {
    to = string_indexOf(s, delim, from);
    if (to == -1) break;
    array[i] = string_substring(s, from, to);
    from = to + string_length(delim);
  }
  array[i] = string_substring(s, from, string_length(s));
  return i+1;
}

int string_compare(String *s1, String *s2)
{
  return strcmp(s1->chars, s2->chars);
}

int string_qsort_compare(const void *p1, const void *p2)
{
  String **sp1 = (String **) p1;
  String **sp2 = (String **) p2;
  return string_compare(*sp1, *sp2);
}

void string_sort(String *strings[], int n)
{
  qsort(strings, n, sizeof(String *), string_qsort_compare);
}

