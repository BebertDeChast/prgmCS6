#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
    int status;
    pid_t pid;
    pid_t second_son;
    for (int rank = 1; rank <= 3; rank++)
    {
        pid = fork();
        if (rank == 2)
        {
            second_son = pid;
        }
        if (pid == 0)
        {
            sleep(rank);
            printf("Child %ld (%d) with parent's process %ld\n", getpid(), rank, getppid());
            exit(rank);
        }
    }

    if (pid != 0)
    {
        printf("Parent's PID : %ld\n", getpid());
        waitpid(second_son, &status, 0);
        printf("Second son exit with code : %d\n", WEXITSTATUS(status));
    }
    return 0;
}