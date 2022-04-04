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

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage : sig-send sig val pid\n");
        exit(1);
    }
    union sigval value;
    value.sival_int = atoi(argv[2]);
    sigqueue(atoi(argv[3]), atoi(argv[1]), value);
    return 0;
}