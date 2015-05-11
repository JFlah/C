#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

#define MAX_CUST 25

pthread_mutex_t lock;  /* mutex ensuring exclusive access to buffer */

pthread_cond_t self;
int num_customers;
int balance;
int d=0,w=0;

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
    puts("usage: atm number_of_customers initial_balance, ex atm 5 500\n");
    exit(0);
  }    
  num_customers = atoi(argv[1]);
  balance =  atoi(argv[2]);

  printf("# of customers are: %d\n",num_customers);
  printf("the initial balance is: $%d.00\n",balance);
  pthread_mutex_init(&lock, NULL);
  
  pthread_cond_init(&self, NULL);
  
  ltime = time(NULL);
  stime = (unsigned) ltime/2;
  srand(stime);
  
  for (n = 0;n<num_customers;n++){
    info = (cust_struct *)malloc(sizeof(cust_struct));
    info->id = n;
    info->type = (rand()%200)/100; //0 => deposit, 1 => withdrawal
    if(info->type == 0)
      d = d + 1;
    else
      w = w + 1;
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
  //printf("there are %d withdraw threads\n",w);
  printf("customer %d is trying to withdraw $%d.00\n",i,amt);
  pthread_mutex_lock(&lock);
  
  while( balance < amt){
    printf("not enough funds, withdrawer %d will wait\n",i);  //uses my fake id, could use pthread_self()
    printf("---------------------------------------------\n");
    if (d == 0){
      printf("I am withdrawer id=%d\n",i);
      printf("not enough funds and no deposters left: balance = $%d.00, amt = $%d.00\n",balance,amt);
      pthread_mutex_unlock(&lock);
      return;
    }
    printf("---------------------------------------------\n");
    pthread_cond_wait(&self, &lock);
  }
  printf("customer %d is withdrawing from balance = $%d.00 an amt = $%d.00\n",
	 i,balance,amt);
  balance = balance - amt;
  printf("new balance is $%d.00.\n",balance);
  printf("---------------------------------------------\n");
  w = w - 1;
  /* pthread_cond_wait reacquired lock before returning */  
  pthread_mutex_unlock(&lock);
  return;
}
void deposit(int i,int amt){
  //printf("there are %d depositors\n",d);
  printf("cust %d is depositing $%d.00 into balance.\n",i, amt);
  pthread_mutex_lock(&lock);
  balance = balance + amt;
  d = d - 1;
  printf("new balance is $%d.00. number of depositers reamining: %d\n",balance,d);
  printf("---------------------------------------------\n");
 
  pthread_mutex_unlock(&lock);
  pthread_cond_broadcast(&self);
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
/*
cs-signoril:threads signoril$ gcc atm.c -lpthread
cs-signoril:threads signoril$ ./a.out
error!!!!
usage: atm number_of_customers initial_balance, ex atm 5 500

cs-signoril:threads signoril$ ./a.out  5 500
# of customers are: 5
the initial balance is: $500.00
I am a withdrawer, ID=0, amount = $268.00 
customer 0 is trying to withdraw $268.00
customer 0 is withdrawing from balance = $500.00 an amt = $268.00
new balance is $232.00.
---------------------------------------------
I am a withdrawer, ID=1, amount = $143.00 
customer 1 is trying to withdraw $143.00
customer 1 is withdrawing from balance = $232.00 an amt = $143.00
I am a depositor, ID=2, amount = $63.00 
new balance is $89.00.
I am a withdrawer, ID=3, amount = $9.00 
I am a withdrawer, ID=4, amount = $188.00 
cust 2 is depositing $63.00 into balance.
---------------------------------------------
customer 3 is trying to withdraw $9.00
customer 4 is trying to withdraw $188.00
new balance is $152.00. d=1
---------------------------------------------
customer 3 is withdrawing from balance = $152.00 an amt = $9.00
new balance is $143.00.
---------------------------------------------
not enough funds, withdrawer 4 will wait
---------------------------------------------
I am withdrawer id=4
not enough funds and no deposters left: balance = $143.00, amt = $188.00
cs-signoril:threads signoril$ 
*/
