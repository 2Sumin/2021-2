#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
    int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n);
element pop(int* n);
void Print(int* n);

int main(void)
{
    element num, del;
    FILE* fp = fopen("input.txt", "r");
    printf("***** insertion into a min heap *****\n");
    while (!feof(fp)) {
        fscanf(fp, "%d ", &num.key);
        push(num, &n);
        Print(&n);//출력
    }
    printf("***** deletion from a min heap *****\n");
    while (heap) {
        del = pop(&n);
        Print(&n);
    }

    return 0;
}

void push(element item, int* n)
{//제일 작은 원소가 위로 가도록
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n);
    //새로 넣을 값이 부모노드보다 더 작으면
    while ((i != 1) && (item.key < heap[i / 2].key)) {
        heap[i] = heap[i / 2]; //부모노드 아래로 내리기
        i /= 2; //부모노드의 인덱스를 i로->그 부모와 다시 비교
    }
    heap[i] = item;
}

element pop(int* n)
{
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
       // fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }
    //제일 위의 노드를 item, 제일 아래의 노드를 temp에 넣기
    item = heap[1]; //제거대상
    temp = heap[(*n)--]; //n은 item을 제거한 후 노드 수
    parent = 1;
    child = 2;
    while (child <= *n) {
        //현재노드의 자식 중 더 작은 자식 노드를 child로 설정
        if ((child < *n) && (heap[child].key > heap[child + 1].key))
            child++;
        if (temp.key <= heap[child].key) break;
        //한 단계 아래로 이동
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

void Print(int* n)
{
    for (int i = 1; i <= *n; i++) 
        printf(" %2d", heap[i]);
    printf("\n");
}
