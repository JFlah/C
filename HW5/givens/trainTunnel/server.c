/**
 * Server.c
 *
 * This creates the trains and then eats a donut before
 * creating another.
 *
 */


#include "tunnel.h"
#include "trains.h"


#define NUM_OF_TRAINS 10

void NorthBound(int *t);
void SouthBound(int *t);

int main()
   {
      int n = 0,*who;
      int count = 0;
	   
	  srand(time(NULL));
      pthread_t trains[NUM_OF_TRAINS];
      pthread_mutex_init(&lock, NULL);
      pthread_cond_init(&self, NULL);

      TunnelController();
      
      while (count < NUM_OF_TRAINS) {
         
         n = (rand()/10000)%2;
 
          who = (int *)malloc(sizeof(int));
         *who = count;
         if (n == 1) {
	     //north train
           pthread_create(&(trains[count]), NULL, (void *)NorthBound, who);
		   
         }
         else {
           //south train
            pthread_create(&(trains[count]), NULL, (void *)SouthBound, who);
         }
         ++count;
      }
     for(count=0;count<NUM_OF_TRAINS;count++)
	     pthread_join(trains[count],NULL);
     puts("all done, bye bye");
     exit(0);
  }
