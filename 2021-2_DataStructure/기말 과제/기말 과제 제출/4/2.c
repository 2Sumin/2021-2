#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct edge* tEdgePointer;
typedef struct edge {
	int vertex1;
	int vertex2;
	tEdgePointer link1;
	tEdgePointer link2;
}tEdge;
tEdgePointer* adjMulList;

tEdgePointer createEdge(int ver1, int ver2);
void addEdge(int ver1, int ver2);
void printMultilist(int numVertex);

int main(void)
{
	FILE* fp;
	int vertex, edge, ver1, ver2;

	//fp=fopen("input.txt", "r");
	//fp=fopen("input2.txt", "r");
	fp=fopen("input4.txt", "r");

	fscanf(fp, "%d %d", &vertex, &edge); //정점, 간선 수 입력
	MALLOC(adjMulList, sizeof(*adjMulList) * vertex); //adjList 배열 할당

	for (int i = 0; i < vertex; i++)
		adjMulList[i] = NULL;

	printf("<<<<<<<<<< edges incident to each vertex >>>>>>>>>>\n\n");
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &ver1, &ver2);
		addEdge(ver1, ver2);
	}

	printMultilist(vertex);

	return 0;
}

tEdgePointer createEdge(int ver1, int ver2)
{
	tEdgePointer ptr;
	MALLOC(ptr, sizeof(ptr));
	ptr->vertex1 = ver1;
	ptr->vertex2 = ver2;
	ptr->link1 = NULL;
	ptr->link2 = NULL;

	return ptr;
}

void addEdge(int ver1, int ver2)
{
	tEdgePointer ptr = createEdge(ver1, ver2);
	tEdgePointer tmp;
	if (adjMulList[ver1])	{ 
		 tmp = adjMulList[ver1];
		while (1) {
			if (tmp->vertex1 == ver1) { 
				if (!tmp->link1) {
					tmp->link1 = ptr;
					break;
				}
				tmp = tmp->link1;
			}
			else {
				if (!tmp->link2) {
					tmp->link2 = ptr;
					break;
				}
				tmp = tmp->link2;
			}
		}
	}
	else
		adjMulList[ver1] = ptr;

	if (adjMulList[ver2]) {
		 tmp = adjMulList[ver2];
		while (1) {
			if (tmp->vertex1 == ver2) {
				if (!tmp->link1) {
					tmp->link1 = ptr;
					break;
				}
				tmp = tmp->link1;
			}
			else {
				if (!tmp->link2) {
					tmp->link2 = ptr;
					break;
				}
				tmp = tmp->link2;
			}
		}
	}
	else
		adjMulList[ver2] = ptr;
}

void printMultilist(int numVertex)
{
	tEdgePointer tmp;
	printf("간선의 정점 출력 순서 - 입력데이터 순서대로\n");
	for (int i = 0; i < numVertex; i++) {
		tmp = adjMulList[i];
		printf("edges incident to vertex %d : ", i);

		while (tmp) {
			printf("(%d, %d) ", tmp->vertex1, tmp->vertex2);
			if (tmp->vertex1 == i)
				tmp = tmp->link1;
			else
				tmp = tmp->link2;
		}
		printf("\n");
	}
	printf("\n");

	printf("간선의 정점 출력 순서 - 헤더노드 정점이 먼저 오게\n");
	for (int i = 0; i < numVertex; i++) {
		tmp = adjMulList[i];
		printf("edges incident to vertex %d : ", i);

		while (tmp) {
			if (tmp->vertex1 == i) {
				printf("(%d, %d) ", tmp->vertex1, tmp->vertex2);
				tmp = tmp->link1;
			}
			else {
				printf("(%d, %d) ", tmp->vertex2, tmp->vertex1);
				tmp = tmp->link2;
			}
		}
		printf("\n");
	}
}