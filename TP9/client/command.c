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
int Command_ReadCommandFromPipe(Command *self, int pipe)
{
// TODO
}

//===============================================
void Command_WriteExitStatusOnPipe(Command *self, int pipe, pid_t serverpid)
{
// TODO
}

//===============================================
void Command_AskForCommand(pid_t serverpid)
{
// TODO
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
