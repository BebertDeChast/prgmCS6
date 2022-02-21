// File : tree.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "tree.h"

//===============================================
void Tree_InitEmpty(Tree *tree)
{
  tree->size = 0;
  tree->root = Node_AllocEmpty();
}

//===============================================
void Tree_InsertMovie(Tree *self, Movie movie)
{
  // TODO
}

//===============================================
void Tree_CreateFromMovieTable(Tree *self, MovieTable movietable)
{
  // TODO
}

//===============================================
bool Tree_Search(Tree self, MovieTitle title)
{
  // TODO
}

//===============================================
void Tree_Suggestions(Node *self, MovieTable movieTable, MovieTitle prefix)
{
  // TODO
}

//===============================================
int Tree_AutoSuggestions(Tree self, MovieTable movieTable, MovieTitle prefix)
{
  // TODO
}

//===============================================
int Tree_GetSize(Tree self)
{
  return self.size;
}

//===============================================
void Tree_Print(Tree self, FILE *fout)
{
  printf("\n");
  Node_Print(*self.root, fout);
}

//===============================================
void Tree_Destroy(Tree *self)
{
  Node_DestroyTree(self->root);
  self->size = 0;
}
