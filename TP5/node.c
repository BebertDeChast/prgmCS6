// File : node.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

//===============================================
Node *Node_AllocEmpty()
{
  Node *node;
  node = malloc(sizeof(Node));
  node->isWordEnd = false;
  node->movieID = -1;
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    node->children[i] = NULL;
  }
  return node;
}

//===============================================
bool Node_IsLastNode(Node self)
{
  for (int i = 0; i < ALPHABET_SIZE; i++)
  {
    if (self.children[i] != NULL)
    {
      return false;
    }
  }
  return true;
}

//===============================================
bool Node_IsWordEnd(Node self)
{
  return self.isWordEnd;
}

//===============================================
int Node_GetMovieID(Node self)
{
  return self.movieID;
}

//===============================================
void Node_Print(Node self, FILE *fout)
{
  if (Node_IsLastNode(self))
  {
    printf("\n");
    return;
  }

  for (int i = 0; i < ALPHABET_SIZE; i++)
    if (self.children[i])
    {
      printf("-%c", (char)(32 + i));
      Node_Print(*self.children[i], fout);
    }
}

//===============================================
void Node_DestroyTree(Node *self)
{
  if (Node_IsLastNode(*self))
  {
    free(self);
  }
  else
  {
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
      if (self->children[i] != NULL)
      {
        Node_DestroyTree(self->children[i]);
      }
    }
  }
}
