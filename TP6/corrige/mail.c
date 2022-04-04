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
void Mail_InitEmpty(Mail * self)
{
	self->capacity = 0;
  self->length = 0;
  self->sender = NULL;
	self->subject = NULL;
	self->classification = NULL;
	self->totalWeight = NULL;
	self->fileName = NULL;
}

//===============================================
bool Mail_IsFull(Mail self)
{
  return self.length == self.capacity;
}

//===============================================
void Mail_Realloc(Mail * self)
{
  if (self->capacity == 0)
    self->capacity = 1;

  int newCapacity = self->capacity * 2;
  MailAddress * newSender = realloc(self->sender, newCapacity * sizeof * newSender);
  assert (newSender != NULL );
  Subject * newSubject = realloc(self->subject, newCapacity * sizeof * newSubject);
  assert (newSubject != NULL );
  MailClassification * newClassification = realloc(self->classification, newCapacity * sizeof * newClassification);
  assert (newClassification != NULL );
  int * newTotalWeight = realloc(self->totalWeight, newCapacity * sizeof * newTotalWeight);
  assert (newTotalWeight != NULL );
  FileName * newFileName = realloc(self->fileName, newCapacity * sizeof * newFileName);
  assert (newFileName != NULL );

  self->capacity = newCapacity;
  self->sender = newSender;
  self->subject = newSubject;
  self->classification = newClassification;
  self->totalWeight = newTotalWeight;
  self->fileName = newFileName;
}

//===============================================
bool Mail_IsMail(FILE * fin)
{
  char Mail_[100];

  fscanf(fin, "%s\n", Mail_);

  return (!strcmp(Mail_, "#email"));
}

//===============================================
void Mail_GetSender(FILE * fin, MailAddress sender)
{
  fscanf(fin, "%s\n", sender);
}

//===============================================
void Mail_GetSubject(FILE * fin, Subject subject)
{
  fgets(subject, MAX_SUBJECT_SIZE, fin);
}

//===============================================
void Mail_AddMail(Mail * self, FileName fileName)
{
  FILE * fin = fopen(fileName, "r");

  if (!Mail_IsMail(fin))
    return;

  if (Mail_IsFull(*self))
    Mail_Realloc(self);

  Mail_GetSender(fin, self->sender[self->length]);
  Mail_GetSubject(fin,  self->subject[self->length]);
  strcpy(self->fileName[self->length], fileName);
  self->length++;

  fclose(fin);
}

//===============================================
void Mail_AddMailsFromDirectory(Mail * self, char * dirName)
{
  struct dirent *directoryEntry;
  DIR *directory;
  struct stat fileInfo;
  FileName fileName;

  directory = opendir(dirName);

  assert(directory!=NULL);

  while ((directoryEntry = readdir(directory))) {
    sprintf(fileName, "%s/%s", dirName,directoryEntry->d_name);
    assert(stat (fileName, &fileInfo)!=-1);
    if (S_ISREG(fileInfo.st_mode)) {
        Mail_AddMail(self, fileName);
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
  if (Blocked_IsBlocked(blocked, self->sender[index])){
    self->classification[index] = BLOCKED;
    return;
  }
  if (Suspected_IsSuspected(suspected, self->subject[index], 60)){
    self->classification[index] = SUSPECTED;
    self->totalWeight[index] = Suspected_GetTotalWeight(suspected, self->subject[index]);
    return;
  }

  self->classification[index] = CLEAN;
}

//===============================================
void Mail_ClassifyAll(Mail *self, Blocked blocked, Suspected suspected)
{
  for (int i=0; i<self->length; i++){
    Mail_Classify(self, i, blocked, suspected);
  }
}

//===============================================
void Mail_Rename(Mail self, int index)
{
  FileName newName;

  switch(self.classification[index]){
    case BLOCKED : sprintf(newName, "%s[BLOCKED]", self.fileName[index]);
                   printf("Name : %s - NewName: %s\n", self.fileName[index], newName);
                   rename(self.fileName[index], newName);
      break;
    case SUSPECTED : sprintf(newName, "%s[SUSPECTED %d]", self.fileName[index], self.totalWeight[index]);
                   printf("Name : %s - NewName: %s\n", self.fileName[index], newName);
                   rename(self.fileName[index], newName);
      break;
  }
}

//===============================================
void Mail_RenameAll(Mail self)
{
  for (int i=0; i<self.length; i++){
    Mail_Rename(self, i);
  }
}

//===============================================
void Mail_Print(Mail self)
{
  for (int i=0; i<self.length; i++){
    printf ("Sender : %s\nSubject : %s\n", self.sender[i], self.subject[i]);
  }
}

//===============================================
void Mail_Destroy(Mail *self)
{
  free(self->sender);
  free(self->subject);
  free(self->classification);
  free(self->totalWeight);
  free(self->fileName);
  Mail_InitEmpty(self);
}
