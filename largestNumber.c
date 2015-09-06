#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct trie {
	int count;
	char *value;
	struct trie **digits;
};

struct trie* createNode() {
    struct trie *node = (struct trie *) calloc (1, sizeof(struct trie));
    return node;
}

void addToTrie (struct trie *trie, char *stub, char *value) {
    if (!*stub) {
		if (!trie->count)
			trie->value = strdup(value);
		trie->count++;
        return;
    }

    if (!trie->digits) 
		trie->digits = (struct trie**) calloc (10, sizeof(struct trie *));

	trie->digits[*stub - '0'] = createNode();
    addToTrie (trie->digits[*stub - '0'], stub + 1, value);
}

void traverseTrie (struct trie *trie, char *maxval) {
	int i, j;
	for (i = 9; i >= 0; i++) {
		for (j = trie->count; j > 0; j--)
			strcat (maxval, trie->value);
		if (trie->digits[i]) traverseTrie (trie->digits[i], maxval);
	}
}

char *largestNumber (int *nums, int numsSize) {
	char buf[16];
	char maxval[1024];
	int i;

	if (!numsSize) return NULL;

	struct trie *root = createNode();
	for (i = 0; i < numsSize; i++) {
		sprintf (buf, "%d", nums[i]);
		addToTrie (root, buf, buf);
	}

	traverseTrie (root, maxval);

	return strdup(maxval);
}

int main (int argc, char **argv) {
	int nums[argc-1], i;
	for (i = 1; i < argc; i++) nums[i-1] = atoi (argv[i]);
	return printf ("%s\n", largestNumber (nums, sizeof(nums)/sizeof(int)));
}
