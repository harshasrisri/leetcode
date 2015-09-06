#include <uthash.h>
#include <stdbool.h>
#include <stdio.h>

struct hashtable {
    int key;
    int index;
    UT_hash_handle hh;
};

struct hashtable *htbl = NULL;

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    struct hashtable *hput = NULL, *hget = NULL;
    int i;
    
    for (i = 0; i < numsSize; i++) {
        HASH_FIND_INT (htbl, &nums[i], hget);
        if (hget) {
            if (i - hget->index <= k) 
                return true;
			continue;
        }
        hput = (struct hashtable *) malloc (sizeof(struct hashtable));
        hput->index = i;
        hput->key = nums[i];
        HASH_ADD_INT (htbl, key, hput);
    }
    return false;
}

int main (int argc, char **argv) {
	int arr[] = {1, 2}, k = 2;
	return printf ("%s\n", containsNearbyDuplicate (arr, 2, k) == true ? "True" : "False");
}
