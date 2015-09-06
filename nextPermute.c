#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b) {
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

void nextPermutation (int* nums, int numsSize) {
	int x, y;

	/* Find the first number from the right which is smaller than it next */
	/* x such that nums[x] < nums[x+1] */
	for (x = numsSize - 2; x >= 0; x--)
		if (nums[x] < nums[x+1])
			break;

	/* Find the first number from the right which is greater than nums[x] */
	/* y such that nums[y] > nums[x] */
	if (x >= 0) {
		for (y = numsSize - 1; y >= x; y--)
			if (nums[y] > nums[x])
				break;
		/* Swap nums[x] and nums[y] */
		swap (&nums[x], &nums[y]);
	}

	/* Reverse the array from x+1 till end */
	for (x = x + 1, y = numsSize - 1; x < y; x++, y--) 
		swap (&nums[x], &nums[y]);

	return;
}

int main (int argc, char **argv) {
	int array[argc-1], i;
	for (i = 0; i < argc - 1; i++) 
		array[i] = atoi(argv[i+1]);
	nextPermutation (array, argc - 1);
	for (i = 0; i < argc - 1; i++)
		printf ("%d ", array[i]);
	printf ("\n");
	return 0;
}
