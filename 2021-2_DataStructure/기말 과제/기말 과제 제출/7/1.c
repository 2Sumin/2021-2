#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100
#define logB(x,base) log(x)/log(base)

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int key;
}element;

void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);

int main(void)
{
	element data[MAX_SIZE];
	int num;
	FILE* f=fopen("input.txt", "r");

	printf("<<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>>>\n");
	fscanf(f, "%d", &num); //�Է�Ű�� ��
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d", &data[i].key);
		printf("%3d", data[i].key);
	}
	fclose(f);

	printf("\n\n<<<<<<<<<< executing iterative merge sort >>>>>>>>>>\n");
	mergeSort(data, num);

	printf("<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>\n");
	for (int i = 1; i <= num; i++)
		printf("%3d", data[i].key);
	printf("\n");

	return 0;
}

void merge(element initList[], element mergedList[], int i, int m, int n)
{
	//i���� �����ϴ� ���ĵ� �κ����հ� m+1���� �����ϴ� ���ĵ� �κ������� 
	// �����ؼ� �����ͺ��� mergedList�� �ֱ�
	//�κ����� �� �����̸� merge�ؼ� ����
	//initList[i:m]+[m+1:n]
	int j, k, t;
	j = m + 1;
	k = i; //mergedList index i���� ����

	while (i <= m && j <= n) { //�ϳ��� ������ ���� ����
		//���� �κ����հ� ���� �κ�����. ������ �κ����� ������ �̵�
		//i�� j �� ���� �ź��� mergedList�� �ֱ�
		if (initList[i].key <= initList[j].key)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	//���� ������ ����
	//�պκа� �޺κ��� ����Ʈ �� ���� �� append
	if (i > m)  //�պκ��� ���� ����->�޺κ� �״�� ���̱�
		for (t = j; t <= n; t++)
			mergedList[k++] = initList[t];

	else //�޺κ��� ���� ����->�պκ� �״�� ���̱�
		for (t = i; t <= m; t++)
			mergedList[k++] = initList[t];
	
	//mergedList[k + t - i] = initList[t]; ->����Ƽ ����
	//�պκп� �ִ� �Ŵϱ� mergedList�� �ε��� �޶���
	//���� mergedList�� �ε��� k
	//=�޺κ� ���� ����(n-m-1)+���ĵ� �պκ� ���� ����(i)
	//�պκ� ���� �ε���=t���� ����
}

void mergePass(element initList[], element mergedList[], int n, int s)
{
	int i, j;
	//initList�� 2s���� �����̷� �߶� merge ����
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) 
		//sublist 1���� ũ�Ⱑ s->2���� ��ġ�ϱ� �����Ŀ��� 2s ���ϱ�
		// 2s�� ����->merge ������ �κ��� i+2s-1 -> ���ǽĿ��� �� �κ��� n���� �۴�
		// i+2s-1<=n <=> i<=n-2s+1
	//merge(initList, mergedList, ����, ù segment ��, �ι�° segment ��)
		merge(initList, mergedList, i,    i + s - 1,     i + 2 * s - 1);

	//2s���� ������ ���� merge �ϰ� ���� ���� �κ� ó��
	//
	// ���� �κ��� s�� ���� �� ���� ��
	//���� �κ� �� �պκ��� sũ��� �ڸ��� �޺κ��� �ٸ� ũ���� ��
	//���� �κ� ù �ε����� i�� �ΰ� initList ��(n)���� merge
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	//���� �κ��� s���� ���� ��
	//�̹� ���ĵ� ���´ϱ� ���� �պ��� �ʿ���� �״�� mergedList�� ����(����)
	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];

	printf("segment size :%3d\n", s);

	int num = logB(s,2); //s�� 2�� �� ��������->¦�� �������̸� a,extra ����
	if (num % 2 ==0) {
		//merge ��
		printf("\t   %s :", "a");
		for (int h = 1; h <= n; h++)
			printf("%3d", initList[h].key);
		printf("\n");
		//merge ��
		printf("\t%s:", "extra");
		for (int h = 1; h <= n; h++)
			printf("%3d", mergedList[h].key);
		printf("\n\n");
	}
	else {
		//merge ��
		printf("\t%s:", "extra");
		for (int h = 1; h <= n; h++)
			printf("%3d", initList[h].key);
		printf("\n");
		//merge ��
		printf("\t   %s :", "a");
		for (int h = 1; h <= n; h++)
			printf("%3d", mergedList[h].key);
		printf("\n\n");
	}
}

void mergeSort(element a[], int n)
{
	int s = 1; //current segment size
	element extra[MAX_SIZE];

	while (s < n) { //�κ������� ��ü ���� ������ ū ���� ����. �������� ����
//mergePass( initList, mergedList, int n, int s)
		//a(��ü ������)�� extra��� sublist�� �����ؼ� ����
		//->extra �迭 ���� �����ʹ� 2s���� ��� ��� ���ĵ� ����
		//printf("mergePass(a,extra)");
		mergePass(a, extra, n, s);
		s *= 2;
		//���ĵ� extra�� �̹����� a ����
		//s�� ������ ���ĵǾ��ִ� extra�� 2s���� ���� ���� �� a�� merge
		//printf("mergePass(extra,a)");
		mergePass(extra, a, n, s);
		s *= 2;
	}
}