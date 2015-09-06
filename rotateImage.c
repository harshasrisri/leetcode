#include <stdio.h>
#include <stdlib.h>

void arrayprint (int **arr, int rows, int cols) {
    if (rows < 1 || cols < 1) return;
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++)
			printf ("%03d ", arr[i][j]);
		printf ("\n");
	}
	printf ("\n");
}

void swap (int *a, int *b) {*a = *a ^ *b; *b = *a ^ *b; *a = *a ^ *b;}
void four_way_swap (int *p1, int *p2, int *p3, int *p4) {swap (p1, p2); swap (p3, p4); swap (p1, p3);}

void rotate(int** matrix, int matrixRowSize, int matrixColSize) {
    if (matrixRowSize <= 1 || matrixColSize <= 1) return;
    
    int i, j;
    for (i = 0; i <= matrixRowSize / 2; i++) {
        for (j = i; j <= matrixColSize - i - 2; j++) {
            four_way_swap (
                &matrix[i][j],
                &matrix[j][matrixColSize - i - 1],
                &matrix[matrixRowSize - i - 1][matrixColSize - j - 1],
                &matrix[matrixRowSize - j - 1][i]);
        }
    }
}

int main (int argc, char **argv) {
	int **arr, i, j, k, count, tests;

	if (argc > 1) tests = atoi(argv[1]);
	else tests = 10;

	arr = (int **) calloc (tests, sizeof(int*));
	for (i = 0; i < tests; i++) arr[i] = (int *) calloc (tests, sizeof(int));

	for (k = 1; k <= tests; k++) {
		for (count = 1, i = 0; i < k; i++)
			for (j = 0; j < k; j++)
				arr[i][j] = count++;
		count = 0;

		arrayprint (arr, k, k);
		rotate (arr, k, k);
		arrayprint (arr, k, k);
		printf ("\n");
	}

	return 0;
}
