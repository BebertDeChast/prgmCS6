// File : node.h
#ifndef NODE_H
#define NODE_H
#include <stdbool.h>

#define ALPHABET_SIZE 224
#define MOVIEID_MAX_SIZE 256

#define CHAR_TO_INDEX(c) ((int)c - (int)' ')

typedef struct Node {
  	struct Node *children[ALPHABET_SIZE];
  	bool isWordEnd;
  	int movieID;
} Node;

Node * Node_AllocEmpty();
bool Node_IsLastNode(Node self);
bool Node_IsWordEnd(Node self);
int Node_GetMovieID(Node self);
void Node_Print(Node self, FILE * fout);
void Node_DestroyTree(Node *self);

#endif
