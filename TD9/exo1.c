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

int count;
void handler(int sig)
{
    printf("Received signal : %d\n", sig);
    count++;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : ./exo1 n\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    pid_t son;
    son = fork();
    switch (son)
    {
    case 0:
        for (int i = 0; i < n; i++)
        {
            kill(getppid(), SIGUSR1);
        }
        exit(0);
        break;
    default:
        mysignal(SIGUSR1, &handler, SA_RESTART);
        waitpid(son, NULL, 0);
        printf("Number of signals received : %d\n", count); // ! This is normal behavior that not all signals are received
        break;
    }
    return 0;
}