#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int *quickSort(int *a,int *, int nElements);
void quick(int *a, int *,int l, int r);
int partition(int *,int *, int ,int, int);
void swapper(int *a, int *b);


int* quickSort(int * array,int *map, int num)
{
	quick(array,map,0,num-1);
	// for(int i=0;i<num;i++)
	// {
	// 	printf("%d\n", array[i]);
	// }
	return array;
}
int partition(int * a,int *map, int left, int right, int pivotIndex)
{
	int pivotValue=a[pivotIndex];
	swapper(a+pivotIndex,a+right);
	swapper(map+pivotIndex,map+right);
	int store=left;
	for(int i=left;i<right;i++)
	{
		if(a[i]>pivotValue)
		{
			swapper(a+i,a+store);
			swapper(map+i,map+store);
			store+=1;
		}
	}
	swapper(a+right,a+store);
	swapper(map+right,map+store);
	return store;
}
void quick(int * a,int *m, int left, int right)
{
	int p=(left+right)/2;
	int pnew;
	if(left<right)
	{
		pnew=partition(a,m,left,right,p);
		quick(a,m,left,pnew-1);
		quick(a,m,pnew+1,right);
	}
}
void swapper(int * a, int * b)
{
	int temp = *a;
	memcpy(a,b,sizeof(temp));
	memcpy(b,&temp,sizeof(temp));
}