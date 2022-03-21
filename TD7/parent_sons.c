#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
    pid_t son1, son2, son3;
    son1 = fork();
    if (son1 != 0)
    {
        son2 = fork();
    }
    if (son1 != 0 && son2 != 0)
    {
        son3 = fork();
    }

    if (son1 != 0 && son2 != 0 && son3 != 0)
    {
        printf("Parent's PID : %ld\n", getpid());
        int status;
        waitpid(son2, &status, 0);
        printf("Exited with code status :  %d\n", WEXITSTATUS(status));
    }

    if (son1 == 0)
    {
        sleep(1);
        printf("1st son with PID : %ld (1) and Parent's PID : %ld ended.\n", getpid(), getppid());
        exit(1);
    }
    else if (son2 == 0)
    {
        sleep(2);
        printf("2nd son with PID : %ld (2) and Parent's PID : %ld ended.\n", getpid(), getppid());
        exit(2);
    }
    else if (son3 == 0)
    {
        sleep(3);
        printf("3rd son with PID : %ld (3) and Parent's PID : %ld ended.\n", getpid(), getppid());
        exit(3);
    }
    return 0;
}
