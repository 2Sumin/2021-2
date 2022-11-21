#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define INF_NUM 10000

int nums[MAX_SIZE + 1] = { 0 }; //key to sort
int winTree[MAX_SIZE * 2] = { 0 }; //winner tree
int sorted[MAX_SIZE * 10 + 1] = { 0 }; //sorted result

int initWinner(int cur, int k);
void adjustWinner(int min, int k);
void inorder(int root, int k);

int main(void)
{
	int seed,k;

	printf("<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>\n\n");
	printf("the number of keys ( 8, 16, or 32 as a power of 2 ) >> ");
	scanf("%d", &k);
	
	printf("random numbers to use as key values (1~100)\n");
	printf("seed >> ");
	scanf("%d", &seed);
	srand(seed);

	for (int i = 1; i <= k; i++) { //k�� record ����
		nums[i] = rand() % MAX_SIZE + 1;
		printf(" %3d ", nums[i]);
	}
	nums[k + 1] = INF_NUM;

	printf("\n\ninitialization of min-winner tree\n");
	initWinner(1, k);

	printf("\ninorder traversal for min-winner tree\n");
	inorder(1, k);

	printf("\n\nsorting with min-winner tree...\n\n");
	for (int i = 1; i <= k; i++) {
		sorted[i] = nums[winTree[1]];
		//���� ���� ��=winTree[1]�ε����� nums �迭 ���� ��
		//->���ĵ� �迭�� �ֱ�(sorted)
		nums[winTree[1]] = INF_NUM; //�̹� ���� ���ڿ� ���Ѵ� �ֱ�
		adjustWinner(k - 1 + winTree[1], k);
		//���� �ʿ���� ���� �״�� �ΰ�
		//�ö� �� ������ ���ؾ��ϴ� ������ ����
	}	
	
	printf("sorted result\n");
	for (int i = 1; i <=k; i++)
		printf(" %3d", sorted[i]);

	return 0;
}

int initWinner(int cur, int k)
{
	if (cur >= k) return winTree[cur] = (cur + 1) - k;
	//winTree �޺κп��� Ű�� ����ŭ ������ nums�� �ε���
	//�״�� ����ֱ�
	int leftChild = initWinner(cur * 2, k); //cur�� �����ڽ� 
	int rightChild = initWinner(cur * 2 + 1, k); //������ �ڽ�

	return winTree[cur]
		= nums[leftChild] < nums[rightChild] ? leftChild : rightChild;
//���� ������ �� �� ���� �ڽ��� �ε��� �θ��忡 �ֱ�
}

void adjustWinner(int min, int k)
{
	if (min == 1) return; //�� ���ĵ����� 
	int parent = min / 2;
	int leftChild = winTree[parent * 2];
	int rightChild = winTree[parent * 2 + 1];

	winTree[parent] =
		nums[leftChild] < nums[rightChild] ?
		leftChild : rightChild; //�� ���� �ε��� �θ��忡 �ֱ�
	adjustWinner(parent, k);
}

void inorder(int root, int k)
{
	if (root > 0 && root < 2 * k) {
		inorder(root * 2, k);
		printf(" %3d", nums[winTree[root]]);
		inorder(root * 2 + 1, k);
	}
}