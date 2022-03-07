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
bool Blocked_IsFull(Blocked self) 
{
  return self.length == self.capacity;
}

//===============================================
void Blocked_Realloc(Blocked * self)
{
 // TODO
}

//===============================================
void Blocked_AddAddress(Blocked * self, BlockedAddress mailAddress)
{
 // TODO
}

//===============================================
void Blocked_AddAddressFromFile(Blocked * self, char * filename)
{
 // TODO
}

//===============================================
bool Blocked_IsBlocked(Blocked self, BlockedAddress mailAddress)
{
 // TODO
}

//===============================================
void Blocked_Destroy(Blocked * self)
{
  free(self->mailAddress);
  Blocked_InitEmpty(self);
}
