#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}tNode;

void addEdge(nodePointer * list, int ver);
void Print(nodePointer list);

int main(void)
{
	FILE* fp;
	int ver, edge, ver1, ver2;
	char dir; //directed / undirected
	nodePointer* adjList;

	//fp = fopen("input.txt", "r");
	//fp=fopen("input2.txt", "r");
	fp=fopen("input3.txt", "r");

	fscanf(fp, "%c %d %d", &dir, &ver, &edge); //����,����,���� ��
	MALLOC(adjList, sizeof(*adjList) * ver); //���� ����ŭ adjList�迭 ����

	for (int i = 0; i < ver; i++)
		adjList[i] = NULL; //�ʱ�ȭ

	if (dir == 'u') { //������ �׷����̸�
		//ver1->ver2, ver2->ver1 �� �� �Է��ϱ�
		while (!feof(fp)) {
			fscanf(fp, "%d %d", &ver1, &ver2);
			addEdge(&adjList[ver1], ver2); //ver1->ver2
			addEdge(&adjList[ver2], ver1); //ver2->ver1
		}
	}
	else { //���� �׷����̸�
		while (!feof(fp)) {
			//ver1->ver2
			fscanf(fp, "%d %d", &ver1, &ver2);
			addEdge(&adjList[ver1], ver2); //ver1->ver2
		}
	}
	fclose(fp);

	printf("<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>\n");
	for (int i = 0; i < ver; i++) { //���� 0����
		printf("adjList[%d] : ", i);
		Print(adjList[i]);
		printf("\n");
	}

	return 0;
}

void addEdge(nodePointer* list, int ver)
{
	nodePointer tmp;
	MALLOC(tmp, sizeof(*tmp)); //��� ����
	tmp->data = ver;
	if (*list) { //��忡 ��� ����
		//*list�� "����������" adj[i]�� ������ ����� �ּҰ�
		tmp->link = *list;
		*list = tmp; 
		//tmp�� �ּҰ� adj[i]�� �ּҿ� ����
		//->adj[i]�� ���������� ����� ��带 ����Ŵ
	}
	else { //��� ����� �� ������ ù ��� ����
		tmp->link = NULL;
		*list = tmp;
		//tmp�� �ּҰ� adj[i]�� �����
	}
}

void Print(nodePointer list)
{
	for (; list; list = list->link)
		printf(" %3d", list->data);
}
