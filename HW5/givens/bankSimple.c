#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include <sys/types.h>

#define MAX_CUST 25

pthread_mutex_t bankSem;  /* mutex ensuring exclusive access to buffer */

int num_customers;
int balance;

typedef struct {
  int id;
  int type;
  int amount;
}cust_struct;



void deposit(int i,int amt);
void withdraw(int i,int amt);
void cust(cust_struct * info);

int main(int argc,char *argv[]){
  int n,type;
  cust_struct *info;
  pthread_t cus[MAX_CUST];
  void * retval;
  int stime;
  long ltime;

  if(argc != 3) {
    printf("error!!!!\n");
    puts("usage: bank number_of_customers initial_balance, ex bank 5 500\n");
    exit(0);
  }    
  num_customers = atoi(argv[1]);
  balance =  atoi(argv[2]);

  printf("# of customers are: %d\n",num_customers);
  printf("the initial balance is: $%d.00\n",balance);
  pthread_mutex_init(&bankSem, NULL);

  
  ltime = time(NULL);
  stime = (unsigned) ltime/2;
  srand(stime);
  
  for (n = 0;n<num_customers;n++){
    info = (cust_struct *)malloc(sizeof(cust_struct));
    info->id = n;
    info->type = (rand()%200)/100; //0 => deposit, 1 => withdrawal
    info->amount= rand()%400 + 1;
    if (pthread_create(&(cus[n]), NULL, (void *)cust, info) != 0) {
      perror("pthread_create");
      exit(1);
    }
  }
  for (n = 0;n<num_customers;n++){
    pthread_join(cus[n],NULL);
  }
  return 0;
}
void withdraw(int i,int amt){
  pthread_mutex_lock(&bankSem);
  printf("customer %d is trying to withdraw $%d.00,\n",i,amt);
  if( balance < amt){
    printf("not enough funds, withdrawer %d will need to go away\n",i);
    printf("---------------------------------------------\n");
  }
  else {
    printf("customer %d is withdrawing from balance = $%d.00 an amt = $%d.00\n",i,balance,amt);
    balance = balance - amt;
    printf("new balance is $%d.00.\n",balance);
  }
  pthread_mutex_unlock(&bankSem);
  return;
}

void deposit(int i,int amt){
  
  pthread_mutex_lock(&bankSem);
  printf("cust %d is depositing $%d.00 into balance process\n",i, amt);
  balance = balance + amt;
  printf("new balance is $%d.00.\n",balance);
  printf("---------------------------------------------\n");
  pthread_mutex_unlock(&bankSem);
  return;
}

void cust(cust_struct * info){
  int n=0;
  switch(info->type){
  case 0:{
    printf("I am a depositor, ID=%d, amount = $%d.00 \n",
	   info->id,info->amount);
     deposit(info->id,info->amount);
     pthread_exit(NULL);
  }
  case 1:{
      printf("I am a withdrawer, ID=%d, amount = $%d.00 \n",
      info->id,info->amount);
      withdraw(info->id,info->amount);
      pthread_exit(NULL);
  }
  }
}
