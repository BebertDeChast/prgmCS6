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
    s.sa_sigaction = h; // * Changed sa_handler to sa_sigaction
    sigemptyset(&s.sa_mask);
    s.sa_flags = options | SA_SIGINFO; // * Added flag to received infos
    int r = sigaction(sig, &s, NULL);
    if (r < 0)
        perror(__func__);
    return r;
}

void handler ( int sig , siginfo_t * info , void * ctx )
{
    printf ("Signal received %d\n", sig);
    if (info->si_code == SI_QUEUE)
        printf ("PID sender %d, data %d\n", (int)info -> si_pid, info -> si_value.sival_int);
}

int main(int argc, char argv[])
{
    for (int i = 0; i < NSIG; i++) { // ! NSIG est le signal avec la valeur la + élevé.
        mysignal(i, &handler, SA_RESTART);
    }
    printf("Attente signaux...\n");
    while(1) pause();
}