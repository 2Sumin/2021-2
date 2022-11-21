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
        Print(&n);//���
    }
    printf("***** deletion from a min heap *****\n");
    while (heap) {
        del = pop(&n);
        Print(&n);
    }

    return 0;
}

void push(element item, int* n)
{//���� ���� ���Ұ� ���� ������
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr, "The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n);
    //���� ���� ���� �θ��庸�� �� ������
    while ((i != 1) && (item.key < heap[i / 2].key)) {
        heap[i] = heap[i / 2]; //�θ��� �Ʒ��� ������
        i /= 2; //�θ����� �ε����� i��->�� �θ�� �ٽ� ��
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
    //���� ���� ��带 item, ���� �Ʒ��� ��带 temp�� �ֱ�
    item = heap[1]; //���Ŵ��
    temp = heap[(*n)--]; //n�� item�� ������ �� ��� ��
    parent = 1;
    child = 2;
    while (child <= *n) {
        //�������� �ڽ� �� �� ���� �ڽ� ��带 child�� ����
        if ((child < *n) && (heap[child].key > heap[child + 1].key))
            child++;
        if (temp.key <= heap[child].key) break;
        //�� �ܰ� �Ʒ��� �̵�
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
