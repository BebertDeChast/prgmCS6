#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void childA(int *sender, int *receiver)
{
    close(receiver[1]);
    close(sender[0]);
    int number = 1;
    int noWritten = write(sender[1], &number, sizeof(number));
    for (int i = 0; i < 200; i++)
    {
        int noRead = read(receiver[0], &number, sizeof(number));
        printf("Child A read : %d\n", number);
        number++;
        int noWritten = write(sender[1], &number, sizeof(number));
    }
    close(receiver[0]);
    close(sender[1]);
}

void childB(int *sender, int *receiver)
{
    close(receiver[1]);
    close(sender[0]);
    for (int i = 0; i < 200; i++)
    {
        int number;
        int noRead = read(receiver[0], &number, sizeof(number));
        printf("Child B read : %d\n", number);
        number--;
        int noWritten = write(sender[1], &number, sizeof(number));
    }
    close(receiver[0]);
    close(sender[1]);
}

int main(void)
{
    int pipefdAB[2];
    int pipefdBA[2];
    if (pipe(pipefdAB) == -1 || pipe(pipefdBA) == -1)
    {
        perror("Error creating pipe\n");
        exit(1);
    }
    int pidA = fork();
    if (pidA == -1)
    {
        exit(1);
    }
    if (pidA == 0)
    {
        childA(pipefdAB, pipefdBA);
    }

    int pidB = fork();
    if (pidB == -1)
    {
        exit(1);
    }
    if (pidB == 0)
    {
        childB(pipefdBA, pipefdAB);
    }
    else
    {
        close(pipefdAB[0]);
        close(pipefdAB[1]);
        close(pipefdBA[0]);
        close(pipefdBA[1]);
        wait(NULL);
        wait(NULL);
        printf("Father is finished, all sons are dead\n");
    }
    return 0;
}
