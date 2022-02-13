// File : sparse.h
#ifndef SPARSE_H
#define SPARSE_H
#include "full.h"

typedef struct FullMatrix FullMatrix; // forward definition

typedef struct SparseMatrix
{
  int rows, columns;
  int nbElements;
  int *irows;
  int *icolumns;
  double *elements;
} SparseMatrix;

void SparseMatrix_InitEmpty(SparseMatrix *self);
void SparseMatrix_Alloc(SparseMatrix *self, int rows, int columns, int nbElements);
double SparseMatrix_GetElement(SparseMatrix self, int row, int column);
void SparseMatrix_ReadFromFile(SparseMatrix *self, char *fileName);
void SparseMatrix_WriteToFile(SparseMatrix self, char *fileName);
void SparseMatrix_Convert(SparseMatrix *self, FullMatrix full);
void SparseMatrix_Print(SparseMatrix self, FILE *fout);
void SparseMatrix_Destroy(SparseMatrix *self);
void SparseMatrix_AddValue(SparseMatrix *self, int row, int column, double element);
#endif
