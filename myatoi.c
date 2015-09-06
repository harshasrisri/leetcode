#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int myAtoi (char *s) {
	unsigned long long num = 0;
	int sign = 1;
	
	while (isspace(*s)) s++;
	if (*s == '-' || *s == '+') {
		if (*s == '-') sign = -1; 
		if (*s == '+') sign = 1; 
		s++;
	}

	for (; isdigit(*s); s++) {
		num *= 10;
		num += *s - '0';
	}

	if (*--s != num % 10 || num > INT_MAX) {
		if (sign < 0) return INT_MIN;
		return INT_MAX;
	}

	return sign * num;
}

int main (int argc, char **argv) { return printf ("%d\n", myAtoi(argv[1])); }
