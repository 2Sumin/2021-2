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

	//printf("동치관계의 수: ");
	scanf("%d", &number); //동치관계 쌍의 수

	/*Phase 1: Input the equivalence pairs: */

	for (int k = 0; k < number; k++) {
		//printf("Enter a pair of numbers (-1 -1 to quit): ");
		scanf("%d%d", &i, &j);
		//(i,j)->seq[i] (배열) 바로 밑에(노드 중 제일 위에)
		//데이터로 j를 넣은 노드 연결
		MALLOC(x, sizeof(*x));
		x->data = j; //x 노드 data에 j 입력
		x->link = seq[i]; 
		//원래 연결된 노드가 있었다면 그걸 x아래에 붙이기
		//seq[]는 nodePointer 배열이니까 노드의 주소값 저장돼있음
		//header node느낌
		seq[i] = x; //원래있던 노드와 새로 들어온 x를 합친 연결리스트를
		//seq[i]에 붙이기 (x가 제일 위 노드)
		//(j,i)
		MALLOC(x, sizeof(*x));
		x->data = i; x->link = seq[j]; seq[j] = x;
	}

	/*Phase 2: Output the equivalence classes */
	for (i = 0; i < n; i++) {
		++findex;
		int index = 0;
		for (int k = 0; k < MAX_SIZE; k++)
			arr[findex][k] = -1; //배열 초기화
		if (out[i] == FALSE) { //아직 seq[i]가 확인되지 않은 경우
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
