#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int key;
}element;

element a[MAX_SIZE];
int link[MAX_SIZE] ;

int listMerge(element a[], int link[], int start1, int start2);
int rmergeSort(element a[], int link[], int left, int right);

int main(void)
{
	int num = 0;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &num);

	printf("<<<<<<<<<Input List>>>>>>>>>>\n");	
	for (int i=1;i<=num;i++) {
		fscanf(fp, "%d", &a[i].key);
		printf("%d ", a[i].key);
	}
	fclose(fp);

	printf("\n\n<<<<<<excuting recursive merge sort>>>>>>\n");
	rmergeSort(a, link, 1, num);

	printf("\n<<<<<<<<<<<Sorted List>>>>>>>>>>>>\n");
	int j = link[0];
	for (j = link[0]; link[j]; j = link[j]) {
		printf("%d ", a[j].key);
	}
	printf("%d\n", a[j].key);
	return 0;
}

int listMerge(element a[], int link[], int start1, int start2)
{
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;)
		if (a[last1].key <= a[last2].key) {
			link[lastResult] = last1;
			lastResult = last1; last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2; last2 = link[last2];
		}
	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;
	return link[0];
}

int rmergeSort(element a[], int link[], int left, int right)
{
	printf("left: %-2d, right: %-2d\n", left, right);
	int mid;
	if (left >= right) return left;
	mid = (left + right) / 2;
	return listMerge(a, link,
		rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}