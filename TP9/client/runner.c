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
    s.sa_flags = options;
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

  char to_pipard[64];
  char from_pipard[64];
  int clientpid = getpid();
  sprintf(to_pipard, "to%d", clientpid);
  sprintf(from_pipard, "from%d", clientpid);

  mkfifo(to_pipard, 755);
  mkfifo(from_pipard, 755);

  union sigval value ;
  value.sival_int = 0;
  sigqueue(server_pid, SIGUSR1, value);
  pause();

  int pipeWrite = open(to_pipard, O_WRONLY);
  int pipeRead = open(from_pipard, O_RDONLY);
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
  close(pipeWrite);
  close(pipeRead);
}
