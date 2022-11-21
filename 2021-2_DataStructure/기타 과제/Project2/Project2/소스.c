#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct node* treePointer;
typedef struct node {
    char data; 
    treePointer leftChild, rightChild;
}tNode;
treePointer root;

treePointer createBinTree(char data);
int calc_height(treePointer root);
int terminal_node(treePointer root);
int calc_node_count(treePointer root);

int main(void)
{
    root = createBinTree('A');
    root->leftChild = createBinTree('B');
    root->rightChild = createBinTree('C');
    root->leftChild->leftChild = createBinTree('D');
    root->leftChild->rightChild = createBinTree('E');
    root->rightChild->leftChild = createBinTree('F');
    root->rightChild->rightChild = createBinTree('G');

    printf("터미널 노드 수: %d\n",terminal_node(root));
    printf("총 노드 수: %d\n",calc_node_count(root));
    printf("차수: %d\n",calc_height(root));

    return 0;
}

treePointer createBinTree(char data)
{
    treePointer ptr;
    MALLOC(ptr, sizeof(*ptr));
    ptr->leftChild = NULL;
    ptr->rightChild = NULL;
    ptr->data = data;
    return ptr;
}

int calc_height(treePointer root)
{
    int height = 0;
    if (root != NULL)
        height = 1 + max(calc_height(root->leftChild), calc_height(root->rightChild));
    return height;
}

int terminal_node(treePointer root)
{
    int cnt = 0;
    if (root) {
        if (root->rightChild == NULL && root->leftChild == NULL) {
            return 1;
        }
        cnt = cnt + terminal_node(root->rightChild);
        cnt = cnt + terminal_node(root->leftChild);
        return cnt;
    }
}

int calc_node_count(treePointer root)
{
    int cnt = 0;
    if (root != NULL)
        cnt = 1 + calc_node_count(root->leftChild) + calc_node_count(root->rightChild);
    return cnt;
}