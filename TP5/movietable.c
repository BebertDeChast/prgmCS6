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
  return (self.capacity <= id);
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
  while (MovieTable_OverCapacity(*self, movie.ID)) // ? Reallocating memory to welcome the new movie
  {
    MovieTable_Realloc(self);
  }
  self->movies[movie.ID] = movie;
  self->used[movie.ID] = true;
}

//===============================================
void MovieTable_ReadMoviesFromFile(MovieTable *self, char *filename)
{
  FILE *file;
  Movie *movie;
  file = fopen(filename, "r");
  assert(file != NULL);

  char line[256];
  fgets(line, 256, file);
  while (fgets(line, 256, file) != NULL)
  {
    if (strlen(line) > 1)
    {
      movie = Movie_CreateMovieFromLine(line);
      MovieTable_AddMovie(self, *movie);
    }
  }
  fclose(file);
}

//===============================================
int MovieTable_GetCapacity(MovieTable self)
{
  return self.capacity;
}

//===============================================
Movie MovieTable_GetMovie(MovieTable self, int id)
{
  return self.movies[id];
}

//===============================================
void MovieTable_Print(MovieTable self, FILE *fout)
{
  for (int i = 0; i <= self.capacity; i++)
  {
    if (self.used[i])
    {
      Movie_Print(self.movies[i], fout);
    }
  }
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
