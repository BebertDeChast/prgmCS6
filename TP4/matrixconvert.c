// File : matrixconvert.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "sparse.h"
#include "full.h"

//===============================================
int main(int argc, char * argv[]) {
  FullMatrix full;
  SparseMatrix sparse;

  if (argc != 4) { // TO DO - test the number of arguments 
    perror("Usage: matrixconvert -f|-s source_matrix converted_matrix\n Wrong number of argument");
    exit(EXIT_FAILURE);
  }

  if (!strcmp("-f", argv[1])) {
    FullMatrix_ReadFromFile(&full, argv[2]);
    printf ("Full matrix: \n");
    FullMatrix_Print(full, stdout);

    SparseMatrix_Convert(&sparse, full);
    printf ("\nSparse matrix: \n");
    SparseMatrix_Print(sparse,stdout);

    SparseMatrix_AddValue(&sparse, 0, 0, 0);
    printf ("\nReturn of the Sparse matrix: \n");
    SparseMatrix_Print(sparse,stdout);

    SparseMatrix_AddValue(&sparse, 0, 2, 0);
    printf ("\nReturn of the Sparse matrix: \n");
    SparseMatrix_Print(sparse,stdout);

		SparseMatrix_WriteToFile(sparse, argv[3]);

		FullMatrix_Destroy(&full);
    SparseMatrix_Destroy(&sparse);
    exit(EXIT_SUCCESS);
  }

  if (!strcmp("-s", argv[1])) {
    SparseMatrix_ReadFromFile(&sparse,argv[2]);
    printf ("Sparse matrix: \n");
    SparseMatrix_Print(sparse, stdout);

    FullMatrix_Convert(&full, sparse);

    printf ("\nFull matrix: \n");
    FullMatrix_Print(full, stdout);

		FullMatrix_WriteToFile(full,argv[3]);
		FullMatrix_Destroy(&full);
    SparseMatrix_Destroy(&sparse);
    exit(EXIT_SUCCESS);
  }

  perror("Usage: matrixconvert -f|-s source_matrix converted_matrix. Arguments not recognized.");
  exit(EXIT_FAILURE);
}
