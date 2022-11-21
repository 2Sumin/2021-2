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

typedef struct qNode* queuePointer;
typedef struct qNode {
	int vertex;
	queuePointer link;
}tQNode;

queuePointer front, rear;
short int visited[MAX_VERTICES];
queuePointer graph[MAX_VERTICES];

void insert(int x, int y);
void Print(int v);
void addq(int item);
int deleteq();
void bfs(int v);

int main(void)
{
	int vertex, edge, u, v;

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);

	while (!feof(fp)) {
		fscanf(fp, "%d %d", &u, &v);
		insert(u, v);
	}
	Print(vertex);

	printf("<<<<<<<<<<<<<<< Breadth First Search >>>>>>>>>>>>>>>\n");
	for (int i = 0; i < vertex; i++) {
		printf("bfs<%d> :", i);
		bfs(i);
		for (int j = 0; j < vertex; j++)
			visited[j] = FALSE; //다음 bfs를 위해 초기화
		printf("\n");
	}

	fclose(fp);
	return 0;
}

void insert(int x, int y)
{
	queuePointer tmp;
	//x->y
	MALLOC(tmp, sizeof(*tmp));
	tmp->vertex = y;
	tmp->link = graph[x];
	graph[x] = tmp;
	//y->x
	MALLOC(tmp, sizeof(*tmp));
	tmp->vertex = x;
	tmp->link = graph[y];
	graph[y] = tmp;
}

void Print(int v)
{
	printf("<<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>>\n");
	for (int i = 0; i < v; i++) {
		printf("graph[%d] :", i);
		for (queuePointer w = graph[i]; w; w = w->link)
			printf("%5d", w->vertex);
		printf("\n");
	}
	printf("\n");
}

void addq(int item)
{
	queuePointer tmp;
	MALLOC(tmp, sizeof(*tmp));

	tmp->vertex = item;
	tmp->link = NULL;

	if (front) //큐에 뭐가 있으면
		rear->link = tmp; //마지막 노드 다음에 새 노드 추가
	else
		front = tmp;

	rear = tmp; //추가한 노드를 마지막노드로 설정
}

int deleteq()
{
	queuePointer tmp = front; //삭제할 노드(제일 앞의 front)
	int item;

	item = tmp->vertex;
	front = tmp->link; //front의 정보 빼고 없애기 (다음 노드를 front로)

	return item;
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
		for (queuePointer w = graph[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex); //연결된 노드 원소 출력하고
				addq(w->vertex); //큐에 넣고
				visited[w->vertex] = TRUE; //visited=>1로 바꾸기
			} //다음에 연결된 노드가 없으면 while문으로 돌아가기
		}
	}
	//큐에 아무것도 남지않으면 종료
}