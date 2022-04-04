#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

//===============================================
void firstPipe (int inpipe[2], int outpipe[2])
{
  char message[4096];

  close(inpipe[1]); // close inpipe write
  close(outpipe[0]); // close outpipe read

  while(read(inpipe[0], message, 4096)){
    for (int i=0; i<strlen(message); i++)
      message[i] = toupper(message[i]);
    write(outpipe[1], message, 4096);
  }

  close(inpipe[0]);
  close(outpipe[1]);
}

//===============================================
void secondPipe (int inpipe[2], int outpipe[2])
{
  char message[4096];

  close(inpipe[1]); // close inpipe write
  close(outpipe[0]); // close outpipe read

  while(read(inpipe[0], message, 4096)){
    for (int i=0; i<strlen(message); i++){
      if (message[i] >= '0' && message[i] < '5')
        message[i]+=5;
      else{
        if (message[i] >= '5' && message[i] <= '9')
          message[i]-=5;
      }
    }
    write(outpipe[1], message, 4096);
  }
  close(inpipe[0]);
  close(outpipe[1]);
}

//===============================================
void thirdPipe (int inpipe[2])
{
  char message[4096];

  close(inpipe[1]); // close inpipe write

  while(read(inpipe[0], message, 4096)){
    for (int i=0; i<strlen(message); i++){
      if (message[i] >= 'A' && message[i] < 'N')
        message[i]+=13;
      else{
        if (message[i] >= 'N' && message[i] <= 'Z')
          message[i]-=13;
      }
    }
    write(STDOUT_FILENO, message, strlen(message));
  }
  close(inpipe[0]);
}

//===============================================
//===============================================
int main (int argc, char *argv[])
{
  pid_t pid;
  char message[4096];
  int pipefd[3][2];

  if (pipe(pipefd[0]) < 0){perror("pipe"); exit(EXIT_FAILURE);}

  pid=fork();
  if (pid < 0){ perror("fork"); exit(EXIT_FAILURE);}


  if (pid > 0){ // father
    close(pipefd[0][0]);
    while (fgets(message, 4095, stdin)!=NULL){
      write(pipefd[0][1], message, strlen(message));
    }
    close(pipefd[0][1]);
    exit(EXIT_SUCCESS);
  }

  // first child
  if (pipe(pipefd[1]) < 0){ perror("pipe"); exit(EXIT_FAILURE);}

  pid=fork();
  if (pid < 0){ perror("fork"); exit(EXIT_FAILURE);}
  if (pid > 0){ // child 1
    firstPipe(pipefd[0], pipefd[1]);
    exit(EXIT_SUCCESS);
  }

  // second child
  if (pipe(pipefd[2]) < 0){perror("pipe"); exit(EXIT_FAILURE);}

  pid=fork();
  if (pid < 0){ perror("fork"); exit(EXIT_FAILURE);}
  if (pid > 0){ // child 2
    secondPipe(pipefd[1], pipefd[2]);
    exit(EXIT_SUCCESS);
  }

  // third child
  thirdPipe(pipefd[2]);
  exit(EXIT_SUCCESS);
}
