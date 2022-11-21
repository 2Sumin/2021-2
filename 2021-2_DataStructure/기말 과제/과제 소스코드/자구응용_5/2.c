#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 100
#define FALSE 0
#define TRUE 1

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct NODE* nodePointer;
typedef struct NODE {
	int vertex;
	nodePointer next;
}NODE;

int visited[MAX_VERTICES];
nodePointer graph[MAX_VERTICES];
nodePointer front, rear;

void addq(int x);
int deleteq();
void insert(int x, int y);
void Print(int v);
void bfs(int v);

int main()
{
	int vertex, edge, u, v;

	FILE* f = fopen("input.txt", "r");
	fscanf(f, "%d %d", &vertex, &edge);

	while (!feof(f)) {
		fscanf(f, "%d %d", &u, &v);
		insert(u, v);
	}
	Print(vertex);

	printf("<<<<<<<<<< Breadth First Search >>>>>>>>>>\n");
	for (int i = 0; i < vertex; i++) {
		printf("bfs<%d> :", i);
		bfs(i);
		for (int j = 0; j < vertex; j++)
			visited[j] = FALSE; //다음 bfs를 위해 초기화
		puts("");
	}

	fclose(f);
	return 0;
}

void addq(int x)
{
	nodePointer temp;
	MALLOC(temp, sizeof(*temp));

	temp->vertex = x;
	temp->next = NULL;

	if (front) //큐에 뭐가 있으면
		rear->next = temp; //마지막 노드 다음에 새 노드 추가
	else
		front = temp;

	rear = temp; //추가한 노드를 마지막노드로 설정
}

int deleteq()
{
	nodePointer temp = front; //삭제할 노드(제일 앞의 front)
	int item;

	/*if (!temp)
		return queueEmpty;*/

	item = temp->vertex;
	front = temp->next; //front의 정보 빼고 없애기 (다음 노드를 front로)
	//free(temp);

	return item;
}

void Print(int v)
{
	printf("<<<<<<<<<< Adjacency List >>>>>>>>>>\n");
	for (int i = 0; i < v; i++) {
		printf("graph[%d] :", i);
		for (nodePointer w = graph[i]; w; w = w->next)
			printf("%5d", w->vertex);
		puts("");
	}
	puts("");
}

void bfs(int v) 
//한 줄씩 해서(graph[0]에 연결된 것 모두 출력 후 graph[1]) 모든 원소 출력
{
	front = rear = NULL;
	printf("%5d", v); //v번 정점 출력하고
	visited[v] = TRUE; //v번 정점 1로 바꾸고 
	addq(v); //큐에 추가
	while (front) { //큐에 뭔가 있으면
		v = deleteq(); //큐 제일 앞에 있는 거 빼서 그거에 대해 for문
		//처음에는 graph[v]에 연결된 첫번때 노드를 w로 설정
		for (nodePointer w = graph[v]; w; w = w->next) {
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex); //연결된 노드 원소 출력하고
				addq(w->vertex); //큐에 넣고
				visited[w->vertex] = TRUE; //visited=>1로 바꾸기
			} //다음에 연결된 노드가 없으면 while문으로 돌아가기
		}
	}
	//큐에 아무것도 남지않으면 종료
}


void insert(int x, int y)
{//adj
	//(x,y)
	nodePointer tmp;
	//x->y
	MALLOC(tmp, sizeof(*tmp));
	tmp->vertex = y;
	tmp->next = graph[x];
	graph[x] = tmp;
	//y->x
	MALLOC(tmp, sizeof(*tmp));
	tmp->vertex = x;
	tmp->next = graph[y];
	graph[y] = tmp;

	/*LINK node, node2;
	MALLOC(node, sizeof(NODE));
	MALLOC(node2, sizeof(NODE));

	node->vertex = y;
	node->next = NULL;

	node2->vertex = x;
	node2->next = NULL;
	if (graph[x]) {
		node->next = graph[x];
		graph[x] = node;
	}
	else
		graph[x] = node;

	if (graph[y]) {
		node2->next = graph[y];
		graph[y] = node2;
	}
	else
		graph[y] = node2;
		*/
}
