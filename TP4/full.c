// File : full.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "full.h"

//===============================================
void FullMatrix_InitEmpty(FullMatrix *self)
{
  self->rows = 0;
  self->columns = 0;
  self->elements = NULL;
}

//===============================================
void FullMatrix_Alloc(FullMatrix *self, int rows, int columns)
{
  assert(rows > 0 && columns > 0);
  self->rows = rows;
  self->columns = columns;
  self->elements = malloc(rows * sizeof *self->elements);
  assert(self->elements != NULL);
  for (int i = 0; i < rows; i++)
  {
    self->elements[i] = malloc(columns * sizeof *self->elements[i]);
    assert(self->elements[i] != NULL);
  }
}

//===============================================
void FullMatrix_PutElement(FullMatrix *self, int row, int column, double element)
{
  assert(row >= 0 && column >= 0);
  assert(row <= self->rows && column <= self->columns);
  self->elements[row][column] = element;
}

//===============================================
double FullMatrix_GetElement(FullMatrix self, int row, int column)
{
  assert(row >= 0 && column >= 0);
  assert(row <= self.rows && column <= self.columns);
  return self.elements[row][column];
}

//===============================================
void FullMatrix_ReadFromFile(FullMatrix *self, char *fileName)
{
  FILE *fin;
  int rows, columns;
  double element;

  fin = fopen(fileName, "r");

  fscanf(fin, "%d", &rows);
  fscanf(fin, "%d", &columns);

  FullMatrix_InitEmpty(self);
  FullMatrix_Alloc(self, rows, columns);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
    {
      fscanf(fin, "%lf", &element);
      FullMatrix_PutElement(self, i, j, element);
    }

  fclose(fin);
}

//===============================================
void FullMatrix_WriteToFile(FullMatrix self, char *fileName)
{
  FILE *fout;

  fout = fopen(fileName, "w");

  FullMatrix_Print(self, fout);

  fclose(fout);
}

//===============================================
int FullMatrix_CountNonZeroElements(FullMatrix self)
{
  int count = 0;

  for (int i = 0; i < self.rows; i++)
  {
    for (int j = 0; j < self.columns; j++)
    {
      if (self.elements[i][j] != 0)
      {
        count++;
      }
    }
  }
  return count;
}

//===============================================
void FullMatrix_Convert(FullMatrix *self, SparseMatrix sparse)
{
  double element;

  FullMatrix_InitEmpty(self);
  FullMatrix_Alloc(self, sparse.rows, sparse.columns);

  // * 666IQ
  for (int i = 0; i < self->rows; i++)
  {
    for (int j = 0; j < self->columns; j++)
    {
      element = SparseMatrix_GetElement(sparse, i, j);
      FullMatrix_PutElement(self, i, j, element);
    }
  }
}

//===============================================
void FullMatrix_Print(FullMatrix self, FILE *fout)
{
  fprintf(fout, "%d\n", self.rows);
  fprintf(fout, "%d\n", self.columns);

  for (int i = 0; i < self.rows; i++)
  {
    for (int j = 0; j < self.columns; j++)
      fprintf(fout, "%lf ", self.elements[i][j]);
    fprintf(fout, "\n");
  }
}

//===============================================
void FullMatrix_Destroy(FullMatrix *self)
{
  for (int i = 0; i < self->rows; i++)
  {
    free(self->elements[i]);
  }
  free(self->elements);
}