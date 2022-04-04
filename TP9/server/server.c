// File : server.c
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <assert.h>
#include <signal.h>

#include "process.h"
#include "clienttable.h"

Clienttable clienttable;
Process process;

//===============================================
int mysignal(int sig, void (*h)(int, siginfo_t *, void *), int options)
{
  struct sigaction s;
  s.sa_sigaction = h;
  sigemptyset(&s.sa_mask);
  s.sa_flags = options;
  int r = sigaction(sig, &s, NULL);
  if (r < 0)
    perror(__func__);
  return r;
}

//===============================================
void handlerClient(int sig, siginfo_t *info, void *ctx)
{
  if (info->si_code == SI_QUEUE)
  {
    int pid = (int)info->si_pid;
    Clienttable_AddClient(&clienttable, pid);
    kill(pid, SIGALRM);
    Clienttable_OpenPipes(&clienttable, pid);
  }
}

//===============================================
void handlerCommand(int sig, siginfo_t *info, void *ctx)
{
  if (info->si_code == SI_QUEUE)
  {
    int clientIndex;
    int pipe;
    switch (info->si_value.sival_int)
    {
    case 1:
      clientIndex = Clienttable_GetClientIndex(&clienttable, (int)info->si_pid);
      pipe = Clienttable_GetToPipe(&clienttable, clientIndex);

      int cmdindex = Process_GetIndexOfUnattributedCommand(&process);
      if (cmdindex == -1)
      {
        write(pipe, &cmdindex, sizeof(cmdindex));
      }
      else
      {
        Process_SetCommandToClient(&process, cmdindex, info->si_pid);
        Process_WriteCommandToPipe(&process, cmdindex, pipe);
      }
      break;
    case 2:
      clientIndex = Clienttable_GetClientIndex(&clienttable, (int)info->si_pid);
      pipe = Clienttable_GetFromPipe(&clienttable, clientIndex);
      Process_ReadStatusFromPipe(&process, pipe);
      break;
    }
  }
}

//===============================================
int main()
{
  Clienttable_Init(&clienttable);
  Process_Init(&process);
  printf("Server's PID : %d\n", getpid());

  mysignal(SIGUSR1, &handlerClient, SA_RESTART);
  mysignal(SIGUSR2, &handlerCommand, SA_RESTART);

  char cmd[MAX_COMMAND_SIZE];
  while (1)
  {
    fgets(cmd, MAX_COMMAND_SIZE, stdin);
    if (strlen(cmd) <= 0)
    {
      Process_PrintStatus(&process);
      exit(0);
    }
    Process_AddCommand(&process, cmd);
  };
  return 0;
}
