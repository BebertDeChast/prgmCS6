#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//===============================================
int wordIndex (int argc, char *argv[], char *word)
{
  // TODO
}

//===============================================
void checkSyntax (int argc, char *argv[])
{
  // TODO
}

//===============================================
void runCommand (char *argv[], int ind1, int ind2)
{
  // TODO
}

//===============================================
int runAll(int argc, char *argv[])
{
  // TODO
}

//===============================================
//===============================================
int main (int argc, char *argv[])
{
  checkSyntax(argc, argv);
  runAll(argc, argv);
}
