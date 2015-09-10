#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* countAndSay(int n) {
    if (n <= 0) return NULL;

    char *s1, *s2;
	int size = 1024;
    s1 = (char *) malloc (size);
    s2 = (char *) malloc (size);
    strcpy (s1, "1");

	int i;
    
    for (i = 1; i < n; i++) {
		char *p1 = s1, *p2 = s2, *temp;
		int count = 1;
		do {
			/* if (p2 - s2 == size) { */
			/* 	size *= 2; */
			/* 	s1 = (char *) realloc (s1, size); */
			/* 	s2 = (char *) realloc (s2, size); */
			/* } */
			if (*p1 != *(p1 + 1)) {
				*p2++ = count + '0';
				*p2++ = *p1;
				count = 1;
			} else {
				count++;
			}
			p1++;
		} while (*p1);
		*p2 = '\0';
		/* printf ("%s -> %s\n", s1, s2); */
		temp = s2;
		s2 = s1;
		s1 = temp;
    }

	free (s2);
	return s1;
}

int main (int argc, char **argv) { return printf ("%s\n", countAndSay(atoi(argv[1])));}
