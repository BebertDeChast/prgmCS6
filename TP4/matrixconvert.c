// File : matrixconvert.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "sparse.h"
#include "full.h"

//===============================================
int main(int argc, char * argv[])
{
  FullMatrix full;
  SparseMatrix sparse;

  if ( true ){ // TO DO - test the number of arguments 
    perror("Usage: matrixconvert -f|-s source_matrix converted_matrix");
    exit(EXIT_FAILURE);
  }

  if (!strcmp("-f", argv[1])){
    // TO DO - read full matrix from file
    printf ("Full matrix: \n");
    FullMatrix_Print(full, stdout);

		// TO DO - convert the full matrix to sparse 

    printf ("\nSparse matrix: \n");
    SparseMatrix_Print(sparse,stdout);

		// TO DO - write the converted sparse matrix to file
		// TO DO - destroy both matrix
    exit(EXIT_SUCCESS);
  }

  if (!strcmp("-s", argv[1])){
    // TO DO - read sparse matrix from file
    printf ("Sparse matrix: \n");
    SparseMatrix_Print(sparse, stdout);

    // TO DO - convert the sparse matrix to full 

    printf ("\nFull matrix: \n");
    FullMatrix_Print(full, stdout);

		// TO DO - write the converted sparse matrix to file
		// TO DO - destroy both matrix
    exit(EXIT_SUCCESS);
  }

  perror("Usage: matrixconvert -f|-s source_matrix converted_matrix");
  exit(EXIT_FAILURE);
}
