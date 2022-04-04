// File : Blocked_.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "blocked.h"

//===============================================
void Blocked_InitEmpty(Blocked * self)
{
	self->capacity = 0;
  self->length = 0;
	self->mailAddress = NULL;
}

//===============================================
bool Blocked_IsFull(Blocked self) {
  return self.length == self.capacity;
}

//===============================================
void Blocked_Realloc(Blocked * self)
{
  if (self->capacity == 0)
    self->capacity = 1;

  int newCapacity = self->capacity * 2;
  BlockedAddress * newMails = realloc(self->mailAddress, newCapacity * sizeof * newMails);
  assert (newMails != NULL );
  self->capacity = newCapacity;
  self->mailAddress = newMails;
}

//===============================================
void Blocked_AddAddress(Blocked * self, BlockedAddress mailAddress)
{
  if (Blocked_IsFull(*self))
    Blocked_Realloc(self);

  strcpy(self->mailAddress[self->length], mailAddress);
  self->length++;
}

//===============================================
void Blocked_AddAddressFromFile(Blocked * self, char * fileName)
{
  FILE * fin;
  BlockedAddress mailAddress;

  fin = fopen(fileName, "r");
  assert (fin != NULL);

  while (!feof(fin)){
    fscanf(fin,"%s\n", mailAddress);
      Blocked_AddAddress(self, mailAddress);
  }
  fclose(fin);
}

//===============================================
bool Blocked_IsBlocked(Blocked self, BlockedAddress mailAddress)
{
  for (int i=0; i<self.length; i++){
    if (!strcmp(self.mailAddress[i], mailAddress))
      return true;
  }

  return false;
}

//===============================================
void Blocked_Destroy(Blocked * self)
{
  free(self->mailAddress);
  Blocked_InitEmpty(self);
}
