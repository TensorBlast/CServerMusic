#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *quickSort(int *a, int nElements, int **ma);
void quick(int *a, int l, int r,int (*com)(int, int), int **m);
void swapper(int *a, int *b);
int greater(int a, int b)
{
	return a-b;
}

int * quickSort(int * array, int num, int **ma)
{
	int left=0;
	int right=num;
	for(int i=0;i<num;i++)
	{
		*ma[i]=i;
	}
	quick(array, left, right, &greater, ma);
	return *ma;
}
void quick(int * a, int left, int right, int (*cmp)(int, int), int **m)
{
	int l=left;
	int r=right;
	int p=(left+right)/2;
	while(l<=r)
	{
		if(cmp(a+l,a+p)<0)
		{
			l++;
		}
		if(cmp(a+r,a+p)>0)
		{
			r--;
		}
		if(l <= r)
		{
			swapper(a+l,a+r);
			int t=*m[l];
			*m[l]=*m[r];
			*m[r]=t;
			l++;
			r--;
		}
	}
	if(left<r)
	{
		quick(a,left,r,cmp,m);
	}
	if(l<right)
	{
		quick(a,l,right,cmp,m);
	}
}
void swapper(int * a, int * b)
{
	int temp=*a;
	memcpy(a,b,sizeof(temp));
	memcpy(b,&temp,sizeof(temp));
}