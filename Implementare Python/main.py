import os
import random
import time


# Generate data for the test cases in the input file
def generate_data():
    # Open the input file
    file_path = "data/input.txt"
    try:
        with open(file_path, "w") as file:
            # Get the number of test cases from the user
            test_cases = int(input("Enter the number of test cases: "))
            print()  # Add an empty line after the prompt
            file.write(f"{test_cases}\n")

            # Generate data for each test case
            for _ in range(test_cases):
                number_of_lobsters = random.randint(10, 1000)

                file.write(f"{random.randint(10, 100)}\n")  # Net capacity
                file.write(f"{number_of_lobsters}\n")  # Number of lobsters

                for i in range(number_of_lobsters):
                    file.write(f"Homarul {i + 1}\n")  # Lobster name
                    file.write(f"{random.randint(5, 50)}\n")  # Lobster dimension
                    file.write(f"{random.randint(5, 50)}\n")  # Lobster value

    except IOError:
        print("Error opening file")


# Read the input data from file
def read_data(file):
    net_capacity = int(file.readline().strip())
    number_of_lobsters = int(file.readline().strip())

    lobsters_name = [""]
    lobsters_dimension = [0]
    lobsters_value = [0]

    for i in range(number_of_lobsters):
        lobsters_name.append(file.readline().strip())
        lobsters_dimension.append(int(file.readline().strip()))
        lobsters_value.append(int(file.readline().strip()))

    return (
        net_capacity,
        number_of_lobsters,
        lobsters_dimension,
        lobsters_value,
        lobsters_name,
    )


# Allocate matrix_data
def matrix_data_allocation(number_of_lobsters, net_capacity):
    matrix_data = []

    for i in range(number_of_lobsters + 1):
        matrix_data.append([0] * (net_capacity + 1))

    return matrix_data


# Function to return the maximum value that can be obtained in the net
def max_value_in_net(
    number_of_lobsters, net_capacity, lobsters_dimension, lobsters_value, matrix_data
):
    # Loop through each lobster and each capacity
    for lobster_num in range(number_of_lobsters + 1):
        for capacity in range(net_capacity + 1):
            # If no lobsters or no capacity, set the value to 0
            if lobster_num == 0 or capacity == 0:
                matrix_data[lobster_num][capacity] = 0
            # If the current lobster fits in the net's capacity,
            # calculate the maximum value considering whether to include the lobster or not
            elif lobsters_dimension[lobster_num] <= capacity:
                matrix_data[lobster_num][capacity] = max(
                    lobsters_value[lobster_num]
                    + matrix_data[lobster_num - 1][
                        capacity - lobsters_dimension[lobster_num]
                    ],
                    matrix_data[lobster_num - 1][capacity],
                )
            # If the current lobster doesn't fit in the net's capacity,
            # the maximum value remains the same as the previous lobster at the same capacity
            else:
                matrix_data[lobster_num][capacity] = matrix_data[lobster_num - 1][
                    capacity
                ]

    # Return the maximum value obtained
    return matrix_data[number_of_lobsters][net_capacity]


# Function to print the lobsters in the net
def lobsters_in_net(
    number_of_lobsters,
    net_capacity,
    lobsters_dimension,
    lobsters_value,
    lobsters_name,
    matrix_data,
):
    i = number_of_lobsters
    j = net_capacity
    quantity = 0

    print("Lobsters in the net:")

    # Iterate over the matrix_data to identify lobsters included in the net
    while i > 0 and j > 0:
        # If the current lobster is included in the net
        if matrix_data[i][j] != matrix_data[i - 1][j]:
            # Print the lobster and update the capacity
            print(
                f"{lobsters_name[i]}: {lobsters_dimension[i]} cm {lobsters_value[i]} monede de aur"
            )
            j -= lobsters_dimension[i]
            quantity += lobsters_dimension[i]
        i -= 1

    print(f"Total quantity in the net: {quantity} cm\n")


# Main function
def main():
    # Generate data for the test cases in the input file
    generate_data()

    # Open the input file
    try:
        with open("data/input.txt", "r") as file:
            # Variables declaration
            test_cases = int(file.readline().strip())
            for i in range(1, test_cases + 1):
                print(f"Test case {i}:")

                # Read the data for each test case
                (
                    net_capacity,
                    number_of_lobsters,
                    lobsters_dimension,
                    lobsters_value,
                    lobsters_name,
                ) = read_data(file)

                print(f"Net capacity: {net_capacity} cm")
                print(f"Number of lobsters: {number_of_lobsters}")

                # Allocate the necessary memory for matrix_data
                matrix_data = matrix_data_allocation(number_of_lobsters, net_capacity)

                # Get the maximum value in the net
                max_value = max_value_in_net(
                    number_of_lobsters,
                    net_capacity,
                    lobsters_dimension,
                    lobsters_value,
                    matrix_data,
                )
                print(f"Max value in the net: {max_value} aur")

                # Print the lobsters in the net
                lobsters_in_net(
                    number_of_lobsters,
                    net_capacity,
                    lobsters_dimension,
                    lobsters_value,
                    lobsters_name,
                    matrix_data,
                )

    except IOError:
        print("Error opening file")


# Call the main function
if __name__ == "__main__":
    main()
