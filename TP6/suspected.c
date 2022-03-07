// File : suspected.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "suspected.h"

//===============================================
void Suspected_InitEmpty(Suspected * self)
{
	self->capacity = 0;
  self->length = 0;
	self->word = NULL;
  self->weight = NULL;
}

//===============================================
bool Suspected_IsFull(Suspected self)
{
  return self.length == self.capacity;
}

//===============================================
void Suspected_Realloc(Suspected * self)
{
  if (self->capacity == 0)
    self->capacity = 1;

  int newCapacity = self->capacity * 2;
  Word * newWord = realloc(self->word, newCapacity * sizeof * newWord);
  assert (newWord != NULL );
  int * newWeight = realloc(self->weight, newCapacity * sizeof * newWeight);
  assert (newWeight != NULL );

  self->capacity = newCapacity;
  self->word = newWord;
  self->weight = newWeight;
}

//===============================================
void Suspected_AddWordWeight(Suspected * self, Word word, int weight)
{
  if (Suspected_IsFull(*self))
    Suspected_Realloc(self);

  strcpy(self->word[self->length], word);
  self->weight[self->length] = weight;
  self->length++;
}

//===============================================
void Suspected_AddWordWeightFromFile(Suspected * self, char * filename)
{
  FILE * fin;
  Word word;
  int weight;

  fin = fopen(filename, "r");
  assert (fin != NULL);

  while (!feof(fin)){
    fscanf(fin, "%s %d\n", word, &weight);
    Suspected_AddWordWeight(self, word, weight);
  }
  fclose(fin);
}

//===============================================
int Suspected_GetWeight(Suspected self, Word word)
{
 // TODO
}

//===============================================
int Suspected_GetTotalWeight(Suspected self, char * subject)
{
 // TODO
}

//===============================================
bool Suspected_IsSuspected(Suspected self, char * subject, int threshold)
{
 // TODO
}

//===============================================
void Suspected_Destroy(Suspected * self)
{
  free(self->word);
  free(self->weight);
  Suspected_InitEmpty(self);
}
