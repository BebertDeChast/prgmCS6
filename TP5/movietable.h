// File : movietable.h
#ifndef MOVIETABLE_H
#define MOVIETABLE_H
#include <stdbool.h>
#include "movie.h"

typedef struct MovieTable
{
    Movie *movies;
    int capacity;
    bool *used;
} MovieTable;

MovieTable *MovieTable_AllocEmpty();
bool MovieTable_OverCapacity(MovieTable self, int id);
void MovieTable_Realloc(MovieTable *self);
void MovieTable_AddMovie(MovieTable *self, Movie movie);
void MovieTable_ReadMoviesFromFile(MovieTable *self, char *filename);
int MovieTable_GetCapacity(MovieTable self);
Movie MovieTable_GetMovie(MovieTable self, int id);
void MovieTable_Print(MovieTable self, FILE *fout);
void MovieTable_Destroy(MovieTable *self);

#endif
