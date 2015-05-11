/**
 * trains.c
 *
 * This class contains the functiond for the train threads.
 *
 */
#include "trains.h"
#include <unistd.h>

void NorthBound(int *t)
{
	int trainNum;
	trainNum = *t;
	
	printf("NorthBound Train %d wants to enter the tunnel\n",trainNum);
	enterTunnelNorthBound(trainNum);
	
	// you can enter the tunnel
	printf("NorthBound Train %d is in the tunnel\n",trainNum);      
	
	sleep(2);//train chugging along
	
	printf("NorthBound Train %d is exiting the tunnel\n",trainNum);        
	exitTunnelNorthBound(trainNum);
	pthread_exit(NULL);
}  

void SouthBound(int *t)
{
	int trainNum;
	trainNum = *t;
	
	printf("SouthBound Train %d wants to enter the tunnel\n",trainNum);
	enterTunnelSouthBound(trainNum);
	
	// you can enter the tunnel
	printf("SouthBound Train %d is in the tunnel\n",trainNum);  
    
	sleep(2);//train chugging along
	
	printf("SouthBound Train %d is exiting the tunnel\n",trainNum);        
	exitTunnelSouthBound(trainNum);
	pthread_exit(NULL);
}