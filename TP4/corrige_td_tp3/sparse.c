// File : sparse.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sparse.h"


//===============================================
void SparseMatrix_InitEmpty(SparseMatrix * self)
{
  self->rows = 0;
  self->columns = 0;
  self->nbElements = 0;
  self->irows = NULL;
  self->icolumns = NULL;
  self->elements = NULL;
}

//===============================================
void SparseMatrix_Alloc(SparseMatrix * self, int rows,  int columns, int nbElements)
{
  assert((columns!=0) && (rows!=0) && (nbElements!=0));

  self->rows = rows;
  self->columns = columns;
  self->nbElements = nbElements;

  self->irows = malloc (nbElements * sizeof * self->irows);
  assert(self->irows != NULL);

  self->icolumns = malloc ((columns+1) * sizeof * self->icolumns);
  assert(self->icolumns != NULL);

  self->elements = malloc (nbElements * sizeof * self->elements);
  assert(self->elements != NULL);
}

//===============================================
double SparseMatrix_GetElement(SparseMatrix self, int row, int column)
{
  for (int i=self.icolumns[column]; i<self.icolumns[column+1]; i++)
    if (self.irows[i] == row)
      return self.elements[i];
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
  for (int i=0; i<=columns; i++)
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
  int nbElements = FullMatrix_CountNonZeroElements(full);
  int elementIndex = 0;
  int columnIndex = 1;
  double element;

  SparseMatrix_InitEmpty(self);
  SparseMatrix_Alloc(self, full.rows, full.columns, nbElements);

  self->icolumns[0] = 0;
  for (int i=0; i<full.rows; i++){
    for (int j=0; j<full.columns; j++){
      element = FullMatrix_GetElement(full, i, j);
      if (element != 0.0){
        self->elements[elementIndex] = element;
        self->irows[elementIndex] = j;
        elementIndex++;
      }
    }
    self->icolumns[columnIndex] = elementIndex;
    columnIndex++;
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
  for (int i=0; i<=self.columns; i++)
    fprintf (fout, "%d ", self.icolumns[i]);
  fprintf(fout, "\n");
  for (int i=0; i<self.nbElements; i++)
    fprintf (fout, "%f ", self.elements[i]);
  fprintf(fout, "\n");

}


//===============================================
void SparseMatrix_Destroy(SparseMatrix *self)
{
  self->rows = 0;
  self->columns = 0;
  self->nbElements = 0;

  free(self->irows);
  free(self->icolumns);
  free(self->elements);
}
