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
			visited[j] = FALSE; //���� bfs�� ���� �ʱ�ȭ
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

	if (front) //ť�� ���� ������
		rear->next = temp; //������ ��� ������ �� ��� �߰�
	else
		front = temp;

	rear = temp; //�߰��� ��带 ���������� ����
}

int deleteq()
{
	nodePointer temp = front; //������ ���(���� ���� front)
	int item;

	/*if (!temp)
		return queueEmpty;*/

	item = temp->vertex;
	front = temp->next; //front�� ���� ���� ���ֱ� (���� ��带 front��)
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
//�� �پ� �ؼ�(graph[0]�� ����� �� ��� ��� �� graph[1]) ��� ���� ���
{
	front = rear = NULL;
	printf("%5d", v); //v�� ���� ����ϰ�
	visited[v] = TRUE; //v�� ���� 1�� �ٲٰ� 
	addq(v); //ť�� �߰�
	while (front) { //ť�� ���� ������
		v = deleteq(); //ť ���� �տ� �ִ� �� ���� �װſ� ���� for��
		//ó������ graph[v]�� ����� ù���� ��带 w�� ����
		for (nodePointer w = graph[v]; w; w = w->next) {
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex); //����� ��� ���� ����ϰ�
				addq(w->vertex); //ť�� �ְ�
				visited[w->vertex] = TRUE; //visited=>1�� �ٲٱ�
			} //������ ����� ��尡 ������ while������ ���ư���
		}
	}
	//ť�� �ƹ��͵� ���������� ����
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
