#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"

#define MAX_NAME_LENGTH 100 // Maximum name length for lobsters

// Read the input data from file
void read_data(FILE *file, int *net_capacity, int *number_of_lobsters, int **lobsters_dimension, int **lobsters_value, char ***lobsters_name)
{
    char temp_str[MAX_NAME_LENGTH]; // Temporary string to store the name of a lobster

    fscanf(file, "%d", net_capacity);
    fscanf(file, "%d", number_of_lobsters);

    // Allocate the necessary memory for lobsters_dimension, lobsters_value, and lobsters_name and check if they were allocated successfully
    *lobsters_name = (char **)malloc((*number_of_lobsters + 1) * sizeof(char *));
    if (*lobsters_name == NULL)
    {
        printf("Error allocating memory for lobsters_name\n");
        exit(1);
    }

    *lobsters_dimension = (int *)malloc((*number_of_lobsters + 1) * sizeof(int));
    if (*lobsters_dimension == NULL)
    {
        printf("Error allocating memory for lobsters_dimension\n");
        exit(1);
    }

    *lobsters_value = (int *)malloc((*number_of_lobsters + 1) * sizeof(int));
    if (*lobsters_value == NULL)
    {
        printf("Error allocating memory for lobsters_value\n");
        exit(1);
    }

    // Initialize the first element of lobsters_dimension, lobsters_value, and lobsters_name
    (*lobsters_name)[0] = strdup("");
    (*lobsters_dimension)[0] = 0;
    (*lobsters_value)[0] = 0;

    // Read the remaining elements of lobsters_dimension, lobsters_value, and lobsters_name
    for (int i = 1; i <= (*number_of_lobsters); i++)
    {
        fscanf(file, " %[^\n]", temp_str); // %[^\n] - read until newline
        (*lobsters_name)[i] = strdup(temp_str);

        fscanf(file, " %d", &(*lobsters_dimension)[i]);
        fscanf(file, " %d", &(*lobsters_value)[i]);
    }
}

// Allocate the necessary memory for matrix_data
int matrix_data_allocation(int number_of_lobsters, int net_capacity, int ***matrix_data)
{
    int i;

    // Allocate the necessary memory for matrix_data and check if it was allocated successfully
    *matrix_data = (int **)malloc((number_of_lobsters + 1) * sizeof(int *));
    if (*matrix_data == NULL)
    {
        printf("Error allocating memory for matrix_data\n");
        exit(1);
    }

    for (i = 0; i <= number_of_lobsters; i++)
    {
        (*matrix_data)[i] = (int *)malloc((net_capacity + 1) * sizeof(int));

        if ((*matrix_data)[i] == NULL)
        {
            printf("Error allocating memory for matrix_data\n");
            exit(1);
        }
    }
}

// Return the maximum of two numbers
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

// Function to return the maximum value that can be obtained in the net
int max_value_in_net(int number_of_lobsters, int net_capacity, int *lobsters_dimension, int *lobsters_value, int **matrix_data)
{
    int lobster_num, capacity;

    // Loop through each lobster and each capacity
    for (lobster_num = 0; lobster_num <= number_of_lobsters; lobster_num++)
    {
        for (capacity = 0; capacity <= net_capacity; capacity++)
        {
            // If no lobsters or no capacity, set the value to 0
            if (lobster_num == 0 || capacity == 0)
            {
                matrix_data[lobster_num][capacity] = 0;
            }
            // If the current lobster fits in the net's capacity,
            // calculate the maximum value considering whether to include the lobster or not
            else if (lobsters_dimension[lobster_num] <= capacity)
            {
                matrix_data[lobster_num][capacity] = max(lobsters_value[lobster_num] + matrix_data[lobster_num - 1][capacity - lobsters_dimension[lobster_num]], matrix_data[lobster_num - 1][capacity]);
            }
            // If the current lobster doesn't fit in the net's capacity,
            // the maximum value remains the same as the previous lobster at the same capacity
            else
            {
                matrix_data[lobster_num][capacity] = matrix_data[lobster_num - 1][capacity];
            }
        }
    }

    // Return the maximum value obtained
    return matrix_data[number_of_lobsters][net_capacity];
}

// Function to print the lobsters in the net
void lobsters_in_net(int number_of_lobsters, int net_capacity, int *lobsters_dimension, int *lobsters_value, char **lobsters_name, int **matrix_data)
{
    int i, j, quantity = 0;

    i = number_of_lobsters;
    j = net_capacity;

    printf("Lobsters in the net:\n");

    // Iterate over the matrix_data to identify lobsters included in the net
    while (i > 0 && j > 0)
    {
        // If the current lobster is included in the net
        if (matrix_data[i][j] != matrix_data[i - 1][j])
        {
            // Print the lobster and update the capacity
            printf("%s: %d cm %d monede de aur\n", lobsters_name[i], lobsters_dimension[i], lobsters_value[i]);
            j -= lobsters_dimension[i];
            quantity += lobsters_dimension[i];
        }

        i--;
    }

    printf("Total quantity in the net: %d cm\n\n", quantity);
}

// Generate data for the test cases in the input file
void generate_data()
{
    // Open the input file
    FILE *file;
    file = fopen("data/input.txt", "w");

    // Check if the file was opened successfully
    if (file == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int i, number_of_lobsters, test_cases;

    printf("Enter the number of test cases: ");
    scanf("%d", &test_cases);

    fprintf(file, "%d\n", test_cases);

    // Seed the random number generator based on current time
    srand((unsigned)time(NULL));

    // Generate data for each test case
    while (test_cases--)
    {
        number_of_lobsters = rand() % 10000000 + 100;

        fprintf(file, "%d\n", rand() % 1000 + 100); // Net capacity
        fprintf(file, "%d\n", number_of_lobsters);  // Number of lobsters

        for (i = 0; i < number_of_lobsters; i++)
        {
            fprintf(file, "Homarul %d\n", i + 1);     // Lobster name
            fprintf(file, "%d\n", rand() % 100 + 10); // Lobster dimension
            fprintf(file, "%d\n", rand() % 100 + 10); // Lobster value
        }
    }

    printf("\n\n");

    // Close the file
    fclose(file);
}

// Free the memory allocated for lobsters_dimension, lobsters_value, lobsters_name and matrix_data
void free_memory(int number_of_lobsters, int *lobsters_dimension, int *lobsters_value, int **matrix_data, char **lobsters_name)
{
    int i;

    for (i = 0; i <= number_of_lobsters; i++)
    {
        free(matrix_data[i]);
        free(lobsters_name[i]);
    }
    free(matrix_data);
    free(lobsters_dimension);
    free(lobsters_value);
    free(lobsters_name);
}
