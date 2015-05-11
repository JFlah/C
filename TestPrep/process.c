#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	int i, j;
	pid_t pid; // for any process
	int status;

	int p1[2], p2[2]; // my PIPES

	char buff[80];

	// pipe() creates the pipe/opens it
	if (pipe(p1) == -1 || pipe(p2) == -1) {
		perror("Pipe error");
		exit(1);
	}

	pid = fork();

	// child
	if (pid == 0){ 
		close(p1[1]); // close writing ability of p1 (the parent) because its only reading
		close(p2[0]); // close reading ability of p2 (child) cuz its writing to p1

		int j = 0;
		while (j++ < 4){
			i = read(p1[0], buff, 80); //source of read, where reading to, how many bytes
			printf("Child received: %s\n", buff);
			sleep(1);
			write(p2[1], "OK", 3); // where writing to (pipe 2), the message, how many bytes ("OK" + sentienl)
		}
		write(p2[1], "DONE", 5);
		close(p2[1]); // read only returns 0 if this writing pipe is closed, which terminates it
		close(p1[0]);

		sleep(5);
		exit(1); // kills the pid (process)
	}

	// parent

	close(p1[0]); // close own read
	close(p2[1]); // close p2 write


	// writes first, then waits for read
	do {
		write(p1[1], "MESSAGE", 8);
	} while ((i=read(p2[0], buff, 80)) != 0);

	puts("DONE"); // write p2 pipe is closed, so it == 0, so now its closed and done
	waitpid(pid, &status, 0); // waits until pid is killed similar to join()

	close(p1[1]);
	close(p2[0]);

}