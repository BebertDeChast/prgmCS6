// File : tree.h
#ifndef TREE_H
#define TREE_H

#include <stdbool.h>
#include "node.h"
#include "movie.h"
#include "movietable.h"

typedef struct Tree {
  int size;
  Node *root;
} Tree;

void Tree_InitEmpty(Tree *self);
void Tree_InsertMovie(Tree *self, Movie movie);
void Tree_CreateFromMovieTable(Tree *self, MovieTable movietable);
bool Tree_Search(Tree self, MovieTitle Title);
void Tree_Suggestions(Node *self, MovieTable movieTable,  MovieTitle prefix);
int Tree_AutoSuggestions(Tree self, MovieTable movieTable, MovieTitle prefix);
int Tree_GetSize(Tree self);
void Tree_Print (Tree self, FILE * fout);
void Tree_Destroy(Tree *self);


#endif
