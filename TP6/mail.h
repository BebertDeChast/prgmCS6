// File : Mail_.h
#ifndef MAIL_H
#define MAIL_H
#include <stdbool.h>
#include "blocked.h"
#include "suspected.h"

#define MAX_MAILADDRESS_SIZE 256
#define MAX_SUBJECT_SIZE 1024
#define MAX_FILENAME_SIZE 256

typedef char MailAddress[MAX_MAILADDRESS_SIZE];
typedef char Subject[MAX_SUBJECT_SIZE];
typedef char Filename[MAX_FILENAME_SIZE];

typedef enum MailClassification {
CLEAN, BLOCKED, SUSPECTED
} MailClassification;

typedef struct Mail {
	int capacity;
  int length;
	MailAddress * sender;
	Subject * subject;
	MailClassification * classification;
	int * totalWeight;
	Filename * filename;
} Mail;

void Mail_InitEmpty(Mail * self);
bool Mail_IsFull(Mail self);
void Mail_Realloc(Mail * self);
bool Mail_IsMail(FILE * fin);
void Mail_GetSender(FILE * fin, MailAddress sender);
void Mail_GetSubject(FILE * fin, Subject subject);
void Mail_AddMail(Mail * self, Filename filename);
void Mail_AddMailsFromDirectory(Mail * self, char * dirName);
bool Mail_IsBlocked(Mail self, int index);
bool Mail_IsSuspected(Mail self, int index);
bool Mail_IsClean(Mail self, int index);
void Mail_Classify(Mail * self, int index, Blocked  blocked, Suspected  suspected);
void Mail_ClassifyAll(Mail * self, Blocked  blocked, Suspected  suspected);
void Mail_Rename(Mail self, int index);
void Mail_RenameAll(Mail self);
void Mail_Print(Mail self);
void Mail_Destroy(Mail * self);

#endif
