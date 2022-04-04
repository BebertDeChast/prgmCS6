#define _GNU_SOURCE
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

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