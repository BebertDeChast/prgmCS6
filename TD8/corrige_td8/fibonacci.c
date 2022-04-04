#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

void father(int input, int output)
{
  int n = 0;

  write(output, &n, sizeof(n));
  n++;
  write(output, &n, sizeof(n));

  do {
    read(input, &n, sizeof(n));
    printf("%d ", n);
    fflush(stdout);
    write(output, &n, sizeof(n));
  } while (n <= 100);

  printf("\n");
  close(output);
  wait(NULL);
}

void child(int input, int output)
{
  int p, q;

  read(input, &p, sizeof(p));

  while(1){
    write(output, &p, sizeof(p));
    if (!read(input, &q, sizeof(q))) return;
    p += q;
  }
}

int main(void)
{
  int pipefc[2], pipecf[2],pid;

  pipe(pipefc); /* pipe father -> child */
  pipe(pipecf); /* pipe child -> father */

  if ( (pid = fork()) == -1) { perror("fork"); exit(EXIT_FAILURE);}

  if (pid > 0){ /* father */
    close(pipefc[0]); close(pipecf[1]);
    father(pipecf[0], pipefc[1]);
  }
  else{ /* child */
    close(pipefc[1]); close(pipecf[0]);
    child(pipefc[0], pipecf[1]);
  }

//  printf("[%d] : terminaison\n", getpid());
  exit(EXIT_SUCCESS);
}
