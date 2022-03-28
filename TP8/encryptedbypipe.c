#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <ctype.h>

//===============================================
void firstPipe(int inpipe[2], int outpipe[2])
{
    close(inpipe[1]);
    close(outpipe[0]);

    char buffer[2048];
    read(inpipe[0], buffer, sizeof(buffer));
    int s_buffer = strlen(buffer);
    char sentence[s_buffer + 1];
    strcpy(sentence, buffer);

    for (int i = 0; i < s_buffer; i++)
    {
        if (isalpha(buffer[i]))
        { // ? Check if the character is alphanumerical or a number
            sentence[i] = toupper(buffer[i]);
        }
        else
        {
            sentence[i] = buffer[i];
        }
    }
    write(outpipe[1], sentence, strlen(sentence));
    close(inpipe[0]);
    close(outpipe[1]);
}

//===============================================
void secondPipe(int inpipe[2], int outpipe[2])
{
    close(inpipe[1]);
    close(outpipe[0]);
    char buffer[2048];
    read(inpipe[0], buffer, sizeof(buffer));
    int s_buffer = strlen(buffer) - 1;
    char sentence[s_buffer + 1];
    strcpy(sentence, buffer);
    for (int i = 0; i < s_buffer; i++)
    {
        if (isdigit(buffer[i]))
        { // ? Check if the character is alphanumerical or a number
            if (buffer[i] <= '4' && buffer[i] >= '0')
            {
                sentence[i] = buffer[i] + 5;
            }
            else
            {
                sentence[i] = buffer[i] - 5;
            }
        }
        else
        {
            sentence[i] = buffer[i];
        }
    }
    write(outpipe[1], sentence, strlen(sentence));
    close(inpipe[0]);
    close(outpipe[1]);
}

//===============================================
void thirdPipe(int inpipe[2])
{
    close(inpipe[1]);
    char buffer[2048];
    read(inpipe[0], buffer, sizeof(buffer));
    int s_buffer = strlen(buffer) - 1;
    char sentence[s_buffer + 1];
    strcpy(sentence, buffer);
    for (int i = 0; i < s_buffer; i++)
    {
        if (isalpha(buffer[i]))
        { // ? Check if the character is alphanumerical or a number
            char next_char = buffer[i];
            for (int i = 0; i < 13; i++)
            {
                if (next_char == 'Z')
                {
                    next_char = 'A';
                }
                else
                {
                    next_char = (char)(((int)next_char) + 1);
                }
            }
            sentence[i] = next_char;
        }
        else
        {
            sentence[i] = buffer[i];
        }
    }
    printf(">> %s\n", sentence);
    close(inpipe[0]);
}

//===============================================
//===============================================
int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        perror("Usage : encryptedbypipe");
        exit(0);
    }

    int pipeF1[2];
    int pipe12[2];
    if (pipe(pipeF1) == -1 || pipe(pipe12) == -1)
        exit(0);

    // create child 1
    int pidc1 = fork();
    if (pidc1 == -1)
        exit(0);

    if (pidc1 == 0)
    {
        int pipe23[2];
        if (pipe(pipe23) == -1)
            exit(1);

        // create child 2
        int pidc2 = fork();
        if (pidc2 == -1)
            exit(0);

        if (pidc2 == 0)
        {
            thirdPipe(pipe23);
        }
        else
        {
            secondPipe(pipe12, pipe23);
            waitpid(pidc2, NULL, 0);
        }
    }
    else
    {
        char input[2048];
        scanf("%s", input);
        write(pipeF1[1], input, strlen(input) + 1);
        firstPipe(pipeF1, pipe12);
        waitpid(pidc1, NULL, 0);
    }
    return 0;
}
