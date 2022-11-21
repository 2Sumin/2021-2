#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define max(a,b) (((a)>(b))?(a):(b))

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct node* treePointer;
typedef struct node {
    char data; // ��������� ���� char ������ ����
    treePointer leftChild, rightChild;
}tNode;
treePointer root;

treePointer createBinTree(char data);
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);
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

    printf("�͹̳� ��� ��: %d\n", terminal_node(root));
    printf("�� ��� ��: %d\n", calc_node_count(root));
    printf("����:%d\n", calc_height(root));

   /* inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);
    */

    return 0;
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

treePointer createBinTree(char data)
{
    treePointer ptr;
    MALLOC(ptr, sizeof(*ptr));
    ptr->leftChild = NULL;
    ptr->rightChild = NULL;
    ptr->data = data;
    return ptr;
}

void inorder(treePointer ptr)
{ /* inorer tree traversal ������ȸ */ 
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{ /* preorder tree traversal ������ȸ */
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
} 

void postorder(treePointer ptr)
{ /* postorder tree traversal ������ȸ */
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}