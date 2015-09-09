/*
Given an array of integers, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2. Please note that your returned answers (both index1 and index2) are not zero-based.

You may assume that each input would have exactly one solution.

Input: numbers={2, 7, 11, 15}, target=9
Output: index1=1, index2=2 

input passed via command line where target is the last arg

./twosum 2 7 11 15 9
1 2
*/

#include <stdio.h>
#include <uthash.h>
#include <stdlib.h>

struct twosum {
	int num;
	int index;
	UT_hash_handle hh;
};

int *twoSum (int *nums, int numsize, int target) {
	int i, diff;
	int *result = (int *)calloc(2, sizeof(int));
	struct twosum *ts = NULL, *temp = NULL, *iter = NULL;

	for (i = 0; i < numsize; i++) {
		diff = target - nums[i];
		HASH_FIND_INT (ts, &diff, temp);

		if (temp) {
			result[0] = temp->index + 1;
			result[1] = i + 1;
			break;
		} else {
			temp = (struct twosum *) calloc (1, sizeof(struct twosum));
			temp->num = nums[i];
			temp->index = i;
			HASH_ADD_INT (ts, num, temp);
		}
	}

	HASH_ITER (hh, ts, iter, temp) {
		HASH_DEL (ts, iter);
		free (iter);
	}

	return result;
}

int main (int argc, char **argv) {
	int size = argc - 2, i;
	int *result, *arr = (int *) calloc (size, sizeof(int));

	for (i = 0; i < size; i++)
		arr[i] = atoi (argv[i + 1]);

	result = twoSum (arr, size, atoi (argv[argc - 1]));

	printf ("%d %d\n", result[0], result[1]);
	free (result);
	free (arr);

	return 0;
}
