/**
 * tunnel.h
 *
 * This class contains the methods called by the  trains.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include "pthread.h"

pthread_mutex_t lock;  /* mutex ensuring exclusive access to buffer */
pthread_cond_t self;

int northBoundCount ;
int southBoundCount ;
int northBound ;
int southBound ;

void TunnelController();

void enterTunnelNorthBound(int t) ;
             
void enterTunnelSouthBound(int t) ;

void exitTunnelNorthBound(int t) ;

void exitTunnelSouthBound(int t) ;
