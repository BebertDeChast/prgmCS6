// File : blocked.h
#ifndef BLOCKED_H
#define BLOCKED_H
#include <stdbool.h>

#define MAX_BLOCKEDADDRESS_SIZE 256

typedef char BlockedAddress[MAX_BLOCKEDADDRESS_SIZE];

typedef struct Blocked {
	int capacity;
  int length;
	BlockedAddress *mailAddress;
} Blocked;

void Blocked_InitEmpty(Blocked * self);
bool Blocked_IsFull(Blocked  self);
void Blocked_Realloc(Blocked * self);
void Blocked_AddAddress(Blocked * self, BlockedAddress mailAddress);
void Blocked_AddAddressFromFile(Blocked * self, char * filename);
bool Blocked_IsBlocked(Blocked self, BlockedAddress mailAddress);
void Blocked_Destroy(Blocked * self);

#endif
