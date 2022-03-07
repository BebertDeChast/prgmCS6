// File : mail.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "mail.h"

//===============================================
void Mail_InitEmpty(Mail *self)
{
  self->capacity = 0;
  self->length = 0;
  self->sender = NULL;
  self->subject = NULL;
  self->classification = NULL;
  self->totalWeight = NULL;
  self->filename = NULL;
}

//===============================================
bool Mail_IsFull(Mail self)
{
  return self.length == self.capacity;
}

//===============================================
void Mail_Realloc(Mail *self)
{
  if (self->capacity == 0)
    self->capacity = 1;

  int newCapacity = self->capacity * 2;
  MailAddress *newSender = realloc(self->sender, newCapacity * sizeof *newSender);
  assert(newSender != NULL);
  Subject *newSubject = realloc(self->subject, newCapacity * sizeof *newSubject);
  assert(newSubject != NULL);
  MailClassification *newClassification = realloc(self->classification, newCapacity * sizeof *newClassification);
  assert(newClassification != NULL);
  int *newTotalWeight = realloc(self->totalWeight, newCapacity * sizeof *newTotalWeight);
  assert(newTotalWeight != NULL);
  Filename *newFilename = realloc(self->filename, newCapacity * sizeof *newFilename);
  assert(newFilename != NULL);

  self->capacity = newCapacity;
  self->sender = newSender;
  self->subject = newSubject;
  self->classification = newClassification;
  self->totalWeight = newTotalWeight;
  self->filename = newFilename;
}

//===============================================
bool Mail_IsMail(FILE *fin)
{
  char line[10];
  fgets(line, 10, fin);
  return !strcmp(line, "#email");
}

//===============================================
void Mail_GetSender(FILE *fin, MailAddress sender)
{
  fscanf(fin, "%s\n", sender);
}

//===============================================
void Mail_GetSubject(FILE *fin, Subject subject)
{
  fgets(subject, MAX_SUBJECT_SIZE, fin);
}

//===============================================
void Mail_AddMail(Mail *self, Filename filename)
{
  // * Reading file
  FILE *file;
  MailAddress sender;
  Subject subject;
  file = fopen(filename, "r");
  if (!Mail_IsMail(file))
  {
    perror("File is not a mail");
    exit(EXIT_FAILURE);
  }
  Mail_GetSender(file, sender);
  Mail_GetSubject(file, subject);

  // * Filling self with read data
  if (Mail_IsFull(*self))
  {
    Mail_Realloc(self);
  }
  strcpy(self->sender[self->length], sender);
  strcpy(self->subject[self->length], subject);
  strcpy(self->filename[self->length], filename);
  self->length++;
  fclose(file);
}

//===============================================
void Mail_AddMailsFromDirectory(Mail *self, char *dirName)
{
  DIR *directory;
  struct dirent *current_file;
  struct stat *buffer;
  directory = opendir(dirName);
  assert(directory != NULL);

  while ((current_file = readdir(directory)))
  {
    int test = stat(current_file->d_name, buffer)
    assert(test != -1);
    if (S_ISREG(buffer->st_mode))
    {
      Mail_AddMail(self, current_file->d_name);
    }
  }
  closedir(directory);
}

//===============================================
bool Mail_IsBlocked(Mail self, int index)
{
  return self.classification[index] == BLOCKED;
}

//===============================================
bool Mail_IsSuspected(Mail self, int index)
{
  return self.classification[index] == SUSPECTED;
}

//===============================================
bool Mail_IsClean(Mail self, int index)
{
  return !(Mail_IsBlocked(self, index) || Mail_IsSuspected(self, index));
}

//===============================================
void Mail_Classify(Mail *self, int index, Blocked blocked, Suspected suspected)
{
  assert(index < self->length);
  self->totalWeight[index] = Suspected_GetTotalWeight(suspected, self->subject[index]);
  if (Blocked_IsBlocked(blocked, self->sender[index]))
  {
    self->classification[index] = BLOCKED;
  }
  else if (Suspected_IsSuspected(suspected, self->subject[index], 60))
  {
    self->classification[index] = SUSPECTED;
  }
  else
  {
    self->classification[index] = CLEAN;
  }
}

//===============================================
void Mail_ClassifyAll(Mail *self, Blocked blocked, Suspected suspected)
{
  for (int i = 0; i < self->length; i++)
  {
    Mail_Classify(self, i, blocked, suspected);
  }
}

//===============================================
void Mail_Rename(Mail self, int index)
{
  assert(index < self.length);
  char  *new_name;
  if (self.classification[index] == CLEAN)
  {
    return;
  }

  if (self.classification[index] == BLOCKED)
  {
    new_name = strcat(self.filename[index], "[BLOCKED]");
  }
  else if (self.classification[index] == SUSPECTED)
  {
    sprintf(new_name, "%s[SUSPECTED %d]", self.filename[index], self.totalWeight[index]);
  }
  rename(self.filename[index], new_name);
  strcpy(self.filename[index], new_name);
}

//===============================================
void Mail_RenameAll(Mail self)
{
  for (int i = 0; i < self.length; i++)
  {
    Mail_Rename(self, i);
  }
}

//===============================================
void Mail_Print(Mail self)
{
  for (int i = 0; i < self.length; i++)
  {
    printf("Sender : %s\nSubject : %s\n", self.sender[i], self.subject[i]);
  }
}

//===============================================
void Mail_Destroy(Mail *self)
{
  free(self->sender);
  free(self->subject);
  free(self->classification);
  free(self->totalWeight);
  free(self->filename);
  Mail_InitEmpty(self);
}
