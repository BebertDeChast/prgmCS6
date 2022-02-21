// File : full.h
#ifndef FULL_H
#define FULL_H
#include "sparse.h"

typedef struct SparseMatrix SparseMatrix; // forward definition

typedef struct FullMatrix {
  int rows, columns;
  double **elements;
} FullMatrix;

void FullMatrix_InitEmpty(FullMatrix * self);
void FullMatrix_Alloc(FullMatrix * self,  int rows, int columns);
void FullMatrix_PutElement(FullMatrix * self, int row, int column, double element);
double FullMatrix_GetElement(FullMatrix self, int row, int column);
void FullMatrix_ReadFromFile(FullMatrix * self, char * fileName);
void FullMatrix_WriteToFile(FullMatrix self, char * fileName);
int  FullMatrix_CountNonZeroElements(FullMatrix self);
void FullMatrix_Convert(FullMatrix * self, SparseMatrix sparse);
void FullMatrix_Print(FullMatrix self, FILE *fout);
void FullMatrix_Destroy(FullMatrix * self);

#endif
