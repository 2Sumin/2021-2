#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define INF_NUM 10000 //무한대

int nums[MAX_SIZE + 1][11] = { 0 }; //key to sort
int sortedIdx[MAX_SIZE + 1] = { 0 }; //각 record의 몇번째 원소를 정렬하는지
int winTree[MAX_SIZE * 2] = { 0 }; //winner tree
int sorted[MAX_SIZE * 10 + 1] = { 0 }; //sorted result

int initWinner(int cur, int k);
void adjustWinner(int min, int k);

int main(void)
{
	int seed, k;

	printf("<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>\n\n");
	printf("the number of keys ( 8, 16, or 32 as a power of 2 ) >> ");
	scanf("%d", &k);
	printf("random numbers to use as key values (1 ~ 100)\n");
	printf("seed >> ");
	scanf("%d", &seed);
	srand(seed);

	printf("initial records:\n");
	//k개 record->제일 위의 값 정하기->아래의 값은 +1씩->순차정렬
	for (int i = 1; i <= k; i++) {
		nums[i][1] = rand() % MAX_SIZE + 1;//i번째 record 제일 위의 값
		for (int j = 2; j <= 10; j++)
			nums[i][j] = nums[i][j - 1] + 1;
		printf("%d-th records:\n", i);
		for (int j = 1; j <= 10; j++)
			printf("%d ", nums[i][j]);
		nums[i][11] = INF_NUM;
		printf("\n");
	}

	for (int i = 1; i <= k; i++)
		sortedIdx[i] = 1; //처음에는 각 record의 첫번째 원소가 정렬대상
	
	printf("\ninitialization of min-winner tree\n");
	initWinner(1, k);

	printf("\ninorder traversal for min-winner tree\n");

	printf("\n\nsorting with min-winner tree...\n\n");
	for (int i = 1; i <= k * 10; i++) {
		sorted[i] = nums[winTree[1]][sortedIdx[winTree[1]]];
		//제일 작아서 빠져나온거는 정렬된 원소
		sortedIdx[winTree[1]]++; 
		//제일 작아서 빠져나온 원소가 있는 record는 그 다음 원소 빼서 비교
		adjustWinner(k - 1 + winTree[1], k);
	}

	printf("sorted result\n");
	for (int i = 1; i <= k * 10; i++) {
		printf(" %3d", sorted[i]);
		if (i % k == 0)
			printf("\n");
	}

	return 0;
}

int initWinner(int cur, int k)
{
	if (cur >= k) 
		return winTree[cur] = (cur + 1) - k;//record 번호 그대로 넣기
	int leftChild = initWinner(cur * 2, k); //왼쪽 자식
	int rightChild = initWinner(cur * 2 + 1, k); //오른쪽 자식

	return winTree[cur]
		= nums[leftChild][sortedIdx[leftChild]] < nums[rightChild][sortedIdx[rightChild]] ?
		leftChild : rightChild; //둘 중 작은 값 넣기
}

void adjustWinner(int min, int k)
{
	if (min == 1)
		return;
	int parent = min / 2;
	int leftChild = winTree[parent * 2];
	int rightChild = winTree[parent * 2 + 1];

	winTree[parent]=
		nums[leftChild][sortedIdx[leftChild]]
		< nums[rightChild][sortedIdx[rightChild]] ? 
		leftChild : rightChild;
	adjustWinner(parent, k);
}