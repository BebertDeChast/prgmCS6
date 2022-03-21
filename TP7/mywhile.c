#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//===============================================
int wordIndex(int argc, char *argv[], char *word)
{
  for (int i = 0; i < argc; i++)
  {
    if (!strcmp(word, argv[i]))
    {
      return i;
    }
  }
  return -1;
}

//===============================================
void checkSyntax(int argc, char *argv[])
{
  int do_index = wordIndex(argc, argv, "--do");
  int done_index = wordIndex(argc, argv, "--done");
  if ((do_index > 1 && done_index > do_index + 1 && done_index == argc - 1))
  {
    return;
  }
  else
  {
    perror("Usage : mywhile command1 [arg ...] --do command2 [arg ...] --done\n");
    exit(1);
  }
}

//===============================================
void runCommand(char *argv[], int ind1, int ind2)
{
  argv[ind2] = NULL;
  execvp(argv[ind1], argv + ind1);
  perror("Yeet the command !\n");
  exit(1);
}

//===============================================
int runAll(int argc, char *argv[])
{
  int do_index = wordIndex(argc, argv, "--do");
  int done_index = wordIndex(argc, argv, "--done");
  int status;

  while (true)
  {

    pid_t leg1 = fork();
    if (leg1 < 0) // child not created
    {
      perror("Yeet the child (command 1)!\n");
      exit(1);
    }
    if (leg1 == 0)
    {
      runCommand(argv, 1, do_index);
    }

    waitpid(leg1, &status, 0); // Waiting for command 1 to finish
    int stat = WEXITSTATUS(status);
    if (stat != 0) // if the command 1 fail, we stop the loop and exit the process
    {
      printf("Command 1 failed with status : %d\n", stat);
      exit(1);
    }
    else // The command 1 succeeded, continuing with command 2
    {
      pid_t leg2 = fork();
      if (leg2 < 0) // child not created
      {
        perror("Yeet the child (command 2)!\n");
        exit(1);
      }
      if (leg2 == 0)
      {
        runCommand(argv, do_index + 1, done_index);
      }
    }
  }
}

//===============================================
//===============================================
int main(int argc, char *argv[])
{
  checkSyntax(argc, argv);
  runAll(argc, argv);
}
