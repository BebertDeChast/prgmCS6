// File : sparse.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sparse.h"


//===============================================
void SparseMatrix_InitEmpty(SparseMatrix * self)
{
	// TO DO
}

//===============================================
void SparseMatrix_Alloc(SparseMatrix * self, int rows,  int columns, int nbElements)
{
	// TO DO
}

//===============================================
double SparseMatrix_GetElement(SparseMatrix self, int row, int column)
{
	// TO DO
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
  for (int i=0; i<=nbElements; i++)
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
	// TO DO
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
  for (int i=0; i<=self.nbElements; i++)
    fprintf (fout, "%d ", self.icolumns[i]);
  fprintf(fout, "\n");
  for (int i=0; i<self.nbElements; i++)
    fprintf (fout, "%f ", self.elements[i]);
  fprintf(fout, "\n");

}


//===============================================
void SparseMatrix_Destroy(SparseMatrix *self)
{
	// TO DO
}
