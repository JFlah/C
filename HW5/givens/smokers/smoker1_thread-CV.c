
/*
 *  smoker1_thread-CV.c
 *
 *
 *  Created by SIGNORILE,ROBERT P
 *
 */

#include "smoker1.h"

int main (int argc,char *argv[]) {
  int i;
  int * who,*times;
  
  int stime;
  long ltime;
  ltime = time(NULL);
  stime = (unsigned) ltime/2;
  srand(ltime);
  
  //turn  = 0;  //assign value for global variable
  tobacco = 0; matches = 0; paper= 0;
  
  if(argc < 2 ) {
    printf("USAGE: smk # of times agents runs\n");
    exit(1);
  }
  //create the conditional variable
  pthread_cond_init(&self, NULL);
  
  
  /* Create THE MONITOR MUTEX  */
  if (pthread_mutex_init(&TABLE, NULL)) {
    perror("pthread_mutex_init");
    exit(1);
  }
  
  /* Create an agent thread */
  if((times = (int *)malloc(sizeof(int))) == NULL) {
    /* I am using malloc as a way to make sure that each
     * thread uses different memory
     */
    perror("malloc");
    exit(1);
  }
  *times = atoi(argv[1]);
  if (pthread_create(&(ag), NULL, (void *)agent, times ) != 0) {
    perror("pthread_create");
    exit(1);
  }
  
  /* Create some smokers threads */
  for (i=0; i < 3; i++) {
    if((who = (int *)malloc(sizeof(int))) == NULL) {
      /* I am using malloc as a way to make sure that each
       * thread uses different memory
       */
      perror("malloc");
      exit(1);
    }
    *who = i+1;//remember, 1 = tobacco, 2= matches, 3 = paper , save 0 for agent
    if (pthread_create(&(sm[i]), NULL, (void *)smoker, who) != 0) {
      perror("pthread_create");
      exit(1);
    }
  }
  
  pthread_join(ag, NULL); /* Wait for agent thread to die */
  printf("Thread agent has terminated\n");
  printf("main is going now, time to kill off smokers\n");
  for (i=0; i < 3; i++) {
    pthread_kill(sm[i], 0);
    switch(i){
    case 0:
      printf("smoker %d (that is tobacco) terminated\n",i);
      break;
    case 1:
      printf("smoker %d (that is matches) terminated\n",i);
      break;
    case 2:
      printf("smoker %d (that is paper) terminated\n",i);
      break;
    }
  }
  exit(0);
}


/*
  cs-signoril-1:threads signoril$ ./smoker_cv 5
  agent placed matches and paper on table
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  smoker 1 (that is tobacco) Yippe it is for me
  smoker 3 (that is paper) darn, the goods on the table are not for me, i have to wait
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  agent placed matches and tobacco on table
  smoker 3 (that is paper) darn, the goods on the table are not for me, i have to wait
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  smoker 1 (that is tobacco) darn, the goods on the table are not for me, i have to wait
  smoker 3 (that is paper) Yippe it is for me
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  smoker 1 (that is tobacco) darn, the goods on the table are not for me, i have to wait
  agent placed tobacco and paper on table
  smoker 3 (that is paper) darn, the goods on the table are not for me, i have to wait
  smoker 2 (that is matches) Yippe it is for me
  agent placed matches and tobacco on table
  smoker 1 (that is tobacco) darn, the goods on the table are not for me, i have to wait
  smoker 3 (that is paper) Yippe it is for me
  smoker 1 (that is tobacco) darn, the goods on the table are not for me, i have to wait
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  agent placed matches and tobacco on table
  smoker 1 (that is tobacco) darn, the goods on the table are not for me, i have to wait
  smoker 3 (that is paper) Yippe it is for me
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  smoker 1 (that is tobacco) darn, the goods on the table are not for me, i have to wait
  agent done
  smoker 2 (that is matches) darn, the goods on the table are not for me, i have to wait
  Thread agent has terminated
  main is going now, time to kill off smokers
  smoker 0 (that is tobacco) terminated
  smoker 1 (that is matches) terminated
  smoker 2 (that is paper) terminated
  cs-signoril-1:threads signoril$ 

*/



