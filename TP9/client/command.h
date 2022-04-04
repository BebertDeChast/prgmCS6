// File : Command_.h
#ifndef COMMAND_H
#define COMMAND_H

#define MAX_COMMAND_SIZE 256

typedef struct Command {
  char commandline[MAX_COMMAND_SIZE];
  int argc;
  char ** argv;
  int exitStatus;
  int commandNumber;
} Command;

void Command_Init(Command *self);
void Command_Reset(Command *self);
int Command_ReadCommandFromPipe(Command *self, int pipe);
void Command_WriteExitStatusOnPipe(Command *self, int pipe, pid_t serverpid);
void Command_AskForCommand(pid_t serverpid);
void Command_CountCommandArg(Command *self);
void Command_CreateArgv(Command *self);
void Command_Execute(Command *self);
#endif
