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
  Node *current_node;
  current_node = self->root;
  int children_index;
  char c;
  for (size_t i = 0; i < (int)strlen(movie.title); i++)
  {
    c = movie.title[i];
    children_index = CHAR_TO_INDEX(c);
    //! Rustine
    if (children_index < 0) {
      children_index = -children_index;
    }
    printf("Working with index : %d\n", children_index);
    printf("%d\n", sizeof(current_node->children[children_index]));
    printf("%d\n", current_node->children[children_index]);
    if (current_node->children[children_index] == NULL)
    {
      current_node->children[children_index] = Node_AllocEmpty();
    }
    current_node = current_node->children[children_index];
    assert(current_node != NULL);
  }
  current_node->isWordEnd = true;
  current_node->movieID = movie.ID;
  self->size++;
}

//===============================================
void Tree_CreateFromMovieTable(Tree *self, MovieTable movietable)
{
  // Tree_InitEmpty(self);
  for (int i = 0; i <= movietable.capacity; i++)
  {
    if (movietable.used[i])
    {
      printf("Trying to insert in tree : %d, %s\n", movietable.movies[i].ID, movietable.movies[i].title);
      Tree_InsertMovie(self, movietable.movies[i]);
    }
  }
}

//===============================================
bool Tree_Search(Tree self, MovieTitle title)
{
  Node *current_node;
  current_node = self.root;
  int children_index;
  for (size_t i = 0; i < strlen(title); i++)
  {
    children_index = CHAR_TO_INDEX(title[i]);
    if (current_node->children[children_index] == NULL)
    {
      return false;
    }
    current_node = current_node->children[children_index];
    assert(current_node != NULL);
  }
  if (current_node->isWordEnd)
  {
    return true;
  }
  return false;
}

//===============================================
void Tree_Suggestions(Node *self, MovieTable movieTable, MovieTitle prefix)
{
  if (self->isWordEnd)
  {  
    Movie_Print(movieTable.movies[self->movieID], stdout);
  }
  for (int j = 0; j < ALPHABET_SIZE; j++)
  {
    if (self->children[j] != NULL) {
      Tree_Suggestions(self->children[j], movieTable, prefix);
    }
  }
}

//===============================================
int Tree_AutoSuggestions(Tree self, MovieTable movieTable, MovieTitle prefix)
{
  Node *current_node;
  current_node = self.root;
  int children_index;
  for (int i = 0; i < (strlen(prefix) - 1); i++)
  {
    children_index = CHAR_TO_INDEX(prefix[i]);
    if (current_node->children[children_index] == NULL)
    {
      return 0;
    }
    current_node = current_node->children[children_index];
  }
  if (current_node->isWordEnd)
  {
    return 1;
  }
  Tree_Suggestions(current_node, movieTable, prefix);
  return -1;
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
