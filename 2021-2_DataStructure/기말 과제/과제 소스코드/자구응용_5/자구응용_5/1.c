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

short int visited[MAX_VERTICES]; //전역변수->모두 0(False)로 초기화됨
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

	//인접 연결리스트로 표현
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &u, &v);
		insert(u, v);
	}
	Print(ver); //인접연결리스트 출력

	printf("<<<<<<<<<<<<<<< Depth First Search >>>>>>>>>>>>>>>\n");
	for (int i = 0; i < ver; i++) {
		printf("dfs<%d> :", i);
		dfs(i);
		//다음 dfs 진행하기 전에 모두 초기화
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
	tmp->link = graph[x]; //graph[x]에 들어있던 거는 앞의 노드의 주소
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
	visited[v] = TRUE; //시작하는 v정점 TRUE로 바꾸고 
	printf("%5d", v); //v부터 출력
	//인접연결리스트(adjList[])로 정리된 graph[]
	//시작할 때는 graph[v]에 연결된 노드부터 w에 집어넣고 
	for (w = graph[v]; w; w = w->link) { 
		if (!visited[w->ver]) //visited[node]==0 이면 
			dfs(w->ver); //graph[node]에 대해 dfs 진행
		//visited[node]==1 이면 0인 노드 찾을때까지 옆 노드로 이동
		//옆으로 끝까지 갔는데 visited[node]==0인게 없으면 backtracking
	}
	//v에 연결된 노드 모두 프린트
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

