// File : node.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "node.h"

//===============================================
Node * Node_AllocEmpty()
{
	//TODO
}

//===============================================
bool Node_IsLastNode(Node self)
{
	//TODO
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
void Node_Print(Node self, FILE * fout)
{
  if (Node_IsLastNode(self)){
    printf("\n");
    return;
  }

  for (int i=0; i < ALPHABET_SIZE; i++)
    if (self.children[i]){
      printf ("-%c", (char)(32+i));
      Node_Print(*self.children[i], fout);
    }
}

//===============================================
void Node_DestroyTree(Node *self)
{
	//TODO
}
