#ifndef CODE_UTLIS_H
#define CODE_UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Read the input data from file
void read_data(FILE *file, int *net_capacity, int *number_of_lobsters, int **lobsters_dimension, int **lobsters_value, char ***lobsters_name);

// Allocate the necessary memory for matrix_data
int matrix_data_allocation(int number_of_lobsters, int net_capacity, int ***matrix_data);

// Return the maximum of two numbers
int max(int a, int b);

// Function to find the maximum value that can be obtained in the net
int max_value_in_net(int number_of_lobsters, int net_capacity, int *lobsters_dimension, int *lobsters_value, int **matrix_data);

// Function to print the lobsters in the net
void lobsters_in_net(int number_of_lobsters, int net_capacity, int *lobsters_dimension, int *lobsters_value, char **lobsters_name, int **matrix_data);

// Generate data for the test cases in the input file
void generate_data();

// Free the memory allocated for lobsters_dimension, lobsters_value, lobsters_name and matrix_data
void free_memory(int number_of_lobsters, int *lobsters_dimension, int *lobsters_value, int **matrix_data, char **lobsters_name);

#endif // CODE_UTLIS_H
