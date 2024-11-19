#include <stdio.h>
#include <stdlib.h>


// frees the memory of a double pointer (2d array or matrix)
void free_2d_array(int rows, double** matrix)
{
	for(int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

// works
// swaps two rows of a 2d array (int**)
void swap_rows(double** matrix, int row1, int row2)
{
	double* temp = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = temp;
}


// works
// finds the index of the pivot in a row (basically the first non-zero number in that row)
int get_pivot_col(int row_length, double* row)
{
	for(int col = 0; col < row_length; col++)
	{
		if(row[col] != 0) return col;
	}

	return -1;
}


// still work in progress
void back_substitution(int num_equations, double** coefficient_matrix, double* const_vector)
{
	double* variables = malloc(num_equations * sizeof(double));
	for(int row = num_equations - 1; row >= 0; row--)
	{
		int pivot_col = get_pivot_col(num_equations, coefficient_matrix[row]);
		if(pivot_col == -1)
		{
			fprintf(stderr, "\n\nCouldn't find pivot during back substitution.\n\n");
			exit(EXIT_FAILURE);
		}


	}
}


// pretty much done
void gaussian_elimination(int num_equations, double** coefficient_matrix, double* const_vector)
{
	// loop over the rows
	for(int current_equation = 0; current_equation < num_equations; current_equation++)
	{
		// find a row with a suitable pivot and swap it with the current row
		for(int row = current_equation + 1; coefficient_matrix[current_equation][current_equation] == 0 && row < num_equations; row++)
		{
			swap_rows(coefficient_matrix, current_equation, row);
		}

		// find the column where the pivot is located at (first non-zero number)
		int pivot_col = get_pivot_col(num_equations, coefficient_matrix[current_equation]);
		if(pivot_col == -1)
		{
			fprintf(stderr, "\n\nCouldn't find pivot during the creation of the upper triangular matrix.\n\n");
			exit(EXIT_FAILURE);
		}
		
		// subtract the current row from each of the rows below it
		for(int row = current_equation + 1; row < num_equations; row++)
		{
			// find factor to multiply the current row with before subtracting it from the other
			double factor = coefficient_matrix[row][pivot_col] / coefficient_matrix[current_equation][pivot_col];

			// actually perform the subtraction column by column
			for(int col = pivot_col; col < num_equations; col++)
			{
				coefficient_matrix[row][col] -= factor * coefficient_matrix[current_equation][col];
			}

			// also subtract from the right-hand side
			const_vector[row] -= factor * const_vector[current_equation]
		}
	}
}


// puts everything together
void solve_linear_system(int num_equations, double** coefficient_matrix, double* const_vector)
{
	gaussian_elimination(num_equations, coefficient_matrix, const_vector);
	back_substitution(num_equations, coefficient_matrix, const_vector);
}

int main()
{
	/*
	char buffer[256];
	printf(
		"The system of equations has to be linear AND square\n\n"
		"Input the number of equations/variables the system has: "
	);

	int num_equations;
	if(fgets(buffer, sizeof(buffer), stdin))
	{
		num_equations = strtol(buffer, NULL, 10);
	}

	int* coefficient_matrix[num_equations];
	for(int i = 0; i < num_equations; i++) coefficient_matrix[i] = calloc(num_equations, sizeof(int));
	*/

	int num_equations = 5;

	double** coefficient_matrix = malloc(num_equations * sizeof(double*));
	for(int i = 0; i < num_equations; i++)
	{
		coefficient_matrix[i] = malloc(num_equations * sizeof(double));
	}

	double temp_matrix[] = 
	{
		5, 4, 3, 2, 1,
		0, 0, 2, 3, 4,
		0, 1, 4, 5, 9,
		10,8, 6, 6, 9,
		0, 1, 4, 5, 8
	};

	double* const_vector;
	for(int i = 0; i < num_equations; i++) const_vector[i] = 2*i + 1;

	for(int i = 0; i < num_equations; i++)
	{
		for(int j = 0; j < num_equations; j++)
		{
			coefficient_matrix[i][j] = temp_matrix[i * num_equations + j];
			printf("%lf ", coefficient_matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	gaussian_elimination(num_equations, coefficient_matrix);
	for(int i = 0; i < num_equations; i++) 
	{
		for(int j = 0; j < num_equations; j++) printf("%lf ", coefficient_matrix[i][j]);
		printf("\n");
	}

	free_2d_array(num_equations, coefficient_matrix);
	

	return 0;
}

