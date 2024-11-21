#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


// frees the memory of a double pointer (2d array or matrix)
void free_2d_array(int rows, double** matrix)
{
	for(int i = 0; i < rows; i++)
		free(matrix[i]);

	free(matrix);
}

// works
// swaps two rows of a linear system (coefficient matrix and constants vector)
void swap_rows(double** matrix, double* vector, int row1, int row2)
{
	double* temp = matrix[row1];
	matrix[row1] = matrix[row2];
	matrix[row2] = temp;

	double temp_const = vector[row1];
	vector[row1] = vector[row2];
	vector[row2] = temp_const;
}


// works
// finds the index of the pivot in a row (basically the first non-zero number in that row)
int get_pivot_col(int row_length, double* row)
{
	for(int col = 0; col < row_length; col++)
	{
		if(fabs(row[col]) > 1e-9) return col;
	}

	return -1;
}


// still work in progress
void back_substitution(int num_equations, double **coefficient_matrix, double *const_vector, double *variables)
{
	for(int row = num_equations - 1; row >= 0; row--)
	{
		int pivot_col = get_pivot_col(num_equations, coefficient_matrix[row]);
		if(pivot_col == -1)
		{
			fprintf(stderr, "\n\nCouldn't find pivot during back substitution.\n\n");
			exit(EXIT_FAILURE);
		}

		double temp_variable = const_vector[row];
		for(int col = num_equations - 1; col >= pivot_col; col--)
		{
			if(col != pivot_col)
			{
				temp_variable -= variables[col] * coefficient_matrix[row][col];
			}
			else
			{
				variables[row] = temp_variable / coefficient_matrix[row][pivot_col];
			}
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
			swap_rows(coefficient_matrix, const_vector, current_equation, row);
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
			const_vector[row] -= factor * const_vector[current_equation];
		}
	}
}


// puts everything together
void solve_linear_system(int num_equations, double **coefficient_matrix, double *const_vector, double *variables)
{
	gaussian_elimination(num_equations, coefficient_matrix, const_vector);
	back_substitution(num_equations, coefficient_matrix, const_vector, variables);
}

void get_matrix_from_string(int num_equations, double **coefficient_matrix, char **matrix_string)
{
	char *element;
	const char delimiter[] = " ";
	for(int row = 0; row < num_equations; row++)
	{
		element = strtok(matrix_string[row], delimiter);
		if(element[0] != '\0')
			coefficient_matrix[row][0] = strtol(element, NULL, 10);

		while(element != NULL)
		{
			// add all the elements and check for overflow
			element = strtok(NULL, delimiter);
		}
	}
}

int main()
{
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
	
	printf("%d", num_equations);

	int* coefficient_matrix[num_equations];
	for(int i = 0; i < num_equations; i++) coefficient_matrix[i] = calloc(num_equations, sizeof(int));

	printf(
		"\nEnter the coefficient matrix A:\n"
	);

	

	//if(fgets(buffer))




	/*
	int num_equations = 3;
	double **coefficient_matrix = malloc(num_equations * sizeof(double*));
	for(int i = 0; i < num_equations; i++)
	{
		coefficient_matrix[i] = malloc(num_equations * sizeof(double));
	}

	double temp_matrix[] = 
	{
		3, 3, 2,
		6, 3, 4,
		8, 9, 1
	};

	double *const_vector = malloc(num_equations * sizeof(double));
	const_vector[0] = 15;
	const_vector[1] = 24;
	const_vector[2] = 29;

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

	double *variables = malloc(num_equations * sizeof(double));
	for(int i = 0; i < num_equations; i++) printf("%lf\n", const_vector[i]);
	printf("\n");
	solve_linear_system(num_equations, coefficient_matrix, const_vector, variables);

	for(int i = 0; i < num_equations; i++) 
	{
		printf("%lf ", variables[i]);
	}


	free_2d_array(num_equations, coefficient_matrix);
	free(variables);
	free(const_vector);
	*/
	

	return 0;
}

