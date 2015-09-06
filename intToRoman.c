#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *stringOf (int n) {
    switch (n) {
        case 1 : return "I";
        case 2 : return "II";
        case 3 : return "III";
        case 4 : return "IV";
        case 5 : return "V";
        case 9 : return "IX";
        case 10 : return "X";
        case 20 : return "XX";
        case 30 : return "XXX";
        case 40 : return "XL";
        case 50 : return "L";
        case 90 : return "XC";
        case 100 : return "C";
        case 200 : return "CC";
        case 300 : return "CCC";
        case 400 : return "CD";
        case 500 : return "D";
        case 900 : return "CM";
        case 1000 : return "M";
        case 2000 : return "MM";
        case 3000 : return "MMM";
		default : return "";
    }
}

char* intToRoman(int num) {
    char res[20] = "";
    unsigned int vals[] = {3000,2000,1000,900,500,400,300,200,100,90,50,40,30,20,10,9,5,4,3,2,1}, i;
    
    for (i = 0; i < sizeof(vals); i++) {
        if (num >= vals[i]) {
            strcat (res, stringOf(vals[i]));
            num -= vals[i];
        }
    }
    return strdup(res);
}

int main (int argc, char **argv) { return printf ("%s\n", intToRoman(atoi(argv[1]))); }
