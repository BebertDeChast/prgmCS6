// File : command.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#include "command.h"

//===============================================
void Command_Init(Command *self)
{
  self->commandline[0] = '\0';
  self->argc = 0;
  self->argv = NULL;
  self->exitStatus = 0;
  self->commandNumber = -1;
}


//===============================================
void Command_Reset(Command *self)
{
  if(self->argc){
    for (int i=0; i<self->argc; i++)
      free(self->argv[i]);
    free(self->argv);
  }
  Command_Init(self);
}

//===============================================
void Command_ReadCommandFromPipe(Command *self, int pipe)
{
  char sentence[MAX_COMMAND_SIZE];
  int index;
  read(pipe, sentence, sizeof(sentence));
  // printf("[DEBUG] Index received : %s\n", sentence);
  index = atoi(sentence);
  self->commandNumber = index;
  if (index != -1)
  {
    char sentence2[MAX_COMMAND_SIZE];
    read(pipe, sentence2, sizeof(sentence2));
    strcpy(self->commandline, sentence2);
  }
}


//===============================================
void Command_WriteExitStatusOnPipe(Command *self, int pipe, pid_t serverpid)
{
  char sentence[sizeof(int)];
  sprintf(sentence, "%d", self->commandNumber);
  write(pipe, sentence, sizeof(sentence));
  sprintf(sentence, "%d", self->exitStatus);
  write(pipe, sentence, sizeof(sentence));

  union sigval value ;
  value.sival_int = 2;
  sigqueue(serverpid, SIGUSR2, value);
  // printf("[DEBUG] Sent SIGUSR2 signal with payload 2 to %d\n", serverpid);
}

//===============================================
void Command_AskForCommand(pid_t serverpid)
{
  union sigval value ;
  value.sival_int = 1;
  sigqueue(serverpid, SIGUSR2, value);
}

//===============================================
void Command_CountCommandArg(Command *self)
{
  int narg = 0;
  char *commandlineCopy = strdup(self->commandline);
  char *ptr = strtok(commandlineCopy, " ");

  while (ptr != NULL){
    narg++;
    ptr = strtok(NULL, " ");
  }
  self->argc = narg;
  free(commandlineCopy);
}

//===============================================
void Command_CreateArgv(Command *self)
{
  Command_CountCommandArg(self);

  char *commandlineCopy = strdup(self->commandline);
  char *newline = strchr(commandlineCopy, '\n');
  *newline = '\0'; // to eliminate the newline at the end
  char *ptr = strtok(commandlineCopy, " ");

  self->argv = malloc(self->argc+1 * sizeof(char *));

  for (int i=0; i<self->argc; i++){
    self->argv[i] = strdup(ptr);
    ptr = strtok(NULL, " ");
  }
  self->argv[self->argc] = NULL;
}

//===============================================
void Command_Execute(Command *self)
{
  pid_t p;
  int exitStatus;


  p = fork ();
  if (p < 0) { perror ("fork"); exit (EXIT_FAILURE); }

  if (p == 0){
    Command_CreateArgv(self);
    printf("Executing %s", self->commandline);
    execvp (self->argv[0], self->argv);
    perror ("execvp");
    exit (EXIT_FAILURE);
  }

  wait(&exitStatus);
  printf("Finish %s", self->commandline);

  self->exitStatus = WEXITSTATUS (exitStatus);
}
