#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main () {
	pid_t pid, pidSecondSon;
	int status;
	int rank;
	
	printf ("I am the father %d\n", getpid());

	for (int i=1; i<=3; i++){
		rank = i;
	  pid = fork ();
		if (pid<0) { perror("fork"); exit(1); }
		if (rank==2) 
			pidSecondSon = pid;
		if (pid==0) {  /* child */
			printf ("I am the son %d of %d\n", getpid(), getppid());
			sleep(rank);
			exit(rank);
		}
	}

	/* father */
	printf ("Wait second son : %d\n", pidSecondSon);
	waitpid(pidSecondSon, &status, 0);
	printf ("Exit code of second son : %d\n", WEXITSTATUS(status));
	exit (0);
}
