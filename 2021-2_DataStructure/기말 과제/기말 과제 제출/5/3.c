#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 20
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

short int visited[MAX_VERTICES];
nodePointer adjList[MAX_VERTICES];

void insert(int x, int y);
void dfs(int v);
void Print(int v);
void connected(int num);

void main(void)
{
	int u, v, ver, edge;

	FILE* fp = fopen("input1.txt", "r"); // G1
	//FILE* fp = fopen("input.txt", "r"); // G4

	fscanf(fp, "%d %d", &ver, &edge);
	
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &u, &v);
		insert(u, v);
	}

	printf("<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>\n");
	Print(ver);
	printf("<<<<<<<<<<<<<<<<<< Connected Components >>>>>>>>>>>>>>>>>>\n");
	connected(ver);
}

void insert(int x, int y)
{
	nodePointer node;

	//x->y
	MALLOC(node, sizeof(*node));
	node->ver = y;
	node->link = adjList[x];
	adjList[x] = node;
	//y->x
	MALLOC(node, sizeof(*node));
	node->ver = x;
	node->link = adjList[y];
	adjList[y] = node;
}

void dfs(int v)
{
	nodePointer  w;
	visited[v] = TRUE; //v정점 TRUE로 바꾸고 
	printf("%3d", v); //v부터 출력
	//인접연결리스트(adjList[])로 정리된 graph[]
	//시작할 때는 graph[v]에 연결된 노드부터 w에 집어넣고 
	for (w = adjList[v]; w; w = w->link) {
		if (!visited[w->ver]) //visited[node]==0 이면 
			dfs(w->ver); //graph[node]에 대해 dfs 진행
		//visited[node]==1 이면 0인 노드 찾을때까지 옆 노드로 이동
	}
	//v에 연결된 노드 모두 프린트
}

void Print(int v)
{
	nodePointer w;
	for (int i = 0; i < v; i++) {
		printf("graph[%d] :", i);
		for ( w = adjList[i]; w; w = w->link)
			printf("%5d", w->ver);
		printf("\n");
	}
	printf("\n");
}

void connected(int num)
{
	int cnt = 1;

	for (int i = 0; i < num; i++) {
		if (!visited[i]) { 
			//1번이랑 다르게 visited 초기화 안 해주니까
			//n번 vertex에서 visited[i]가 모두 1로 바뀌면
			//<=>모든 정점이 출력되면
			//더이상 출력되지 않음
			printf("connected component %d : ", cnt);
			dfs(i);
			printf("\n");
			cnt++;
		}
	}
}

