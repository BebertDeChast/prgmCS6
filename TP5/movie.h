// File : movie.h
#ifndef MOVIE_H
#define MOVIE_H

#define MOVIE_TITLE_MAX_SIZE 256
typedef char MovieTitle[MOVIE_TITLE_MAX_SIZE];

#define GENRE_TYPE_MAX_SIZE 64
typedef char GenreType[GENRE_TYPE_MAX_SIZE];

typedef struct Movie{
    MovieTitle title;
    GenreType *genre;
    int numberOfGenre;
    int ID;
} Movie;

Movie * Movie_AllocEmpty();
void Movie_GenreRealloc(Movie *self);
void Movie_SetTitle(Movie * self, MovieTitle title);
void Movie_SetID(Movie * self, int ID);
void Movie_AddGenre(Movie * self, GenreType genre);
Movie * Movie_CreateMovieFromLine(char *line);
void Movie_Print(Movie self, FILE *fout);
void Movie_Destroy(Movie * self);

#endif
