#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *quickSort(int *a, int nElements);
void quick(int *a, int l, int r);
int partition(int *, int ,int, int);
void swapper(int *a, int *b);


int* quickSort(int * array, int num)
{
	int left=0;
	quick(array,0,num-1);
	return array;
}
int partition(int * a, int left, int right, int pivotIndex)
{
	int pivotValue=a[pivotIndex];
	swapper(a+pivotIndex,a+right);
	int store=left;
	for(int i=left;i<right;i++)
	{
		if(a[i]>pivotValue)
		{
			swapper(a+i,a+store);
			store+=1;
		}
	}
	swapper(a+right,a+store);
	return store;
}
void quick(int * a, int left, int right)
{
	int p=(left+right)/2;
	int pnew;
	if(left<right)
	{
		pnew=partition(a,left,right,p);
		quick(a,left,pnew-1);
		quick(a,pnew+1,right);
	}
}
void swapper(int * a, int * b)
{
	int temp = *a;
	memcpy(a,b,sizeof(temp));
	memcpy(b,&temp,sizeof(temp));
}