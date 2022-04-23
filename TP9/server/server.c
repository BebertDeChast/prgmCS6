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
  s.sa_flags = SA_SIGINFO | options;
  int r = sigaction(sig, &s, NULL);
  if (r < 0)
    perror(__func__);
  return r;
}

//===============================================
void handlerClient(int sig, siginfo_t *info, void *ctx)
{
  // printf("[DEBUG] SIGUSR1 received\n");
  if (info->si_code == SI_QUEUE)
  {
    int pid = (int)info->si_pid;
    // printf("[DEBUG] Payload received: %d\n", pid);
    Clienttable_AddClient(&clienttable, pid);
    kill(pid, SIGALRM);
    // printf("[DEBUG] SIGALRM sent to %d\n", pid);
    Clienttable_OpenPipes(&clienttable, pid);
    printf("[INFO] Client %d connected\n",pid);
  }
}

//===============================================
void handlerCommand(int sig, siginfo_t *info, void *ctx)
{
  // printf("[DEBUG] SIGUSR2 received.\n");
  if (info->si_code == SI_QUEUE)
  {
    int pipe;
    // printf("[DEBUG] Payload received : %d\n", info->si_value.sival_int);
    switch (info->si_value.sival_int)
    {
    case 1: // demande de commande
      // printf("[DEBUG] Asked for command by runner %d\n",(int)info->si_pid);
      pipe = Clienttable_GetToPipe(&clienttable, (int)info->si_pid);

      int cmdindex = Process_GetIndexOfUnattributedCommand(&process);
      if (cmdindex == -1)
      {
        // printf("[DEBUG] No command to send\n");
        char dummy[3];
        sprintf(dummy, "-1");
        // printf("[DEBUG] Sending : %s to pipe %d \n", dummy, pipe);
        write(pipe, dummy, sizeof(dummy));
      }
      else
      {
        printf("[INFO] Sending command %d to client %d\n",cmdindex,info->si_pid);
        Process_SetCommandToClient(&process, cmdindex, info->si_pid);
        Process_WriteCommandToPipe(&process, cmdindex, pipe);
      }
      break;
    case 2: // recoit valeur de retour 
      // printf("[DEBUG] Result by runner %d\n",(int)info->si_pid);
      pipe = Clienttable_GetFromPipe(&clienttable, (int)info->si_pid);
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
  printf("[INFO] Server's PID : %d\n", getpid());

  mysignal(SIGUSR1, &handlerClient, SA_RESTART);
  mysignal(SIGUSR2, &handlerCommand, SA_RESTART);

  char cmd[MAX_COMMAND_SIZE];
  printf("[INFO] Awaiting for a command...\n");
  while (fgets(cmd, MAX_COMMAND_SIZE, stdin) != NULL)
  {
    cmd[strlen(cmd) - 1] = '\0'; // * Removed the 'ENTER' character registered upon validation of the command
    sleep(1);
    // printf("[DEBUG] Command added : \n[DEBUG] %s\n[DEBUG]---\n", cmd);
    Process_AddCommand(&process, cmd);
  };
  Process_PrintStatus(&process);
  printf("[INFO] End of process.\nThank you for choosing MPCI\u00A9\n");
  return 0;
}
