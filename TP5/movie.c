// File : movie.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "movie.h"

//===============================================
Movie *Movie_AllocEmpty()
{
  Movie *newMovie = malloc(sizeof *newMovie);
  strcpy(newMovie->title, "");
  newMovie->genre = NULL;
  newMovie->numberOfGenre = 0;
  return newMovie;
}

//===============================================
void Movie_GenreRealloc(Movie *self)
{
  self->genre = realloc(self->genre, (self->numberOfGenre + 1) * sizeof self->genre);
}

//===============================================
void Movie_SetTitle(Movie *self, MovieTitle title)
{
  strcpy(self->title, title);
}

//===============================================
void Movie_SetID(Movie *self, int ID)
{
  self->ID = ID;
}

//===============================================
void Movie_AddGenre(Movie *self, GenreType genre)
{
  Movie_GenreRealloc(self);
  strcpy(self->genre[self->numberOfGenre], genre);
  self->numberOfGenre++;
}

//===============================================
Movie *Movie_CreateMovieFromLine(char *line)
{
  Movie *newMovie = Movie_AllocEmpty();
  char *newline = strdup(line);
  char *ptr = strtok(newline, ",");
  Movie_SetID(newMovie, atoi(ptr));

  ptr = strtok(NULL, "\"");
  Movie_SetTitle(newMovie, ptr);
  ptr = strtok(NULL, "\"");
  ptr = strtok(NULL, "\"");
  strcpy(newline, ptr);
  ptr = strtok(newline, "|");

  while (ptr != NULL)
  {
    Movie_AddGenre(newMovie, ptr);
    ptr = strtok(NULL, "|");
  }
  return newMovie;
}

//===============================================
void Movie_Print(Movie self, FILE *fout)
{
  fprintf(fout, "%d - ", self.ID);
  fprintf(fout, "%s : ", self.title);
  for (int i = 0; i < self.numberOfGenre - 1; i++)
    fprintf(fout, "%s|", self.genre[i]);
  fprintf(fout, "%s\n", self.genre[self.numberOfGenre - 1]);
}

//===============================================
void Movie_Destroy(Movie *self)
{
  free(self->genre);
  free(self);
}
