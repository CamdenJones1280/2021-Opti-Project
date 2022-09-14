// optimized versions of matrix A^T*A operation
#include "matvec.h"

int matata_VER1(matrix_t mat, matrix_t ans) {
  // YOUR CODE HERE
  return 0;
}

// ADDITIONAL VERSIONS HERE

int matata_OPTM(matrix_t mat, matrix_t ans) {
  if(mat.rows != mat.cols ||                    // must be a square matrix for A^T*A
     mat.rows != ans.rows ||
     mat.cols != ans.cols)
  {
    printf("matata_OPTM: dimension mismatch\n");
    return 1;
  }

  // Call to some version of optimized code
  return matata_VER1(mat, ans);
  // return matata_VER2(mat, ans);
}
