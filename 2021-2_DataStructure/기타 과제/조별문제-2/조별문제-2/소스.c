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

treePointer createBinTree(int data);
FILE* inorder(treePointer ptr, FILE* fp);
void printinorder(treePointer ptr);

int main(void)
{
    FILE* fp = fopen("arr.txt", "w");
    int num; //노드 개수
    int node; //노드 데이터(랜덤생성)
    int sum = 0; //모든 노드의 합
    int max = 0; //가장 큰 수
    int cnt = 0; //max까지 탐색횟수
    int res = 0;//탐색횟수*노드 합
    int search[10]; //중위 순회 순서대로 search배열에 저장
    srand(time(NULL));

    num = rand() % 9 + 1;
    printf("Tree size(random): %d\n", num);
    printf("Tree node data :\n");
    for (int i = 0; i < num; i++) {
        node = rand() % 99 + 1; //1~100 수 생성
        sum += node; //노드 데이터 합
        if (max < node)
            max = node; //가장 큰 수 max에 저장
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
        //노드 집어넣기
        //switch말고 노드 입력받는 방법...?
    }

    printf("The largest number : %d\n", max);

    printinorder(root); //중위순회 순서 확인용

    fp = inorder(root, fp); //중위순회 순서대로 fp에 저장
    fclose(fp);

    fp = fopen("arr.txt", "r");

    for (int i = 0; i < num; i++) {
        fscanf(fp, "%d ", &search[i]);
        if (search[i] == max) //max가 중위순회 순서 몇번째인지
            cnt = i + 1;
    }
    fclose(fp);

    printf("\nNumber of search: %d \n", cnt);
    res = sum * cnt;
    printf("Result: %d\n", res);

    return 0;
}

treePointer createBinTree(int data)
{
    treePointer ptr ;
    MALLOC(ptr, sizeof(*ptr));
    ptr->leftChild = NULL;
    ptr->rightChild = NULL;
    ptr->data = data;
    return ptr;
}

FILE* inorder(treePointer ptr,FILE* fp)
{
    if (ptr) {
        inorder(ptr->leftChild,fp);
        fprintf(fp,"%d ", ptr->data);
        inorder(ptr->rightChild,fp);
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

