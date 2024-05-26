#include <stdio.h>
#include <stdlib.h>
#include "includes/utils.h"

int main()
{
    // Generate data for the test cases in the input file
    generate_data();

    // Open the input file
    FILE *file;
    file = fopen("data/input.txt", "r");

    // Check if the file was opened successfully
    if (file == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    // Variables declaration
    int test_cases;
    int net_capacity;
    int number_of_lobsters;
    int max_value;
    int *lobsters_dimension = NULL;
    int *lobsters_value = NULL;
    int **matrix_data = NULL;
    char **lobsters_name = NULL;

    // Read the test cases
    fscanf(file, "%d", &test_cases);
    for (int i = 1; i <= test_cases; i++)
    {
        printf("Test case %d:\n", i);

        // Read the data for each test case
        read_data(file, &net_capacity, &number_of_lobsters, &lobsters_dimension, &lobsters_value, &lobsters_name);

        printf("Net capacity: %d cm\n", net_capacity);
        printf("Number of lobsters: %d\n", number_of_lobsters);

        // Allocate the necessary memory for matrix_data
        matrix_data_allocation(number_of_lobsters, net_capacity, &matrix_data);

        // Get the maximum value in the net
        max_value = max_value_in_net(number_of_lobsters, net_capacity, lobsters_dimension, lobsters_value, matrix_data);
        printf("Max value in the net: %d aur\n", max_value);

        // Print the lobsters in the net
        lobsters_in_net(number_of_lobsters, net_capacity, lobsters_dimension, lobsters_value, lobsters_name, matrix_data);

        // Free the allocated memory
        free_memory(number_of_lobsters, lobsters_dimension, lobsters_value, matrix_data, lobsters_name);
    }

    // Close the file
    fclose(file);

    return 0;
}

