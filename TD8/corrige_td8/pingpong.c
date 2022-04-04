#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>


//===============================================
void processA (int pipeAB[2], int pipeBA[2])
{
  int i=1;
  int count=0;

  close(pipeBA[1]);
  close(pipeAB[0]);

  write(pipeAB[1], &i, sizeof(i));

  while(read(pipeBA[0], &i, sizeof(i)) && (count < 10)){
    printf ("%d - process A read %d\n", count,  i);
    i++;
    count++;
    write(pipeAB[1], &i, sizeof(i));
    sleep(1);
  }
  close(pipeBA[0]);
  close(pipeAB[1]);
  exit(EXIT_SUCCESS);
}

//===============================================
void processB (int pipeAB[2], int pipeBA[2])
{
  int i;

  close(pipeBA[0]);
  close(pipeAB[1]);

  while(read(pipeAB[0], &i, sizeof(i))){
    printf ("process B read %d\n", i);
    i--;
    write(pipeBA[1], &i, sizeof(i));
        sleep(1);
  }
  close(pipeBA[1]);
  close(pipeAB[0]);
  exit(EXIT_SUCCESS);
}

//===============================================
//===============================================
int main (int argc, char *argv[])
{
  pid_t pid;
  int pipeAB[2];
  int pipeBA[2];

  if (pipe(pipeAB) < 0){perror("pipe"); exit(EXIT_FAILURE);}
  if (pipe(pipeBA) < 0){perror("pipe"); exit(EXIT_FAILURE);}

  pid=fork();
  if (pid < 0){ perror("fork"); exit(EXIT_FAILURE);}
  if (pid == 0){
    processA(pipeAB, pipeBA);
  }

  pid=fork();
  if (pid < 0){ perror("fork"); exit(EXIT_FAILURE);}
  if (pid == 0){
    processB(pipeAB, pipeBA);
  }

  close(pipeAB[0]);
  close(pipeAB[1]);
  close(pipeBA[0]);
  close(pipeBA[1]);

  wait(NULL);
  wait(NULL);
}
