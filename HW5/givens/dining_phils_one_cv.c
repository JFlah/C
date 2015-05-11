#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

#define MAX_PHILOSOPHERS 50

void pickup(int j);
void putdown(int i); 
void test(int k);
void philosopher(int * id);  //this is the thread


pthread_mutex_t lock;  /* mutex ensuring exclusive access to buffer */

char state[MAX_PHILOSOPHERS];    
pthread_cond_t self;
int num_phil;

int main(int argc,char *argv[]){
  int n, *who;
  pthread_t phils[MAX_PHILOSOPHERS];
  void * retval;

  if(argc != 2) {
    printf("error!!!!\n");
    puts("usage: phil number_of_philosophers, ex phil 5\n");
    exit(0);
  }    
  num_phil = atoi(argv[1]);
  printf("# of phils is %d\n",num_phil);
  pthread_mutex_init(&lock, NULL);
  for (n = 0;n<num_phil;n++){
    state[n] = 't';
  }
  pthread_cond_init(&self, NULL);
  for (n = 0;n<num_phil;n++){
    //pthread_cond_init(&self, NULL);
    who = (int *)malloc(sizeof(int));
    *who = n;
    if (pthread_create(&(phils[n]), NULL, (void *)philosopher, who) != 0) {
      perror("pthread_create");
      exit(1);
    }
  }
  pthread_join(phils[0],NULL);
  return 0;
}
void pickup(int j){
  printf("phil %d is trying to pickup\n",j);
  pthread_mutex_lock(&lock);
  state[j] = 'h';
  test(j);
  while( state[j] != 'e'){
	    pthread_cond_wait(&self, &lock);  //blocks on cv self, and frees the lock
      test(j);  //????
  }
  pthread_mutex_unlock(&lock);
  return;
}
void putdown(int i){
  printf("phil %d is putting down\n",i);
  state[i] = 't';
  pthread_cond_broadcast(&self);
  //test((i+(num_phil-1)) % num_phil);  //????
  //test((i+1) % num_phil);             //????
}
void test(int k){
  //while
  if( (state[(k+(num_phil-1)) % num_phil] != 'e') && ( state[k] == 'h') && (state[(k+1) % num_phil] != 'e') ){
          state[k] = 'e';
          //pthread_cond_broadcast(&self);  //???
  } 
}
void philosopher(int * id){
  int n=0;
  printf("i am phil %d\n",*id);
  sleep(1);
  while(n < 10){
    pickup(*id);  //this will block
    printf("Philosopher %d is eating\n",*id);
    sleep(1);
    putdown(*id);
    printf("Philosopher %d is thinking\n",*id);
    sleep(1);
    n++;
  }
  return;
}
