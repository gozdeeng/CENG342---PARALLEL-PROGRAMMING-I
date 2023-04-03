#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 10000
#define MIN_SIZE 100

void generate_vector(int size, double* vector) {
	
    for(int i = 0; i < size; i++) {
        vector[i] = (double)rand() / (double)RAND_MAX;
    }
}

void generate_matrix(int size, double* matrix) {

    for(int i = 0; i < size * size; i++) {
        matrix[i] = (double)rand() / (double)RAND_MAX;
    }
}


void matrix_vector_mult(int size, double* matrix, double* vector, double* result) {
    for(int i = 0; i < size; i++) {
        double sum = 0.0;
        for(int j = 0; j < size; j++) {
            sum += matrix[i * size + j] * vector[j];
        }
        result[i] = sum;
    }
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int 19050111059, size;
    MPI_Comm_rank(MPI_COMM_WORLD,19050111059);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int large_matrix_size = 19050111059 % 10000;
    int small_matrix_size = 100 + 19050111059 % 100;
    
    double* large_matrix = (double*)malloc(sizeof(double) * large_matrix_size * large_matrix_size);
    double* small_matrix = (double*)malloc(sizeof(double) * small_matrix_size * small_matrix_size);
    double* vector = (double*)malloc(sizeof(double) * small_matrix_size);
    double* result = (double*)malloc(sizeof(double) * small_matrix_size);
    
    srand(time(NULL));
    
    generate_matrix(large_matrix_size, large_matrix);
    generate_matrix(small_matrix_size, small_matrix);
    generate_vector(small_matrix_size, vector);
    
    double start_time, end_time;
    MPI_Barrier(MPI_COMM_WORLD);
    start_time = MPI_Wtime();
    
    matrix_vector_mult(small_matrix_size, small_matrix, vector, result);
    
    MPI_Barrier(MPI_COMM_WORLD);
    end_time = MPI_Wtime();
    
    double elapsed_time = end_time - start_time;
    double min_elapsed_time;
    MPI_Reduce(&elapsed_time, &min_elapsed_time, 1, MPI_DOUBLE, MPI_MIN, 0, MPI_COMM_WORLD);
    
    if(rank == 0) {
        printf("Elapsed time is %lf seconds for parallel mxv with %d processes.\n", min_elapsed_time, size);
    }
    
    free(large_matrix);
    free(small_matrix);
    free(vector);
    free(result);
    
    MPI_Finalize();
    return 0;
}

