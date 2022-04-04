// File : Process_.c
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include "process.h"


//===============================================
void Process_Init(Process *self)
{
  self->capacity = 0;
  self->numberOfProcess = 0;
  self->clientPid = NULL;
  self->status = NULL;
  self->command = NULL;
}

//===============================================
bool Process_IsFull(Process *self)
{
  return self->numberOfProcess == self->capacity;
}

//===============================================
void Process_Realloc(Process *self)
{
  if (self->capacity == 0)
    self->capacity = 1;

  int newCapacity = self->capacity * 2;
  pid_t * newPid = realloc(self->clientPid, newCapacity * sizeof (pid_t));
  assert (newPid != NULL );
  int * newStatus = realloc(self->status, newCapacity * sizeof (int));
  assert (newStatus != NULL );
  Command * newCommand = realloc(self->command, newCapacity * sizeof (Command));
  assert (newCommand != NULL );

  self->capacity = newCapacity;
  self->clientPid = newPid;
  self->status = newStatus;
  self->command = newCommand;
}

//===============================================
void Process_AddCommand(Process *self, Command com)
{
// TODO
}

//===============================================
int Process_GetIndexOfUnattributedCommand(Process *self)
{
// TODO
}

//===============================================
int Process_GetIndexOfClientPid(Process *self, pid_t clientpid)
{
  for (int i=0; i<self->numberOfProcess; i++)
    if (self->clientPid[i]==clientpid)
      return i;

  return -1;
}

//===============================================
void Process_WriteCommandToPipe(Process *self, int index, int clientpipe)
{
// TODO
}

//===============================================
void Process_ReadStatusFromPipe(Process *self, int clientpipe)
{
// TODO
}

//===============================================
void Process_SetCommandToClient(Process *self, int index, pid_t clientpid)
{
// TODO
}

//===============================================
void Process_PrintStatus(Process *self)
{
  for (int i=0; i<self->numberOfProcess; i++){
    printf("%s - %d\n", self->command[i], self->status[i]);
  }
}

//===============================================
void Process_Destroy(Process *self)
{
  free(self->clientPid);
  free(self->status);
  free(self->command);
  Process_Init(self);
}
