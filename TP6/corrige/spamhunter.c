// File : spamhunter.c
#include <stdio.h>
#include <stdlib.h>
#include "blocked.h"
#include "suspected.h"
#include "mail.h"

//===============================================
int main(int argc, char *argv[])
{
  Blocked blocked;
  Suspected suspected;
  Mail mail;

	if (argc < 4){
    fprintf (stderr, "Usage :  spamhunter blockedaddresses suspectedwords directory\n");
    exit(EXIT_FAILURE);
	}

  Blocked_InitEmpty(&blocked);
  Suspected_InitEmpty(&suspected);
  Mail_InitEmpty(&mail);

  Blocked_AddAddressFromFile(&blocked, argv[1]);
  printf ("Blocked addresses readed\n");

  Suspected_AddWordWeightFromFile(&suspected, argv[2]);
  printf ("Suspected words readed\n");

  Mail_AddMailsFromDirectory(&mail, argv[3]);
  printf ("Mails readed\n");
  Mail_Print(mail);

	Mail_ClassifyAll(&mail, blocked, suspected);
  printf ("Mails classified\n");

	Mail_RenameAll(mail);
  printf ("Mails renamed\n");

	Blocked_Destroy(&blocked);
	Suspected_Destroy(&suspected);
	Mail_Destroy(&mail);

	exit(EXIT_SUCCESS);
}
