#include<stdio.h>
#include<stdlib.h>
#define INT_MAX ((unsigned int)(1 << 31) - 1)
int reverse(int x) {
    long long res = 0, sign = 1, num = x;
    if (num < 0) {sign = -1; num = -num;}
    while (num) {
        res *= 10;
		if (res > INT_MAX) return 0;
        res += (num % 10);
        num /= 10;
    }
    return res * sign;
}
int main (int argc, char **argv) {
	return printf ("%d\n", reverse(atoi(argv[1])));
}
