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
int mysignal (int sig, void (*h)(int, siginfo_t *, void *), int options)
{
  struct sigaction s;
  s.sa_sigaction = h;
  sigemptyset (& s.sa_mask);
  s.sa_flags = options;
  int r=sigaction(sig, &s, NULL);
  if (r < 0) perror (__func__);
  return r ;
}

//===============================================
void handlerClient(int sig, siginfo_t *info, void *ctx)
{
// TODO
}

//===============================================
void handlerCommand(int sig, siginfo_t *info, void *ctx)
{
// TODO
}

//===============================================
int main()
{
// TODO
}
