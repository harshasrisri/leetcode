#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* addBinary(char* a, char* b) {
    if (!a && !b) return NULL;
    if (!a) return b;
    if (!b) return a;
    
    int la = strlen(a), lb = strlen(b), lc = (la > lb) ? la : lb, i, j, k;
    int ba, bb, carry = 0;
    char *res = (char *) calloc (1, lc+2);

    res[lc + 1] = '\0';
    
    for (i = la - 1, j = lb - 1, k = lc; k > 0; k--, i--, j--) {
        ba = i >= 0 ? a[i] - '0' : 0;
        bb = j >= 0 ? b[j] - '0' : 0;
        res[k] = (ba ^ bb ^ carry) + '0';
        carry = (ba * bb) + (carry * (ba ^ bb));
    }
    res[0] = carry + '0';
    
    return carry ? res : res + 1;
}

int main (int argc, char **argv) { return printf ("%s\n%s\n%s\n", argv[1], argv[2], addBinary(argv[1], argv[2])); }
