#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t self;

typedef struct {
	char *msg;
	int sleeptime;
} thread_struct;

void simpleThread();
thread_struct * makeStruct(char *msg, int sleeptime); // constructor

int main() {
	pthread_t threads[2]; // initializes 2 threads

	pthread_mutex_init(&lock, NULL);

	thread_struct *test_struct1 = makeStruct("Heyo", 2);
	thread_struct *test_struct2 = makeStruct("Hi", 1);
	printf("%s is the message 1\n", test_struct1->msg);
	printf("%d is the sleeptime 1\n", test_struct1->sleeptime);

	// make the thread(s)
	if(pthread_create(&(threads[0]), NULL, (void *)simpleThread, test_struct1) != 0){
		perror("pthread error");
		exit(1);
	}
	simpleThread(test_struct2);

}

thread_struct * makeStruct(char *msg, int sleeptime){
	thread_struct *mystruct = (thread_struct *)malloc(sizeof(thread_struct));
	int msgLength = strlen(msg);
	mystruct->msg = (char *)malloc(sizeof(char)*msgLength); // making space for msg
	mystruct->sleeptime = sleeptime; // put sleeptime in
	strcpy(mystruct->msg, msg); // copy actual msg into space malloc'd
	return mystruct;
}

void simpleThread(thread_struct *ts){
	int i = 0;
	while (i++ < 10){
		pthread_mutex_lock(&lock);
		printf("Thread Message: %s\n", ts->msg);
		sleep(ts->sleeptime);
		pthread_mutex_unlock(&lock);
		sleep(1);
	}


}