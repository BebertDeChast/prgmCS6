// File : Suspected_.h
#ifndef SUSPECTED_H
#define SUSPECTED_H
#include <stdbool.h>

#define MAX_WORD_SIZE 256

typedef char Word[MAX_WORD_SIZE];

typedef struct Suspected {
	int capacity;
  int length;
	Word *word;
	int *weight;
} Suspected;

void Suspected_InitEmpty(Suspected * self);
bool Suspected_IsFull(Suspected self);
void Suspected_Realloc(Suspected * self);
void Suspected_AddWordWeight(Suspected * self, Word word, int weight);
void Suspected_AddWordWeightFromFile(Suspected * self, char * filename);
int Suspected_GetWeight(Suspected self, Word word);
int Suspected_GetTotalWeight(Suspected self, char * subject);
bool Suspected_IsSuspected(Suspected self, char * subject, int threshold);
void Suspected_Destroy(Suspected * self);
#endif
