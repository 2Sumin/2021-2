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

void push(element item, int* n); //heap�� ���� ����
element pop(int* n); //heap�� ���� ū ���� ����
void Print(int* n); //heap�� ����ִ� �� ���

int main(void)
{
    element num,del;
    FILE* fp = fopen("input.txt", "r");
    printf("***** insertion into a max heap *****\n");
    while (!feof(fp)) {
        fscanf(fp, "%d ", &num.key);
        push(num, &n);//maxheap�� �ֱ�
        Print(&n);//maxheap���
    }
    printf("***** deletion from a max heap *****\n");
    while (heap) {
        del = pop(&n);//���� ū ���� ���ְ� 
        Print(&n);//���� heap ���
    }

    return 0;
}

void push(element item, int* n) //n�� heap �� ������ ��
{
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr,"The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n); //�ε����� 1���� ����
    //n�� 1�� ����->i�� ������ ��+1
    // \\���� ������ ���Ҹ� ���� �� �������� Ȯ���� ������ ��� ���� i
   
    //i�� 1�̸� n�� 0�̾���->�� �ȿ� ����ִ� �� ������
    //->�׳� �ٷ� heap[1]=item(whileX)
      
    //�ε����� 2�� ������(i/2) �θ��带 ����Ŵ
    //heap[i/2]�� �������� ��(item) ���ؼ� 
    //\\maxheap�� Ŭ���� �������ϱ�
    //�������� ���� �θ��庸�� �� ũ��
    //���� �θ��忡 �ִ� ���� �ؿ� ���� ���� ���� �а�
    //item���� ���ϴ� �θ����� �θ���� ��(i/=2)
    //�� �� ���ڸ��� ã�� ������ �� ���� �θ���� �� ��
    while ((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2]; //�θ��带 �Ʒ��� ������
        i /= 2;//���մ��Կ�����->������(i) ������ -> ��� ���� �ö󰡱�
    }
    //item���� �θ��庸�� �� ������ �ٷ� item �ֱ�
    heap[i] = item; //������ i ��ġ�� ���� �ִ´�
}

element pop(int* n)
{
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        //fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }
    //item�� ��Ʈ ���, temp�� ���� ���� ��� �ֱ�

    item = heap[1]; //���� ����(root) �� item�� �ֱ�(������)
    temp = heap[(*n)--]; //���� ������ ��� ��ġ �̵�
    //��������->ó������ n���� �״�� �ϰ� �� ������ ����
    //temp�� ������ ����� ���� ���� �� ������ ��(*n)�� 1 ����
    parent = 1; //\\�� ������ �׻� parent
    child = 2; //child+1=�� ���� �ڽĳ��
    //root �� ���ָ� �� ���ڸ��� �޿��, �ٽ� �� �� ���ڸ��� �޿�鼭
    // ���ġ�ϱ� ���� while�� ����
    
    //�ڽ� �� �� �� ū �� ���� �ø���
    while (child <= *n) {
        //child�� �� ���� �ڽ�(�������)�� temp�� ��
        //if������ child<*n ������ child==*n�̸� ������ (����)�ڽĳ�� ����
        //�� child�� Ʈ���� ������ ���->�������� ���� �ʿ� ����
        //->ù��° if�� �׳� �Ѿ��
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++; //�ڽ��� �θ� ���� ��&& �� �� �� ū �ڽ��� child
        if (temp.key >= heap[child].key) break;
        //temp�� ������ child�� ���� �� ũ�� child�� ���� �ø���
        //���� ù �ܰ迡���� chlld�� ���� temp���� ũ������
        //��� �����ϴ� ���� temp���� ���� child�� ����
        heap[parent] = heap[child];
        parent = child; //�����ִ� child�� �� ���� �θ� �ڸ��� �־
        //child�ڸ��� �� �ڸ��ϱ� �ű⸦ parent�� �缳���ؼ�
        //ó�� ���� �ٽ� ����
        child *= 2; //���� �ڽĳ�带 child�� �缳��
    }
    heap[parent] = temp; //temp�� child�� �ֱ�
    return item;
}

void Print(int* n)
{
    for (int i = 1; i <= *n; i++) 
        printf(" %2d", heap[i]);
    printf("\n");
}
