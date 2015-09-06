#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int natoi (char *s, int n) {
    int res = 0, i = 0;
    for (i = 0; i < n; i++) {
        res *= 10;
        res += s[i] - '0';
    }
	/* printf ("%d ", res); */
    return res;
}

#define GROW_SIZE 10

char **stringListAppend (char **list, char *str, int *size) {
	if (!(*size % GROW_SIZE)) {
		int newsize = *size + GROW_SIZE;
		list = (char **) realloc (list, sizeof(char *) * newsize);
	}
	list[*size] = strdup (str);
	(*size)++;
	return list;
}

char **restoreIpAddresses (char *s, int *returnSize) {
	int i, j, k, l, len = strlen(s), a, b, c, d;
	char buf[20], **ipList = NULL;

	*returnSize = 0;

	for (i = 1; i <= 3; i++) {
		if (i > len) break;
		a = natoi(s, i);
		if (a > 255) break;
		for (j = 1; j <= 3; j++) {
			if (i+j > len) break;
			b = natoi(s + i, j);
			if (b > 255) break;
			for (k = 1; k <= 3; k++) {
				if (i+j+k > len) break;
				c = natoi(s + i + j, k);
				if (c > 255) break;
				for (l = 1; l <= 3; l++) {
					if (i+j+k+l < len) continue;
					if (i+j+k+l > len) break;
					d = natoi(s + i + j + k, l);
					if (d > 255) break;
					if (len + 3 == sprintf (buf, "%d.%d.%d.%d", a, b, c, d))
						ipList = stringListAppend (ipList, buf, returnSize);
				}
			}
		}
	}
	return ipList;
}

int main (int argc, char **argv) {
	int i, size = 0; char **wordlist = restoreIpAddresses (argv[1], &size);
	for (i = 0; i < size; i++) {
		printf ("%s\n", wordlist[i]);
		free (wordlist[i]);
	}
	free (wordlist);
	return 0;
}
