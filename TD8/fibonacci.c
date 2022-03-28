#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void child(int *pipeFS, int *pipeSF)
{
    close(pipeFS[1]);
    close(pipeSF[0]);
    int temp;
    int sum;
    read(pipeFS[0], &sum, sizeof(sum));
    for (int i = 0; i < 15; i++)
    {
        write(pipeSF[1], &sum, sizeof(sum));
        read(pipeFS[0], &temp, sizeof(temp));
        sum += temp;
        
    }
    close(pipeFS[0]);
    close(pipeSF[1]);
    exit(0);
}

void father(int *pipeFS, int *pipeSF)
{
    close(pipeFS[0]);
    close(pipeSF[1]);
    int fibo1 = 0;
    int fibo2 = 1;
    int current_fibo;
    write(pipeFS[1], &fibo1, sizeof(fibo1));
    write(pipeFS[1], &fibo2, sizeof(fibo2));
    for (int i = 0; i < 15; i++)
    {
        read(pipeSF[0], &current_fibo, sizeof(current_fibo));
        printf("Father read : %d\n", current_fibo);
        write(pipeFS[1], &current_fibo, sizeof(current_fibo));
    }
    close(pipeFS[1]);
    close(pipeSF[0]);
}

int main(void)
{
    int pipeFS[2];
    int pipeSF[2];
    if (pipe(pipeFS) == -1 || pipe(pipeSF) == -1)
        exit(1);
    int pid = fork();
    if (pid == 0)
    {
        child(pipeFS, pipeSF);
    }
    else
    {
        father(pipeFS, pipeSF);
    }
    return 0;
}