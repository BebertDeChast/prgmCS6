#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
	pid_t pid;
	int  status;

	if (argc == 1) {
		printf ("Usage : verify com arg1 .. argn\n");
		exit(1);
	}

	pid = fork ();
	if (pid<0) { perror("fork"); exit(1); }

	if (pid==0) {  /* child */
		execvp (argv[1], argv+1);
		printf ("Error running %s\n", argv[1]);
		exit(1);
	} 

	/* father */
	wait(&status);
	printf ("Process %d ended : %s\n", pid, WEXITSTATUS(status) == 0 ? "SUCCESS" : "FAILURE");
	exit (0);
}
