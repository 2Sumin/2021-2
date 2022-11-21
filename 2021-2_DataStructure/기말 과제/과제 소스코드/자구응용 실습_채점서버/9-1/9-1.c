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
    char data; // 문자출력을 위해 char 형으로 지정
    treePointer leftChild, rightChild;
}tNode;
treePointer root;

treePointer createBinTree(char data);
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main(void)
{
    root = createBinTree('A');
    root->leftChild = createBinTree('B');
    root->rightChild = createBinTree('C');
    root->leftChild->leftChild = createBinTree('D');
    root->leftChild->rightChild = createBinTree('E');

    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);

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

void inorder(treePointer ptr)
{ /* inorer tree traversal 중위순회 */
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%c", ptr->data);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{ /* preorder tree traversal 전위순회 */
    if (ptr) {
        printf("%c", ptr->data);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr)
{ /* postorder tree traversal 후위순회 */
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%c", ptr->data);
    }
}
