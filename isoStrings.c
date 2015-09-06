#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

bool isIsomorphic_slow (char *s, char *t) {
	int fill = -1, len = 0;
	char *ss, *tt, find; 
	volatile char *pos;

	if (!s && !t) return false;
	if (!*s && !*t) return true;

	for (ss = s, tt = t; *s && *t; s++, t++, len++) {
		if (*s < 0 && *t < 0) {
			if (*s != *t) return false;
			continue;
		}
		else if (*s > 0 && *t > 0) {
			for (pos = s, find = *s; (pos = strchr (pos, find)); *pos = fill);
			for (pos = t, find = *t; (pos = strchr (pos, find)); *pos = fill);
			fill--;
		}
		else return false;
	}

	return (bool) (0 == memcmp (ss, tt, len));
}

bool isIsomorphic_fast (char *s, char *t) {
	int i;
	char smap[128] = {0};
	char tmap[128] = {0};

	if (!s && !t) return false;
	if (!*s && !*t) return true;

	for (i = 0; s[i]; i++) {
		if (!smap[s[i]] && !tmap[t[i]]) {
			smap[s[i]] = t[i];
			tmap[t[i]] = s[i];
			continue;
		}
		else if (smap[s[i]] != t[i] || tmap[t[i]] != s[i]) 
			return false;
	}

	return true;
}

int main (int argc, char **argv) {
	clock_t timer = clock();
	printf ("%s : %lfs\n", (true == isIsomorphic_slow (argv[1], argv[2])) ? "True" : "False", clock() - timer);
	timer = clock();
	printf ("%s : %lfs\n", (true == isIsomorphic_fast (argv[1], argv[2])) ? "True" : "False", clock() - timer);
	return 0;
}
