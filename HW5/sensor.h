/* 
 *
 *	sensor.h
 *
 *	Jack Flaherty
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "dlinkedlist.h"

typedef struct sensor {
	int id;
	int seed;
} sensor_t;

dlist sensList;
int NUM, countRd, countCy;

pthread_cond_t sWait;
pthread_mutex_t insert_lock;

sensor_t * newSensor(int seed, int id);

void startSensList();

void activSens(sensor_t * sensor);

void readSens(sensor_t * sensor);

double getTempAvg(dlist dList);