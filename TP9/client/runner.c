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
int main (int argc, char *argv[])
{
  if (argc != 2) {
    printf("Usage : ./runner server_pid\n");
    exit(1);
  }

  Command command;
  Command_Init(&command);
  mysignal(SIGALRM, &handlerAlarm, SA_RESTART);
  int server_pid = atoi(argv[1]);
  printf("[DEBUG] Input server's pid : %d\n", server_pid);

  char to_pipard[64];
  char from_pipard[64];
  int clientpid = getpid();
  sprintf(to_pipard, "to%d", clientpid);
  sprintf(from_pipard, "from%d", clientpid);

  mkfifo(to_pipard, 755);
  mkfifo(from_pipard, 755);

  union sigval value ;
  value.sival_int = getpid();
  printf("[DEBUG] SIGUSR1 sent to %d with payload %d\n", server_pid, getpid());
  sigqueue(server_pid, SIGUSR1, value);
  pause();

  printf("[DEBUG] Signal has been acquired with server !\n");
  int pipeRead = open(to_pipard, O_RDONLY | O_NONBLOCK);
  int pipeWrite = open(from_pipard, O_WRONLY | O_NONBLOCK);
  printf("[DEBUG] Pipes are open, starting loop.\n");
  while(1) {
    sleep(1);
    Command_AskForCommand(server_pid);
    Command_Reset(&command);
    Command_ReadCommandFromPipe(&command, pipeRead);
    if (command.commandNumber >= 0) {
      Command_Execute(&command);
      Command_WriteExitStatusOnPipe(&command, pipeWrite, server_pid);
    } else {
      sleep(10);
      printf("[DEBUG] Invalid command received.\n");
    }
    
  }
  printf("[DEBUG] Closing everything hopefully.\n");
  close(pipeWrite);
  close(pipeRead);
}
