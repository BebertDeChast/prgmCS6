// File : clienttable.c

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>

#include "clienttable.h"

//===============================================
void Clienttable_Init(Clienttable *self)
{
  self->capacity = 0;
  self->numberOfClients = 0;
  self->pid = NULL;
  self->frompipe = NULL;
  self->topipe = NULL;
}

//===============================================
bool Clienttable_IsFull(Clienttable *self)
{
  return self->numberOfClients == self->capacity;
}

//===============================================
void Clienttable_Realloc(Clienttable *self)
{

  if (self->capacity == 0)
    self->capacity = 1;

  int newCapacity = self->capacity * 2;
  pid_t *newpid = realloc(self->pid, newCapacity * sizeof(pid_t));
  assert(newpid != NULL);
  int *newfrompipe = realloc(self->frompipe, newCapacity * sizeof(int));
  assert(newfrompipe != NULL);
  int *newtopipe = realloc(self->topipe, newCapacity * sizeof(int));
  assert(newtopipe != NULL);

  self->capacity = newCapacity;
  self->pid = newpid;
  self->frompipe = newfrompipe;
  self->topipe = newtopipe;
}

//===============================================
void Clienttable_AddClient(Clienttable *self, pid_t clientpid)
{
  if (Clienttable_IsFull(self))
    Clienttable_Realloc(self);

  self->pid[self->numberOfClients] = clientpid;
  self->numberOfClients++;
}

//===============================================
int Clienttable_GetClientIndex(Clienttable *self, pid_t clientpid)
{
  for (int i = 0; i < self->numberOfClients; i++)
    if (self->pid[i] == clientpid)
      return i;

  return -1;
}

//===============================================
void Clienttable_OpenPipes(Clienttable *self, pid_t clientpid)
{
  char to_pipard[64];
  char from_pipard[64];
  sprintf(to_pipard, "to%d", clientpid);
  sprintf(from_pipard, "from%d", clientpid);

  mkfifo(to_pipard, 755);
  mkfifo(from_pipard, 755);

  int pipeWrite = open(to_pipard, O_WRONLY);
  int pipeRead = open(from_pipard, O_RDONLY);

  int index = Clienttable_GetClientIndex(self, clientpid);
  self->frompipe[index] = pipeRead;
  self->topipe[index] = pipeWrite;
}

//===============================================
void Clienttable_ClosePipes(Clienttable *self, pid_t clientpid)
{
  int index = Clienttable_GetClientIndex(self, clientpid);
  close(self->frompipe[index]);
  close(self->topipe[index]);
}

//===============================================
int Clienttable_GetFromPipe(Clienttable *self, pid_t clientpid)
{
  int index = Clienttable_GetClientIndex(self, clientpid);
  return self->frompipe[index];
}

//===============================================
int Clienttable_GetToPipe(Clienttable *self, pid_t clientpid)
{
  int index = Clienttable_GetClientIndex(self, clientpid);
  return self->topipe[index];
}

//===============================================
void Clienttable_Destroy(Clienttable *self)
{
  for (int i = 0; i < self->numberOfClients; i++)
  {
    close(self->frompipe[i]);
    close(self->topipe[i]);
  }

  free(self->pid);
  free(self->frompipe);
  free(self->topipe);
  Clienttable_Init(self);
}
