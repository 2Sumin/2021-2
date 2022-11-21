#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct node* treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
}tNode;
treePointer root;

treePointer createBinTree(int data)
{
    treePointer ptr;
    MALLOC(ptr, sizeof(*ptr));
    ptr->leftChild = NULL;
    ptr->rightChild = NULL;
    ptr->data = data;
    return ptr;
}

int inorder(treePointer ptr, int max)
{ /* inorer tree traversal ������ȸ */
    int cnt = 0;
    if (ptr) {
        ++cnt;
        inorder(ptr->leftChild, max);

        if (ptr->data == max)
            return cnt;

        ++cnt;
        inorder(ptr->rightChild, max);
    }
}

void (treePointer ptr)
{ /* inorer tree traversal ������ȸ */
    if (ptr) {
        inorderr(ptr->leftChild);
        printf("%d ", ptr->data);
        inorderr(ptr->rightChild);
    }
}

int main(void)
{
    int num; //��� ����
    int node; //��� ������
    int sum = 0; //��� ����� ��
    int max = -1; //���� ū ��
    int cnt = 0;//Ž��Ƚ��
    int res = 0;//Ž��Ƚ��*��� ��
    srand(time(NULL));

    num = rand() % 9 + 1;
    printf("Tree size(random): %d\n", num);
    printf("Tree node data :\n");
    for (int i = 0; i < num; i++) {
        node = rand() % 99 + 1; //1~100 �� ����
        if (max < node)
            max = node; //���� ū �� max�� ����
        printf("%d\n", node);
        switch (i) {
        case 0:
            root = createBinTree(node);
            break;
        case 1:
            root->leftChild = createBinTree(node);
            break;
        case 2:
            root->rightChild = createBinTree(node);
            break;
        case 3:
            root->leftChild->leftChild = createBinTree(node);
            break;
        case 4:
            root->leftChild->rightChild = createBinTree(node);
            break;
        case 5:
            root->rightChild->leftChild = createBinTree(node);
            break;
        case 6:
            root->rightChild->rightChild = createBinTree(node);
            break;
        case 7:
            root->leftChild->leftChild->leftChild = createBinTree(node);
            break;
        case 8:
            root->leftChild->leftChild->rightChild = createBinTree(node);
            break;
        case 9:
            root->leftChild->rightChild->leftChild = createBinTree(node);
            break;
        }
        sum += node; //��� ������ ��
    }

    printf("The largest number : %d\n", max);

    inorderr(root); //������ȸ ������� ���

    printf("\nNumber of search: %d \n", cnt);
    res = sum * cnt;
    printf("Result: %d\n", res);

    return 0;
}