#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define INF_NUM 10000 //���Ѵ�

int nums[MAX_SIZE + 1][11] = { 0 }; //key to sort
int sortedIdx[MAX_SIZE + 1] = { 0 }; //�� record�� ���° ���Ҹ� �����ϴ���
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
	//k�� record->���� ���� �� ���ϱ�->�Ʒ��� ���� +1��->��������
	for (int i = 1; i <= k; i++) {
		nums[i][1] = rand() % MAX_SIZE + 1;//i��° record ���� ���� ��
		for (int j = 2; j <= 10; j++)
			nums[i][j] = nums[i][j - 1] + 1;
		printf("%d-th records:\n", i);
		for (int j = 1; j <= 10; j++)
			printf("%d ", nums[i][j]);
		nums[i][11] = INF_NUM;
		printf("\n");
	}

	for (int i = 1; i <= k; i++)
		sortedIdx[i] = 1; //ó������ �� record�� ù��° ���Ұ� ���Ĵ��
	
	printf("\ninitialization of min-winner tree\n");
	initWinner(1, k);

	printf("\ninorder traversal for min-winner tree\n");

	printf("\n\nsorting with min-winner tree...\n\n");
	for (int i = 1; i <= k * 10; i++) {
		sorted[i] = nums[winTree[1]][sortedIdx[winTree[1]]];
		//���� �۾Ƽ� �������°Ŵ� ���ĵ� ����
		sortedIdx[winTree[1]]++; 
		//���� �۾Ƽ� �������� ���Ұ� �ִ� record�� �� ���� ���� ���� ��
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
		return winTree[cur] = (cur + 1) - k;//record ��ȣ �״�� �ֱ�
	int leftChild = initWinner(cur * 2, k); //���� �ڽ�
	int rightChild = initWinner(cur * 2 + 1, k); //������ �ڽ�

	return winTree[cur]
		= nums[leftChild][sortedIdx[leftChild]] < nums[rightChild][sortedIdx[rightChild]] ?
		leftChild : rightChild; //�� �� ���� �� �ֱ�
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