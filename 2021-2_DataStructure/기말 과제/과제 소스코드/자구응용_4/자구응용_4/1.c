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

	fscanf(fp, "%c %d %d", &dir, &ver, &edge); //종류,정점,간선 수
	MALLOC(adjList, sizeof(*adjList) * ver); //정점 수만큼 adjList배열 생성

	for (int i = 0; i < ver; i++)
		adjList[i] = NULL; //초기화

	if (dir == 'u') { //무방향 그래프이면
		//ver1->ver2, ver2->ver1 둘 다 입력하기
		while (!feof(fp)) {
			fscanf(fp, "%d %d", &ver1, &ver2);
			addEdge(&adjList[ver1], ver2); //ver1->ver2
			addEdge(&adjList[ver2], ver1); //ver2->ver1
		}
	}
	else { //방향 그래프이면
		while (!feof(fp)) {
			//ver1->ver2
			fscanf(fp, "%d %d", &ver1, &ver2);
			addEdge(&adjList[ver1], ver2); //ver1->ver2
		}
	}
	fclose(fp);

	printf("<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>\n");
	for (int i = 0; i < ver; i++) { //정점 0부터
		printf("adjList[%d] : ", i);
		Print(adjList[i]);
		printf("\n");
	}

	return 0;
}

void addEdge(nodePointer* list, int ver)
{
	nodePointer tmp;
	MALLOC(tmp, sizeof(*tmp)); //노드 생성
	tmp->data = ver;
	if (*list) { //노드에 노드 연결
		//*list는 "마지막으로" adj[i]에 연결한 노드의 주소값
		tmp->link = *list;
		*list = tmp; 
		//tmp의 주소가 adj[i]의 주소에 저장
		//->adj[i]는 마지막으로 저장된 노드를 가리킴
	}
	else { //노드 연결된 거 없으면 첫 노드 연결
		tmp->link = NULL;
		*list = tmp;
		//tmp의 주소가 adj[i]에 저장됨
	}
}

void Print(nodePointer list)
{
	for (; list; list = list->link)
		printf(" %3d", list->data);
}
