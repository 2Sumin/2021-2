#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (x))

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int key;
}element;

FILE* fp;
int list[MAX_ELEMENTS];

void heapSort(element a[], int n);
void adjust(element a[], int root, int n);

int main()
{
	element data[MAX_ELEMENTS];
	int num;

	fp = fopen("input.txt", "r");

	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	fscanf(fp, "%d", &num);
	for (int i = 1; !feof(fp); i++) {
		fscanf(fp, "%d", &data[i].key);
		printf("%d ", data[i].key);
	}
	printf("\n\n");
	fclose(fp);

	printf("<<<<<<<<<<<<< executing heap sort >>>>>>>>>>>>>\n");
	heapSort(data, num);

	fp = fopen("output.txt", "w");
	printf("<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>\n");
	for (int i = 0; i < num; i++) {
		printf("%d ", list[i]);
		fprintf(fp, "%d ", list[i]);
	}
	fclose(fp);
	printf("\n");

	return 0;
}

void heapSort(element a[], int n)
{
	int i, j;
	element temp;

	for (i = n / 2; i > 0; i--)
		adjust(a, i, n);

	printf("after initialization of max heap...\n");
	for (i = 1; i <= n; i++)
		printf("%2d ", a[i].key);
	printf("\n\n");
	
	for (i = n - 1, j = n - 1; i > 0; i--, j--) {
		printf("step %2d : ", n - i);
		list[j] = a[1].key;
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);
		for (int k = 1; k <= i; k++)
			printf("%2d ", a[k].key);
		for (int l = i ; l < n; l++)
			printf("%2d ", list[l]);
		printf("\n");
	}
	printf("\n");
	list[j] = a[1].key;
}

void adjust(element a[], int root, int n)
{
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && (a[child].key < a[child + 1].key))
			child++;
		if (rootkey > a[child].key)
			break;
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}