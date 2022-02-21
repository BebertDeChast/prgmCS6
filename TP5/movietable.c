// File : movietable.c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "movietable.h"

//===============================================
MovieTable *MovieTable_AllocEmpty()
{
  MovieTable *newMovieTable = malloc(sizeof *newMovieTable);
  newMovieTable->movies = NULL;
  newMovieTable->capacity = 0;
  newMovieTable->used = NULL;
  return newMovieTable;
}

//===============================================
bool MovieTable_OverCapacity(MovieTable self, int id)
{
  // TODO
}

//===============================================
void MovieTable_Realloc(MovieTable *self)
{
  int newCapacity = self->capacity + 100;

  Movie *newMovies = realloc(self->movies, newCapacity * sizeof *newMovies);
  assert(newMovies != NULL);
  bool *newUsed = realloc(self->used, newCapacity * sizeof *newUsed);
  assert(newUsed != NULL);
  for (int i = self->capacity; i < newCapacity; i++)
    newUsed[i] = false;
  self->movies = newMovies;
  self->used = newUsed;
  self->capacity = newCapacity;
}

//===============================================
void MovieTable_AddMovie(MovieTable *self, Movie movie)
{
  // TODO
}

//===============================================
void MovieTable_ReadMoviesFromFile(MovieTable *self, char *filename)
{
  // TODO
}

//===============================================
int MovieTable_GetCapacity(MovieTable self)
{
  return self.capacity;
}

//===============================================
Movie MovieTable_GetMovie(MovieTable self, int id)
{
  // TODO
}

//===============================================
void MovieTable_Print(MovieTable self, FILE *fout)
{
  // TODO
}

//===============================================
void MovieTable_Destroy(MovieTable *self)
{
  if (self->movies != NULL)
    free(self->movies);
  if (self->used != NULL)
    free(self->used);

  self->movies = NULL;
  self->used = NULL;
  self->capacity = 0;
}
