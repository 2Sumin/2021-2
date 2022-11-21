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
{ /* inorer tree traversal 중위순회 */
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
{ /* inorer tree traversal 중위순회 */
    if (ptr) {
        inorderr(ptr->leftChild);
        printf("%d ", ptr->data);
        inorderr(ptr->rightChild);
    }
}

int main(void)
{
    int num; //노드 개수
    int node; //노드 데이터
    int sum = 0; //모든 노드의 합
    int max = -1; //가장 큰 수
    int cnt = 0;//탐색횟수
    int res = 0;//탐색횟수*노드 합
    srand(time(NULL));

    num = rand() % 9 + 1;
    printf("Tree size(random): %d\n", num);
    printf("Tree node data :\n");
    for (int i = 0; i < num; i++) {
        node = rand() % 99 + 1; //1~100 수 생성
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
        sum += node; //노드 데이터 합
    }

    printf("The largest number : %d\n", max);

    inorderr(root); //중위순회 순서대로 출력

    printf("\nNumber of search: %d \n", cnt);
    res = sum * cnt;
    printf("Result: %d\n", res);

    return 0;
}