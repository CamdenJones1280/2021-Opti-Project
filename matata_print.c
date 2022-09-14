// matata_print.c: shows results of computing A^T*A for the BASE
// and OPTM versions; useful for debugging when used with small sizes.
//
// usage: ./matata_print <SIZE>
//   <SIZE> : integer size for matrix like '3' or '7'

#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "matvec.h"

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("usage: %s <size>\n",argv[0]);
    exit(1);
  }

  printf("==== Matrix A^T*A Print ====\n");
  long size = atoi(argv[1]);
  long rows=size, cols=size;
  matrix_t mat;
  matrix_t base_ans, optm_ans;

  matrix_init(&mat,rows,cols);
  matrix_fill_sequential(mat);

  matrix_init(&base_ans,rows,cols);
  matrix_init(&optm_ans,rows,cols);

  matata_BASE(mat,base_ans);
  matata_OPTM(mat,optm_ans);


  printf("Original Matrix:\n");
  matrix_write(stdout, mat);
  printf("\n");

  printf("BASE Matrix A^T*A :\n");
  matrix_write(stdout, base_ans);
  printf("\n");

  printf("OPTM Matrix A^T*A :\n");
  matrix_write(stdout, optm_ans);
  printf("\n");

  printf("BASE/OPTM Element Comparison:\n");

  printf("[%3s][%3s]: %6s %6s\n","i","j","BASE","OPTM");
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      int base = MGET(base_ans,i,j);
      int optm = MGET(optm_ans,i,j);
      char *diff = (base != optm) ? "***" : "";
      printf("[%3d][%3d]: %6d %6d %s\n",
             i,j,base,optm,diff);
    }
  }
    
  matrix_free_data(&mat);       // clean up data
  matrix_free_data(&base_ans);
  matrix_free_data(&optm_ans);
  return 0;
}
