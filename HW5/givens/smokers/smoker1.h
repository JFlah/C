/*
 *  smoker1.h
 *  
 *
 *  Created by SIGNORILE,ROBERT P.
 *  
 *
 */
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

void smoker(int * id);  //all smoker threads execute this function
void agent(int * times); // the agent thread
void canThreadContinue(int id);
int whoseTurn();

pthread_cond_t self;

pthread_mutex_t TABLE;
pthread_t sm[3];
pthread_t ag;

//int turn;  //global variable define it here, assign value in main()

int tobacco, matches, paper; //global variables define it here, assign value in main()