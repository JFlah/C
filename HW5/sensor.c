/* 
 *
 *	sensor.c
 *
 *	Jack Flaherty
 *
 */

#include "sensor.h"

sensor_t * newSensor(int seed, int id){
	sensor_t * sens = (sensor_t *)malloc(sizeof(sensor_t));
	sens->seed = seed;
	sens->id = id;
	return sens;
}

void startSensList(){
	pthread_mutex_init(&insert_lock, NULL);
	pthread_cond_init(&sWait, NULL);
	sensList = (dlist)malloc(sizeof(dlist_t));
	countCy = 0;
	countRd = 0;
}

void activSens(sensor_t * sensor){
	double avg;
	int i = 0;
	printf("Sensor %d is on\n", sensor->id);

	for (i = 0; i < 10; i++){
		// this lock means that only 1 thread at a time can act on the LL
		pthread_mutex_lock(&insert_lock);
		readSens(sensor);
		countRd++;
		sleep(1);

		if (countRd==NUM){
			countCy++;
			pthread_cond_broadcast(&sWait);
			countRd=0;
			printf("\nCycle %d:\n", countCy);
			printf("Readings: ", countCy);
			forwardTraverse(sensList, toString);
			avg = getTempAvg(sensList);
			printf("Avg (F): %f\n\n", avg);
			freeList(sensList);

		}
		// This loop is where the threads cue up, makes share all only act once per cycle
		while (i == countCy){
			pthread_cond_wait(&sWait, &insert_lock);
		}
		// unlocks the data structure so next thread can do stuff to it in cycle
		pthread_mutex_unlock(&insert_lock);
	}

	pthread_exit(NULL);
}

void readSens(sensor_t * sensor){
	int * read = (int *) malloc(sizeof(int));
    int seed = sensor->seed;
	* read = rand()%100+1;
	addToEnd(sensList, read);
	printf("Sensor %d read: %d\n", sensor->id, * read);
}

double getTempAvg(dlist dList){
	int i=0;
	double sum=0;
	node_t * current = dList->head;
	while (current != NULL)
	{
		int * temp = (int *) current->item;
		sum+=(double)* temp;
		current = current->next;
		i++;
	}
	return sum/(double)NUM;
}