#include "process.h"

int send_p1[2];
int reply_p1[2];
int send_p2[2];
int reply_p2[2];

int main(int argc, char *argv[])
{	
	int curr_stat;
	int i;
	pid_t myPid[3];

	if (   pipe(send_p1)  < 0 || pipe(reply_p1) < 0
		|| pipe(send_p2)  < 0 || pipe(reply_p2) < 0){
		puts("Unable to pipe");
		exit(1);
	};


	// If all good, fork() to create the processes and run them

	myPid[0] = fork();

	if (myPid[0] == 0){
		fprintf(stdout, "P1 created.\n");
		p1();
		exit(0);
	}

	myPid[1] = fork();

	if (myPid[1] == 0){
		fprintf(stdout, "P2 created.\n");
		p2();
		exit(0);
	}

	myPid[2] = fork();

	if (myPid[2] == 0){
		fprintf(stdout, "P3 created.\n");
		p3();
		exit(0);
	}

	closeAllPipes();

	// Wait until processes are done
	waitpid(myPid[0], &curr_stat, 0);
	waitpid(myPid[1], &curr_stat, 0);
	waitpid(myPid[2], &curr_stat, 0);
	
	puts("Done");

	exit(0);
}

void caseSwitch(char *line){
	int i;
	char c;
	for (i=0; i<MAX_LINE; i++){
		if (isChar(*(line+i))){
			if (*(line+i) >= 'a')
				*(line+i) -= 32;
			else 
				*(line+i) += 32;
		}
	}
}

// Make sure a given char is an applicable Char (letter here)

int isChar(char c){
  	return (c <= 'z') && (c >= 'a') || (c >= 'A') && (c <='Z');
}

// This process gets the line and sends it to P2

void p1(){
	FILE *fp;
	int x;
	char reply[11];
	close(send_p1[0]);
	close(reply_p1[1]);
	char *line;
	
    fp = fopen("MobyDick.txt" , "r");
    if(fp == NULL) { // make sure the file opens
      perror("f-open error");
      return;
    }
    
	line = returnLine(fp);
	if (line==NULL){ 
		puts("Empty file"); 
	}

    while(line != NULL){
    	write(send_p1[1], line, MAX_LINE);
    	x = read(reply_p1[0], reply, 10); // waits until P2 sends bytes back to read
    	free(line);
    	line = returnLine(fp);
    }
    write(send_p1[1], SEQEND, SEQENDLENGTH+1);
    fclose(fp);

    close(send_p1[1]);
}

void p2(){	
	int a;
	int i;

	char *buff, reply[11];
	buff = (char *)malloc(sizeof(char)*MAX_LINE+1);
	close(send_p1[1]);
	close(reply_p1[0]);
	close(send_p2[0]);
	close(reply_p2[1]);
	while ((i = read(send_p1[0], buff, MAX_LINE)) != 0){
		buff[i] = '\0';
		if (strcmp(SEQEND, buff) == 0){
			a = read(reply_p2[0], reply, 10);
			write(send_p2[1], SEQEND, SEQENDLENGTH+1);
			close(send_p1[0]);
			close(reply_p1[1]);
			close(send_p2[1]);
			close(reply_p2[0]);
			exit(0);
		}
		caseSwitch(buff);
		a = read(reply_p2[0], reply, 10);
		write(send_p2[1], buff, MAX_LINE);
		write(reply_p1[1], "OK", 3);
	}
	puts("P2 Done");
}

// writes to the output file

void p3(){
	char *buff;
	int i;

	buff = (char *)malloc(sizeof(char)*MAX_LINE+1);

	FILE *fout = fopen("output.txt", "w");
	if (fout==NULL)
	{
		printf("F-open error.\n");
		exit(1);
	}

	close(send_p2[1]);
	close(reply_p2[0]);

	write(reply_p2[1], "OK", 3);

	while ((i = read(send_p2[0], buff, MAX_LINE)) != 0){
		buff[i] = '\0';
		if (strcmp(SEQEND, buff)==0){
			fclose(fout);
			close(send_p2[0]);
			close(reply_p2[1]);
			exit(0);
		}
		fprintf(fout, "%s\n", buff); // writing to the file
		write(reply_p2[1], "OK", 3);
	}
	puts("P3 Done");
}

// File tests from Signorile code
int test_eol(char a){
  if (a == '\n')
    return 1;
  else
    return 0;
}
int test_eof(char a){
  if (a == EOF)
    return 1;
  else
    return 0;
}

char * returnLine(FILE *fp){ 
  char c;
  char *line;
  int size=0;
  line = NULL;
  line = realloc(line,sizeof(char));
  c = fgetc(fp); 
  if (test_eof(c)){
    return NULL;
	}
  while (!test_eol(c) && !test_eof(c)){
    *(line+size) = c;
    size++;
    line = realloc(line,sizeof(char)* (size+1));
    c = fgetc(fp);
  }
  *(line+size) = '\0';
  return line;
}

void closeAllPipes(){
	close(send_p1[0]);
	close(send_p1[1]);
	close(reply_p1[0]);
	close(reply_p1[1]);
	close(send_p2[0]);
	close(send_p2[1]);
	close(reply_p2[0]);
	close(reply_p2[1]);
}