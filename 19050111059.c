#include "hellomake.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int i;
int j;

int main(int argc, char *argv[]){

	  if (argc != 4) {
         printf("Usage: ./program rows cols output_filename\n\n", argv[0]);
         return 1;
     }
     
    int matrix_rows = atoi(argv[1]);
    int matrix_cols = atoi(argv[2]);
    char *output_filename = argv[3];
    
    srand(time(NULL));
    
    
    double **matrix = (double **)malloc(matrix_rows * sizeof(double *));
    for ( i = 0; i < matrix_rows; i++) {
        matrix[i] = (double *)calloc(matrix_cols, sizeof(double));
    }

    
    for ( i = 0; i < matrix_rows; i++) {
        for ( j = 0; j < matrix_cols; j++) {
            matrix[i][j] = (double)(rand() % 10000 + 1) / 100.0; 
        }
    }
    
     double *vector = (double *)malloc(matrix_cols * sizeof(double));
    for ( i = 0; i < matrix_cols; i++) {
        vector[i] = (double)(rand() % 10000 + 1) / 100.0; 
    }



    double *result = (double *)calloc(matrix_rows, sizeof(double));
    for ( i = 0; i < matrix_rows; i++) {
        for ( j = 0; j < matrix_cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }


   FILE *output_file = fopen(output_filename, "w");
     for (i = 0; i < matrix_rows; i++) {
         fprintf(output_file, "%.2f\n", result[i]);
     }
     fclose(output_file);

     for (i = 0; i < matrix_rows; i++) {
         free(matrix[i]);
     }
     free(matrix);
     free(vector);
     free(result);

     return 0;


}
