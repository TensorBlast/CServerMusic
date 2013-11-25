#ifndef SORTER_HEAD
#define SORTER_HEAD
int *quickSort(int *a, int nElements, int **ma);
void quick(int *a, int l, int r,int (*com)(int, int), int **m);
void swapper(int *a, int *b);
int greater(int a, int b);
#endif