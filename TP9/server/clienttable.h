// File : Clienttable_.h
#ifndef CLIENTTABLE_H
#define CLIENTTABLE_H

#include <unistd.h>
#include <stdbool.h>

typedef struct Clienttable
{
  int capacity;
  int numberOfClients;
  pid_t *pid;
  int *frompipe;
  int *topipe;
} Clienttable;

void Clienttable_Init(Clienttable *self);
bool Clienttable_IsFull(Clienttable *self);
void Clienttable_Realloc(Clienttable *self);
void Clienttable_AddClient(Clienttable *self, pid_t clientpid);
int Clienttable_GetClientIndex(Clienttable *self, pid_t clientpid);
void Clienttable_OpenPipes(Clienttable *self, pid_t clientpid);
void Clienttable_ClosePipes(Clienttable *self, pid_t clientpid);
int Clienttable_GetFromPipe(Clienttable *self, pid_t clientpid);
int Clienttable_GetToPipe(Clienttable *self, pid_t clientpid);
void Clienttable_Destroy(Clienttable *self);

#endif
