#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (temp))

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int key;
}element;

void quickSort(element a[], int left, int right);
int cnt, num;

int main(void)
{
	element* tmp;
	FILE* fp1, * fp2;

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	fscanf(fp1, "%d ", &num);
	fprintf(fp2, "%d\n", num);

	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	MALLOC(tmp, num * sizeof(*tmp));
	for (int i = 0; i < num; i++) {
		fscanf(fp1, "%d", &tmp[i].key);
		printf("%3d", tmp[i].key);
	}

	printf("\n\nexecution of quick sort ...\n");
	quickSort(tmp, 0, num - 1);

	printf("calls of quick sort : %d\n", cnt);

	printf("\n<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
	for (int i = 0; i < num; i++) {
		printf("%2d ", tmp[i].key);
		fprintf(fp2, "%d ", tmp[i].key);
	}
	printf("\n");

	fclose(fp1);
	fclose(fp2);

	return 0;
}

void quickSort(element a[], int left, int right)
{
	int pivot, i, j;
	element temp;
	cnt++;
	for (int k = 0; k < num; k++)
		printf("%2d ", a[k].key);
	printf("\n");

	if (left < right) {
		i = left; j = right + 1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key < pivot); 
			//pivot���� ū a[i]�� ã�������� ���������� �ö󰡱�
			//a[i].key>pivot �̸� ����
			do j--; while (a[j].key > pivot);
			//pivot���� ���� a[j]�� ã�������� �������� ��������
			//a[j].key<pivot �̸� ����
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j); 
		SWAP(a[left], a[j], temp); //pivot�� j �ٲٱ�
		//j�� �������� ���ʿ� �ִ°�, �����ʿ� �ִ°� quickSort
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

