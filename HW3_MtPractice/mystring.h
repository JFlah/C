#define MAX 16

typedef struct {
  char *chars;
  int len;
} String;

String *make_string();
void print_string(String *s);
int string_length(String *s);
char string_charAt(String *s, int index);
String *string_concat(String *s1, String *s2);
int string_indexOf(String *s, String *sub, int from);
String *string_substring(String *s, int from, int to);
int string_split(String *s, String *delim, String **array, int n);
int string_compare(String *s1, String *s2);
//int string_qsort_compare(const void *p1, const void *p2)
void string_sort(String *strings[], int n);
