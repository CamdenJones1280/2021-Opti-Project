#include "matvec.h"

// Baseline version from matata_base.c
int matata_BASE_NORMAL(matrix_t mat, matrix_t ans) {
  matrix_t tra;
  matrix_init(&tra, mat.rows, mat.cols);

  for(int i=0; i<mat.rows; i++){                // form transpose mat
    for(int j=0; j<mat.cols; j++){
      int mij = MGET(mat, i, j);
      MSET(tra, j, i, mij);
    }
  }

  for(int i=0; i<mat.rows; i++){                // compute ans = A^T * A
    for(int j=0; j<mat.cols; j++){
      MSET(ans,i,j,0);                          // initial sum 0's
      for(int k=0; k<mat.rows; k++){            // sum over dot(row, col)
        int tik = MGET(tra, i, k);
        int mkj = MGET(mat, k, j);
        int cur = MGET(ans, i, j);
        int new = cur + tik*mkj;
        MSET(ans, i, j, new);
      }
    }
  }

  matrix_free_data(&tra);                       // de-allocate transpose mat

  return 0;                                     // return success
}

int matata_BASE(matrix_t mat, matrix_t ans){
  if(mat.rows != mat.cols ||                    // must be a square matrix for A^T*A
     mat.rows != ans.rows ||
     mat.cols != ans.cols)
  {
    printf("matata_BASE: dimension mismatch\n");
    return 1;
  }

  return matata_BASE_NORMAL(mat, ans);
}

