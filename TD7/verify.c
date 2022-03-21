#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int status;
    if (argc == 1)
    {
        printf("Usage : verify com arg1 ... argn\n");
        exit(1);
    }
    pid_t son = fork();
    if (son == -1)
        exit(1);
    if (son == 0)
    {
        execvp(argv[1], argv + 1); // ! ça va recouvrir le processus fils. Autrement dit, si ça marche, tout ce code va être effacé côté fils.
        printf("Error running %s\n", argv[1]);
        exit(1);
    }

    wait(&status);
    printf("Child %ld ended with code : %d\n", son, WEXITSTATUS(status));
    return 0;
}