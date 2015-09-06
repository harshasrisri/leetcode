#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

struct Point {int x; int y;};

#define DBL_MAX 1.7976931348623158e+308 /* max value */
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct {
    double slope;
	int count;
    UT_hash_handle hh;
} slopeTable;

void hashLine (slopeTable **sTable, double *slope) {
	slopeTable *stentry;
    HASH_FIND (hh, *sTable, slope, sizeof(*slope), stentry);
    if (!stentry) {
		stentry = (slopeTable *) calloc (1, sizeof (slopeTable));
		stentry->slope = *slope;
		stentry->count = 1;
		HASH_ADD (hh, *sTable, slope, sizeof(*slope), stentry);
	} else {
		stentry->count++;
	}
}

int maxPoints(struct Point* points, int pointsSize) {
    int i, j, max = 0, dups, verts;
	slopeTable *sTable, *stentry, *tmp;
	struct Point *a, *b;
	double slope;
    
	if (pointsSize < 3) return pointsSize;

    for (i = 0; i < pointsSize - max; i++) {
		a = &points[i];
		dups = 1;
		verts = 0;
		sTable = NULL;
        for (j = i + 1; j < pointsSize; j++) {
			b = &points[j];
            if (a->x == b->x) {
				if (a->y == b->y) dups++;
				else verts++;
			} else {
				slope = (double) (a->y - b->y) / (double ) (a->x - b->x);
				hashLine (&sTable, &slope);
			}
        }

		HASH_ITER (hh, sTable, stentry, tmp) {
			max = max(max,stentry->count + dups);
			HASH_DEL (sTable, stentry); free (stentry);
		}

		max = max(max,verts + dups);
    }
	return max;
}

int main () {
	struct Point points1[] = {
		{.x=5,.y=1},{.x=5,.y=2},{.x=5,.y=3},{.x=5,.y=4},{.x=5,.y=5},
		{.x=4,.y=1},{.x=4,.y=2},{.x=4,.y=3},{.x=4,.y=4},{.x=4,.y=5},
		{.x=3,.y=1},{.x=3,.y=2},{.x=3,.y=3},{.x=3,.y=4},{.x=3,.y=5},
		{.x=2,.y=1},{.x=2,.y=2},{.x=2,.y=3},{.x=2,.y=4},{.x=2,.y=5},{.x=2,.y=6},
		{.x=1,.y=1},{.x=1,.y=2},{.x=1,.y=3},{.x=1,.y=4},{.x=1,.y=5},{.x=1,.y=7},
		{.x=0,.y=8},{.x=-1,.y=9},
		{.x=-3,.y=-3},
		{.x=4,.y=0},{.x=4,.y=-1},{.x=4,.y=5},
	};

	struct Point points2[] = {
		{.x=-435,.y=-347}, {.x=-435,.y=-347}, {.x=609,.y=613}, {.x=-348,.y=-267},
		{.x=-174,.y=-107}, {.x=87,.y=133}, {.x=-87,.y=-27}, {.x=-609,.y=-507},
		{.x=435,.y=453}, {.x=-870,.y=-747}, {.x=-783,.y=-667}, {.x=0,.y=53},
		{.x=-174,.y=-107}, {.x=783,.y=773}, {.x=-261,.y=-187}, {.x=-609,.y=-507},
		{.x=-261,.y=-187}, {.x=-87,.y=-27}, {.x=87,.y=133}, {.x=783,.y=773},
		{.x=-783,.y=-667}, {.x=-609,.y=-507}, {.x=-435,.y=-347}, {.x=783,.y=773},
		{.x=-870,.y=-747}, {.x=87,.y=133}, {.x=87,.y=133}, {.x=870,.y=853},
		{.x=696,.y=693}, {.x=0,.y=53}, {.x=174,.y=213}, {.x=-783,.y=-667},
		{.x=-609,.y=-507}, {.x=261,.y=293}, {.x=435,.y=453}, {.x=261,.y=293},
		{.x=435,.y=453},
	};

	struct Point points3[] = {
		{2,3},{3,3},{-5,3},
	};
	printf ("%d\n", maxPoints (points1, sizeof(points1)/sizeof(struct Point)));
	printf ("%d\n", maxPoints (points2, sizeof(points2)/sizeof(struct Point)));
	printf ("%d\n", maxPoints (points3, sizeof(points3)/sizeof(struct Point)));
	return 0;
}
