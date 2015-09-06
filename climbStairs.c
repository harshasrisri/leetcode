#include<stdio.h>
#include<stdlib.h>

int top, ret, *store = NULL;

int climbStairs(int n) {
    if (!store) {
		top = n;
        store = (int *) calloc (n + 1, sizeof(int));
        if (n >= 1) store[1] = 1;
        if (n >= 2) store[2] = 2;
    }
    if (store[n]) return store[n];
    ret = store[n] = climbStairs(n-1) + climbStairs(n-2);
	if (n == top) free(store);
	return ret;
}

int main (int argc, char **argv) { return printf ("%d\n", climbStairs(atoi(argv[1]))); }
