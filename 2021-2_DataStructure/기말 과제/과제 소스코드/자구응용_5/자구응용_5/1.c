#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 50
#define FALSE 0
#define TRUE 1

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct node* nodePointer;
typedef struct node {
	int ver;
	nodePointer link;
}tNode;

short int visited[MAX_VERTICES]; //��������->��� 0(False)�� �ʱ�ȭ��
nodePointer graph[MAX_VERTICES];

void insert(int x, int y);
void Print(int v);
void dfs(int v);

int main(void)
{
	FILE* fp;
	int ver, edge, u, v;

	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &ver, &edge);

	//���� ���Ḯ��Ʈ�� ǥ��
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &u, &v);
		insert(u, v);
	}
	Print(ver); //�������Ḯ��Ʈ ���

	printf("<<<<<<<<<<<<<<< Depth First Search >>>>>>>>>>>>>>>\n");
	for (int i = 0; i < ver; i++) {
		printf("dfs<%d> :", i);
		dfs(i);
		//���� dfs �����ϱ� ���� ��� �ʱ�ȭ
		for (int j = 0; j < ver; j++)
			visited[j] = FALSE;
		printf("\n");
	}

	fclose(fp);
	return 0;
}

void insert(int x, int y)
{
	nodePointer tmp;
	//x->y
	MALLOC(tmp, sizeof(*tmp));
	tmp->ver = y;
	tmp->link = graph[x]; //graph[x]�� ����ִ� �Ŵ� ���� ����� �ּ�
	graph[x] = tmp;
	//y->x
	MALLOC(tmp, sizeof(*tmp));
	tmp->ver = x;
	tmp->link = graph[y];
	graph[y] = tmp;
}

void dfs(int v)
{
	nodePointer w;
	visited[v] = TRUE; //�����ϴ� v���� TRUE�� �ٲٰ� 
	printf("%5d", v); //v���� ���
	//�������Ḯ��Ʈ(adjList[])�� ������ graph[]
	//������ ���� graph[v]�� ����� ������ w�� ����ְ� 
	for (w = graph[v]; w; w = w->link) { 
		if (!visited[w->ver]) //visited[node]==0 �̸� 
			dfs(w->ver); //graph[node]�� ���� dfs ����
		//visited[node]==1 �̸� 0�� ��� ã�������� �� ���� �̵�
		//������ ������ ���µ� visited[node]==0�ΰ� ������ backtracking
	}
	//v�� ����� ��� ��� ����Ʈ
}

void Print(int v)
{
	printf("<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>>\n");
	for (int i = 0; i < v; i++) {
		printf("graph[%d] :", i);
		for (nodePointer w = graph[i]; w; w = w->link)
			printf("%5d", w->ver);
		puts("");
	}
	printf("\n");
}

