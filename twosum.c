int *twoSum (int *nums, int numsize, int target) {
	int sum, i, j = numsize - 1;
	int *result = (int *)malloc(2 * sizeof(int));

	while (i < j) {
		sum = nums[i] + nums[j];
		if (sum == target) {
			result[0] = i + 1;
			result[1] = j + 1;
			return result;
		}
		else if (sum < target)
			i++;
		else
			j--;
	}
}
