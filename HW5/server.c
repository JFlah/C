/* 
 *
 *	server.c
 *
 *	Jack Flaherty
 *
 */

#include "sensor.h"

int main(int argc, char *argv[]){
	int i;
	int st;
	long lt;

	// create the dlist and mutex
	startSensList();

	// if a number of sensors is not input
	if (argc != 2){
		puts("Invalid use");
		puts("Use: temperature numSensors");
		exit(0);
	}

	lt = time(NULL);
	st = (unsigned) lt/2;
	srand(st);

	NUM = atoi(argv[1]);
	pthread_t snsrs[NUM];


	for (i = 0; i < NUM; i++){
		sensor_t * sens = newSensor(rand()%100, i);
		if (pthread_create(&(snsrs[i]), NULL, (void *) activSens, sens)){
			perror("thread created");
			exit(1);
		}
	}

	for (i = 0; i < NUM; i++){
		pthread_join(snsrs[i], NULL);
	}

	printf("Num Sensors: %d\n", NUM);
	puts("All threads made!");
}