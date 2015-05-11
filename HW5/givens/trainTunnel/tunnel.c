/**
 * tunnel.c
 *
 * This class contains the methods called by the  trains.
 *
 */
#include "tunnel.h"

void TunnelController()
   {
      northBoundCount = 0;
      southBoundCount = 0;
      northBound = 0;
      southBound = 0;
   }

void enterTunnelNorthBound(int t) {
      pthread_mutex_lock(&lock);

      while (southBound == 1) {
          printf("Northbound Train %d must block\n",t);
          pthread_cond_wait(&self, &lock);
      }  
      
      // ok, we can enter the tunnel now.
      
      ++northBoundCount;

      // if I'm the first north-bound train, set the flag
      if (northBoundCount == 1)
         northBound = 1;
      pthread_mutex_unlock(&lock);   
   }
             
void enterTunnelSouthBound(int t) {
      pthread_mutex_lock(&lock);

      while (northBound == 1) {
         printf("Southbound Train %d must block\n",t);
         pthread_cond_wait(&self, &lock);
      }  
      
      // ok, we can enter the tunnel now.
      
      ++southBoundCount;

      // if I'm the first south-bound train, set the flag
      if (southBoundCount == 1)
         southBound = 1;
      pthread_mutex_unlock(&lock);   
   }

void exitTunnelNorthBound(int t) {
     pthread_mutex_lock(&lock);
      --northBoundCount;
      
    if (northBoundCount == 0){
      northBound = 0;
      printf("LAST Northbound Train gone\n");
    }
      pthread_cond_broadcast(&self);
      pthread_mutex_unlock(&lock);
   }

void exitTunnelSouthBound(int t) {
      pthread_mutex_lock(&lock);
      --southBoundCount;
      
	if (southBoundCount == 0){
		southBound = 0;
		printf("LAST Southbound Train gone\n");
	}
      pthread_cond_broadcast(&self);
      pthread_mutex_unlock(&lock);
   }
