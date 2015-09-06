#include <stdio.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    int *res = (int *) malloc (numsSize * sizeof(int)), prod = 1, i;
    res[0] = res[numsSize - 1] = 1; *returnSize = numsSize;
    for (i = 1; i < numsSize; i++) res[i] = (prod *= nums[i - 1]);
    for (prod = 1, i = numsSize - 2; i >= 0; i--) res[i] *= (prod *= nums[i + 1]);
    return res;
}

int main (int argc, char **argv) {
	int arr[] = {5,9,2,-9,-9,-7,-8,7,-9,10}, size = 0, i;
	int *res = productExceptSelf (arr, sizeof(arr) / sizeof(int), &size);
	for (i = 0; i < size; i++) printf ("%d ", res[i]);
	printf ("\n");
	return 0;
}
