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
			visited[j] = FALSE; //���� bfs�� ���� �ʱ�ȭ
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

	if (front) //ť�� ���� ������
		rear->link = tmp; //������ ��� ������ �� ��� �߰�
	else
		front = tmp;

	rear = tmp; //�߰��� ��带 ���������� ����
}

int deleteq()
{
	queuePointer tmp = front; //������ ���(���� ���� front)
	int item;

	item = tmp->vertex;
	front = tmp->link; //front�� ���� ���� ���ֱ� (���� ��带 front��)

	return item;
}


void bfs(int v) 
//�� �پ� �ؼ�(graph[0]�� ����� �� ��� ��� �� graph[1]) ��� ���� ���
{
	front = rear = NULL;
	printf("%5d", v); //v�� ���� ����ϰ�
	visited[v] = TRUE; //v�� ���� 1�� �ٲٰ� 
	addq(v); //ť�� �߰�
	while (front) { //ť�� ���� ������
		v = deleteq(); //ť ���� �տ� �ִ� �� ���� �װſ� ���� for��
		//ó������ graph[v]�� ����� ù���� ��带 w�� ����
		for (queuePointer w = graph[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex); //����� ��� ���� ����ϰ�
				addq(w->vertex); //ť�� �ְ�
				visited[w->vertex] = TRUE; //visited=>1�� �ٲٱ�
			} //������ ����� ��尡 ������ while������ ���ư���
		}
	}
	//ť�� �ƹ��͵� ���������� ����
}