// File : sparse.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sparse.h"


//===============================================
void SparseMatrix_InitEmpty(SparseMatrix * self) {
	self->columns = 0;
  self->rows = 0;
  self->nbElements = 0;
  self->irows = NULL;
  self->icolumns = NULL;
  self->elements = NULL;
}

//===============================================
void SparseMatrix_Alloc(SparseMatrix * self, int rows,  int columns, int nbElements) {
	assert(rows > 0 && columns > 0 && nbElements > 0);
  self->rows = rows;
  self->columns = columns;
  self->nbElements = nbElements;
  self->irows = malloc(nbElements * sizeof * self->irows);
  self->icolumns = malloc(nbElements * sizeof * self->icolumns);
  self->elements = malloc(nbElements * sizeof * self->elements);
  assert(self->irows != NULL && self->icolumns != NULL && self->elements != NULL);
}

//===============================================
double SparseMatrix_GetElement(SparseMatrix self, int row, int column) {
	for (int i = 0; i < self.nbElements; i++) {
    if (self.irows[i] == row && self.icolumns[i] == column) {
      return self.elements[i];
    }
  }
  return 0;
}

//===============================================
void SparseMatrix_ReadFromFile(SparseMatrix * self, char * fileName)
{
  FILE *fin;
  int rows, columns, nbElements;

  fin = fopen(fileName, "r");

  fscanf(fin,"%d", &rows);
  fscanf(fin,"%d", &columns);
  fscanf(fin,"%d", &nbElements);

  SparseMatrix_InitEmpty(self);
  SparseMatrix_Alloc(self, rows, columns, nbElements);

  for (int i=0; i<nbElements; i++)
    fscanf(fin, "%d", &self->irows[i]);
  for (int i=0; i<nbElements; i++)
    fscanf(fin, "%d", &self->icolumns[i]);
  for (int i=0; i<nbElements; i++)
    fscanf(fin, "%lf", &self->elements[i]);

  fclose(fin);
}


//===============================================
void SparseMatrix_WriteToFile(SparseMatrix self, char * fileName)
{
  FILE *fout;

  fout = fopen(fileName, "w");

  SparseMatrix_Print(self, fout);

  fclose(fout);
}

//===============================================
void SparseMatrix_Convert(SparseMatrix * self, FullMatrix full)
{
  double element;
  int nbElement  = FullMatrix_CountNonZeroElements(full);
  SparseMatrix_InitEmpty(self);
  SparseMatrix_Alloc(self, full.rows, full.columns, nbElement);

  
  int length = 0;
  for (int i = 0; i < full.rows; i++) {
    for (int j = 0; j < full.columns; j++) {
      element = FullMatrix_GetElement(full, i, j);
      if (element != 0) {
        self->irows[length] = i;
        self->icolumns[length] = j;
        element = full.elements[i][j];
        self->elements[length] = element;
        length++;
      }
    }
  }
}


//===============================================
void SparseMatrix_Print(SparseMatrix self, FILE *fout)
{
  fprintf(fout, "%d\n", self.rows);
  fprintf(fout, "%d\n", self.columns);
  fprintf(fout, "%d\n", self.nbElements);

  for (int i=0; i<self.nbElements; i++)
    fprintf (fout, "%d ", self.irows[i]);
  fprintf(fout, "\n");
  for (int i=0; i<self.nbElements; i++)
    fprintf (fout, "%d ", self.icolumns[i]);
  fprintf(fout, "\n");
  for (int i=0; i<self.nbElements; i++)
    fprintf (fout, "%f ", self.elements[i]);
  fprintf(fout, "\n");

}


//===============================================
void SparseMatrix_Destroy(SparseMatrix *self)
{
	free(self->irows);
  free(self->icolumns);
  free(self->elements);
}
