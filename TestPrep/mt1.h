enum StateType {IN, OUT};

typedef struct String{
		char *letters;
		struct String *nextStr;
		int len;
}String_t;

char * findMatch(String_t *pattern, String_t *text);
int totalLen(String_t *head);
String_t * makeString(char *letters); // constructor
String_t * addStrLink(String_t *head, char *letters);
void printList(String_t *head);

