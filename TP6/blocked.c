// File : Blocked_.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "blocked.h"

//===============================================
void Blocked_InitEmpty(Blocked *self)
{
  self->capacity = 0;
  self->length = 0;
  self->mailAddress = NULL;
}

//===============================================
bool Blocked_IsFull(Blocked self)
{
  return self.length == self.capacity;
}

//===============================================
void Blocked_Realloc(Blocked *self)
{
  if (self->capacity > 0)
  {
    self->capacity *= 2;
  }
  else
  {
    self->capacity = 2;
  }
  self->mailAddress = realloc(self->mailAddress, self->capacity * sizeof *self->mailAddress);
  assert(self->mailAddress != NULL);
}

//===============================================
void Blocked_AddAddress(Blocked *self, BlockedAddress mailAddress)
{
  if (Blocked_IsFull(*self))
  {
    Blocked_Realloc(self);
  }
  strcpy(self->mailAddress[self->length], mailAddress);
  self->length++;
}

//===============================================
void Blocked_AddAddressFromFile(Blocked *self, char *filename)
{
  FILE *file;
  BlockedAddress address;
  file = fopen(filename, "r");
  assert(file != NULL);

  while (fgets(address, MAX_BLOCKEDADDRESS_SIZE, file) != NULL)
  {
    if (strlen(address) > 1)
    {
      address[strlen(address) - 1] = '\0'; // ! Remove  pesky '\n' from address 
      Blocked_AddAddress(self, address);
    }
  }
  fclose(file);
}

//===============================================
bool Blocked_IsBlocked(Blocked self, BlockedAddress mailAddress)
{
  for (int i = 0; i < self.length; i++)
  {
    // printf("Comparing %s with %s\n ", self.mailAddress[i], mailAddress);
    if (!strcmp(self.mailAddress[i], mailAddress))
    {
      return true;
    }
  }
  return false;
}

//===============================================
void Blocked_Destroy(Blocked *self)
{
  free(self->mailAddress);
  Blocked_InitEmpty(self);
}
