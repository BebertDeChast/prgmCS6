// File : binarytree.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "movietable.h"
#include "tree.h"

int main(int argc, char *argv[])
{
  MovieTitle query;
  MovieTable *movieTable;
  Tree tree;

  if (argc < 2)
  {
    printf("Usage : ./moviesuggestion moviefile\n");
    exit(EXIT_FAILURE);
  }

  movieTable = MovieTable_AllocEmpty();

  MovieTable_ReadMoviesFromFile(movieTable, argv[1]);
  // MovieTable_Print(*movieTable, stdout);

  printf("==================\n");

  Tree_InitEmpty(&tree);
  Tree_CreateFromMovieTable(&tree, *movieTable);
  printf("Tree size : %d\n", Tree_GetSize(tree));

  // Tree_Print(tree, stdout);
  while (1)
  {
    printf("Entry your query: ");
    fgets(query, MOVIE_TITLE_MAX_SIZE, stdin);
    printf("%s", query);
    int comp = Tree_AutoSuggestions(tree, *movieTable, query);
    if (comp == -1)
      printf("No other strings found with this prefix\n");
    else if (comp == 0)
      printf("No string found with this prefix\n");
  }

  MovieTable_Destroy(movieTable);
  Tree_Destroy(&tree);
  exit(EXIT_SUCCESS);
}
