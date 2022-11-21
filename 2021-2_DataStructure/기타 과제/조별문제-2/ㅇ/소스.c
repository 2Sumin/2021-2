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

int inorder(treePointer ptr, int max, int num)
{
    int i = 0;
    int search[10] = { 0 };
    int cnt = 0;
    if (ptr) {
        inorder(ptr->leftChild, max, num);
        search[i++] = ptr->data;
        inorder(ptr->rightChild, max, num);
    }

    for (int j = 0; j < num; j++) {
        if (max == search[j])
            cnt = j + 1;
    }

    return cnt;
}

void printinorder(treePointer ptr)
{
    if (ptr) {
        printinorder(ptr->leftChild);
        printf("%d ", ptr->data);
        printinorder(ptr->rightChild);
    }
}

int main(void)
{
    int num; //��� ����
    int node; //��� ������
    int sum = 0; //��� ����� ��
    int max = -1; //���� ū ��
    //int cnt=0; //max���� Ž��Ƚ��
    int res = 0;//Ž��Ƚ��*��� ��
    /*srand(time(NULL));

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
    }*/

    root = createBinTree(55);
            root->leftChild = createBinTree(34);
            root->rightChild = createBinTree(83);
            root->leftChild->leftChild = createBinTree(18);
            root->leftChild->rightChild = createBinTree(54);


    printf("The largest number : %d\n", max);

    printinorder(root);

   /* int cnt = inorder(root, max, num);

    printf("\nNumber of search: %d \n", cnt);
    res = sum * cnt;
    printf("Result: %d\n", res);*/

    return 0;
}