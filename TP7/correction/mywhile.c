#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

//===============================================
int wordIndex (int argc, char *argv[], char *word)
{
  int i;
  for (i = 0; i < argc; i++)
    if (strcmp (argv[i], word) == 0)
      return i;
  return -1;
}

//===============================================
void checkSyntax (int argc, char *argv[])
{
  int indexDo   = wordIndex (argc, argv, "--do");
  int indexDone = wordIndex (argc, argv, "--done");

  if (indexDo < 2 || indexDone - indexDo < 2 || indexDone != argc-1) {
    fprintf (stderr, "usage: mywhyle com1 ... --do com2 .. --done\n");
    exit (1);
  }
}

//===============================================
void runCommand (char *argv[], int ind1, int ind2)
{
  argv[ind2] = NULL;    /* does need copy */
  execvp (argv[ind1], argv+ind1);
  perror ("execvp");
  exit (1);
}

//===============================================
int runAll(int argc, char *argv[])
{
  pid_t p;
  int s1, s2, e1, e2=1;

  int indexDo   = wordIndex (argc, argv, "--do");
  int indexDone = wordIndex (argc, argv, "--done");

  while (1) {
    /* we run com1 */
    p = fork ();
    if (p < 0) { perror ("fork"); exit (1); }
    if (p == 0)  /* child 1 */
      runCommand(argv, 1, indexDo);

    /* father */
    wait (&s1);
    e1 = WEXITSTATUS (s1);

    if (e1 != 0)
      exit (e2);

    /* we run com2 */
    p = fork ();
    if (p < 0) { perror ("fork"); exit (1); }

    if (p == 0)  /* child 2 */
      runCommand (argv, indexDo+1, indexDone);

     /* father again */
    wait (&s2);
		e2 = WEXITSTATUS (s2);
  }
}

//===============================================
//===============================================
int main (int argc, char *argv[])
{
  checkSyntax(argc, argv);
  runAll(argc, argv);
}
