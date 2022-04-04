// File : Process_.h
#ifndef PROCESS_H
#define PROCESS_H

#include <unistd.h>
#include <stdbool.h>

#define MAX_COMMAND_SIZE 256

typedef char Command[MAX_COMMAND_SIZE];

typedef struct Process {
  int capacity;
  int numberOfProcess;
  int * status;
  pid_t * clientPid;
  Command * command;
} Process;

void Process_Init(Process *self);
bool Process_IsFull(Process *self);
void Process_Realloc(Process *self);
void Process_AddCommand(Process *self, Command com);
int Process_GetIndexOfUnattributedCommand(Process *self);
void Process_WriteCommandToPipe(Process *self, int index, int clientpipe);
void Process_ReadStatusFromPipe(Process *self, int clientpipe);
void Process_SetCommandToClient(Process *self, int index, pid_t clientpid);
void Process_PrintStatus(Process *self);
void Process_Destroy(Process *self);

#endif
