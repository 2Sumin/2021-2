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

FILE* inorder(treePointer ptr, FILE* fp)
{
    if (ptr) {
        inorder(ptr->leftChild, fp);
        fprintf(fp, "%d ", ptr->data);
        inorder(ptr->rightChild, fp);
    }
    return fp;
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
    FILE* fp = fopen("arr.txt", "w");
    int num; //노드 개수
    int node; //노드 데이터
    int sum = 0; //모든 노드의 합
    int max = -1; //가장 큰 수
    //int cnt=0; //max까지 탐색횟수
    int res = 0;//탐색횟수*노드 합
   // srand(time(NULL));
    num = 5;
    //num = rand() % 9 + 1;
    printf("Tree size(random): %d\n", num);
   // printf("Tree node data :\n");
    //for (int i = 0; i < num; i++) {
        //node = rand() % 99 + 1; //1~100 수 생성
        //if (max < node)
          //  max = node; //가장 큰 수 max에 저장
        //printf("%d\n", node);
            node = 55;
            root = createBinTree(node);

            node = 34;
            root->leftChild = createBinTree(node);

            node = 83;
            root->rightChild = createBinTree(node);

            node = 18;
            root->leftChild->leftChild = createBinTree(node);

            node = 54;
            root->leftChild->rightChild = createBinTree(node);

            //sum += node; //노드 데이터 합
   // }

    printf("The largest number : %d\n", max);

    printinorder(root);

    fp = inorder(root, fp);
    fclose(fp);

    fp = fopen("arr.txt", "r");

    int search[10];
    int cnt = 0;

    for (int i = 0; i < num; i++) {
        fscanf(fp, "%d ", &search[i]);
        if (search[i] == max)
            cnt = i;
    }
    fclose(fp);
    cnt += 1;

    printf("\nNumber of search: %d \n", cnt);
    //res = sum * cnt;
    //printf("Result: %d\n", res);

    return 0;
}