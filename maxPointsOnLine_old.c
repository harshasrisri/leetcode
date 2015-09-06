#include <stdio.h>
#include <stdlib.h>
#include <uthash.h>

struct Point {int x; int y;};

#define DBL_MAX 1.7976931348623158e+308 /* max value */
#define DBL_MIN 2.2250738585072014e-308 /* min positive value */
#define max(a,b) ((a)>(b)?(a):(b))

typedef struct {double m; double c;} Line;

typedef struct {
    struct Point point;
    UT_hash_handle hh;
} pointTable;

typedef struct {
    Line line;
    pointTable *pTable;
    int count;
    UT_hash_handle hh;
} lineTable;

Line *ymxc (struct Point *a, struct Point *b) {
    Line *line = (Line *) calloc (1, sizeof(Line));
    double dx = a->x - b->x;
    double dy = a->y - b->y;
    line->m = dx ? dy / dx : DBL_MAX;
    line->c = dx ? a->y - (a->x * line->m) : a->x;
	/* printf ("%4d,%4d %4d,%4d %2.2e %2.2f\t", a->x, a->y, b->x, b->y, line->m, line->c); */
	/* printf ("%4d,%4d %4d,%4d\t", a->x, a->y, b->x, b->y); */
	return line;
}

lineTable *hashLine (lineTable **lTable, Line *line) {
    lineTable *ltentry, find;
	memset (&find, 0, sizeof(lineTable));
	find.line.m = line->m; find.line.c = line->c;
    HASH_FIND (hh, *lTable, &find.line, sizeof(Line), ltentry);
    if (!ltentry) {
        ltentry = (lineTable *) calloc (1, sizeof(lineTable));
        ltentry->line.m = line->m;
        ltentry->line.c = line->c;
        ltentry->pTable = NULL;
        HASH_ADD (hh, *lTable, line, sizeof(Line), ltentry);
    }
	return ltentry;
}

int hashPoint (pointTable **pTable, struct Point *point) {
    pointTable *ptentry, find;
	memset (&find, 0, sizeof(pointTable));
	find.point.x = point->x; find.point.y = point->y;

    HASH_FIND (hh, *pTable, &find.point, sizeof(struct Point), ptentry);
    if (ptentry) return 0;

	ptentry = (pointTable *) calloc (1, sizeof(pointTable));
	ptentry->point.x = point->x;
	ptentry->point.y = point->y;
	HASH_ADD (hh, *pTable, point, sizeof(struct Point), ptentry);
	return 1;
}

int maxPoints(struct Point* points, int pointsSize) {
    int i, j, max = 0, dups = 0, verts = 0;
    lineTable *lTable = NULL, *tmp1, *ltentry;
	Line *line;
	pointTable *pTable, *ptentry, *tmp2;
    
	if (pointsSize < 3) return pointsSize;

    for (i = 0; i < pointsSize; i++) {
        for (j = i + 1; j < pointsSize; j++) {
            if (points[i].x == points[j].x) {
				if (points[i].y == points[j].y) {
					dups++;
					continue;
				}
				else
					verts++;
			}
            line = ymxc (&points[i], &points[j]);
			ltentry = hashLine (&lTable, line);
			free(line);
			ltentry->count += hashPoint (&ltentry->pTable, &points[i]);
			ltentry->count += hashPoint (&ltentry->pTable, &points[j]);
        }
    }

    HASH_ITER (hh, lTable, ltentry, tmp1) {
        if (max < ltentry->count + dups) max = ltentry->count + dups;
		pTable = ltentry->pTable;
		HASH_ITER (hh, pTable, ptentry, tmp2) {
			HASH_DEL (pTable, ptentry);
			free (ptentry);
		}
		HASH_DEL (lTable, ltentry);
		free (ltentry);
    }
    
    return max(max,verts + dups);
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
	printf ("%d\n", maxPoints (points1, sizeof(points1)/sizeof(struct Point)));
	printf ("%d\n", maxPoints (points2, sizeof(points2)/sizeof(struct Point)));
	return 0;
}
