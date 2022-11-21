#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define TRUE 1
#define FALSE 0
#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))


typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

void sort(int arr[], int n);
void printSort(int arr[], int n);

void main(void)
{
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i, j, n;
	int number = 0;
	int findex = -1;
	int arr[MAX_SIZE][MAX_SIZE];

	//printf("Enter the size (<= %d) ", MAX_SIZE);
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		/* initialize seq and out */
		out[i] = FALSE;
		seq[i] = NULL;
	}

	//printf("��ġ������ ��: ");
	scanf("%d", &number); //��ġ���� ���� ��

	/*Phase 1: Input the equivalence pairs: */

	for (int k = 0; k < number; k++) {
		//printf("Enter a pair of numbers (-1 -1 to quit): ");
		scanf("%d%d", &i, &j);
		//(i,j)->seq[i] (�迭) �ٷ� �ؿ�(��� �� ���� ����)
		//�����ͷ� j�� ���� ��� ����
		MALLOC(x, sizeof(*x));
		x->data = j; //x ��� data�� j �Է�
		x->link = seq[i]; 
		//���� ����� ��尡 �־��ٸ� �װ� x�Ʒ��� ���̱�
		//seq[]�� nodePointer �迭�̴ϱ� ����� �ּҰ� ���������
		//header node����
		seq[i] = x; //�����ִ� ���� ���� ���� x�� ��ģ ���Ḯ��Ʈ��
		//seq[i]�� ���̱� (x�� ���� �� ���)
		//(j,i)
		MALLOC(x, sizeof(*x));
		x->data = i; x->link = seq[j]; seq[j] = x;
	}

	/*Phase 2: Output the equivalence classes */
	for (i = 0; i < n; i++) {
		++findex;
		int index = 0;
		for (int k = 0; k < MAX_SIZE; k++)
			arr[findex][k] = -1; //�迭 �ʱ�ȭ
		if (out[i] == FALSE) { //���� seq[i]�� Ȯ�ε��� ���� ���
			arr[findex][index] = i;
			//printf("\nNew class: %5d", i);
			//printf("\n%2d", i);
			out[i] = TRUE;
			x = seq[i]; top = NULL;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j] == FALSE) {
						//printf("%2d", j); 
						arr[findex][++index] = j;
						out[j] = TRUE;
						y = x->link; x->link = top; top = x; x = y;
					}
					else x = x->link;

				}
				if (!top) break; //empty stack
				x = seq[top->data]; top = top->link; //pop
			}
			printSort(arr[findex], n);
		}

	}

}

void sort(int arr[], int n)
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min])
				min = j;
		SWAP(arr[i], arr[min], temp);
	}
}

void printSort(int arr[10], int n)
{
	sort(arr, n);
	for (int i = 0; i < n; i++) {
		if (arr[i] > -1)
			printf("%-2d", arr[i]);
	}
	printf("\n");
}
