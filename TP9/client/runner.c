// File : runner.c
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>

#include "command.h"

//===============================================
int mysignal(int sig, void (*h)(int), int options)
{
  struct sigaction s;
  s.sa_handler = h;
  sigemptyset(&s.sa_mask);
  s.sa_flags = SA_SIGINFO | options;
  int r = sigaction(sig, &s, NULL);
  if (r < 0)
    perror(__func__);
  return r;
}

//===============================================
void handlerAlarm(int sig)
{
  return;
}

//===============================================
int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage : ./runner server_pid\n");
    exit(1);
  }

  Command command;
  Command_Init(&command);
  mysignal(SIGALRM, &handlerAlarm, SA_RESTART);
  int server_pid = atoi(argv[1]);
  // printf("[DEBUG] Input server's pid : %d\n", server_pid);

  char to_pipard[64];
  char from_pipard[64];
  int clientpid = getpid();
  sprintf(to_pipard, "../pipes/to%d", clientpid);
  sprintf(from_pipard, "../pipes/from%d", clientpid);

  if (mkfifo(to_pipard, 0777) == -1)
  {
    perror("pipe creation");
  }
  if (mkfifo(from_pipard, 0777) == -1)
  {
    perror("pipe creation");
  }

  union sigval value;
  value.sival_int = getpid();
  // printf("[DEBUG] SIGUSR1 sent to %d with payload %d\n", server_pid, getpid());
  sigqueue(server_pid, SIGUSR1, value);
  pause();

  // printf("[DEBUG] Signal has been acquired with server !\n");
  int pipeRead = open(to_pipard, O_RDONLY | O_NONBLOCK);
  int pipeWrite = open(from_pipard, O_WRONLY);
  if (pipeRead == -1 | pipeWrite == -1)
  {
    perror("Pipe unreachable");
  }
  // printf("[DEBUG] Pipes are open, starting loop.\n");
  printf("[INFO] Connected to server %d\nReady to proceed\n", server_pid);
  sleep(1);
  while (kill(server_pid, 0) >= 0)
  {
    Command_AskForCommand(server_pid);
    Command_Reset(&command);
    sleep(1);
    Command_ReadCommandFromPipe(&command, pipeRead);
    if (command.commandNumber >= 0)
    {
      // printf("[DEBUG] Executing a command :\n");
      printf("\n[INFO] Executing command %d\n", command.commandNumber);
      Command_Execute(&command);
      // printf("\n[DEBUG] Finished executing command, send exit status.\n");
      Command_WriteExitStatusOnPipe(&command, pipeWrite, server_pid);
      sleep(4);
    }
    else
    {
      // printf("[DEBUG] No command received.\n");
      sleep(10);
    }
  }
  printf("\n[INFO] Shutting down. Deleting pipes.\n");
  unlink(to_pipard);
  unlink(from_pipard);
  return 0;
}
