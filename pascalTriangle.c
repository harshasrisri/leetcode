/* Return an array of arrays of size *returnSize. */ 
/* The sizes of the arrays are returned as *columnSizes array. */ 
/* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free(). */ 

#include <stdio.h>
#include <stdlib.h>

int** generate(int numRows, int** columnSizes, int* returnSize) {
    int **ret = (int **) calloc (numRows, sizeof(int*)), i, j;
	int *cols = (int *) calloc (numRows, sizeof(int));
    *returnSize = 0;
    
    for (i = 0; i < numRows; i++) {
		cols[i] = i + 1;
        *returnSize += cols[i];
        ret[i] = (int *) malloc (cols[i] * sizeof (int));
        ret[i][0] = ret[i][i] = 1;
        for (j = 1; j <= i/2; j++) {
            ret[i][j] = ret[i][i-j] = ret[i-1][j-1] + ret[i-1][j];
		}
	}
 	
	*columnSizes = cols;

	for (i = 0; i < numRows; i++) {
	    printf ("%p : ", &cols[i]);
	    for (j = 0; j < cols[i]; j++) {
	        printf ("%d ", ret[i][j]);
	    }
	    printf ("\n");
	}   

    return ret;
}

int main (int argc, char **argv) {
	int **ret, *columnSizes, returnSize, i = atoi(argv[1]), j, k;

	/* for (i = 0; i <= atoi(argv[1]); i++) { */
		ret = generate(i, &columnSizes, &returnSize);
		for (j = 0; j < i; j++) {
			printf ("%p : ", &columnSizes[j]);
			for (k = 0; k < columnSizes[j]; k++)
				printf ("%d ", ret[j][k]);
			printf ("\n");
		}
		printf ("\n");
	/* } */
	return 0;
}
