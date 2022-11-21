#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

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
treePointer queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

treePointer createNode(char data);
treePointer createCompBinTree();
void insert(treePointer* pRoot, treePointer pNode);
int hasBothChild(treePointer pNode);

void addq(treePointer item);
treePointer deleteq();
void queueFull();
treePointer deleteEmpty();
treePointer getFront();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main(void)
{
    root = createCompBinTree();

    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    postorder(root);

    return 0;
}

treePointer createNode(char data)
{
    treePointer ptr;
    MALLOC(ptr, sizeof(*ptr));
    ptr->leftChild = NULL;
    ptr->rightChild = NULL;
    ptr->data = data;
    return ptr;
}

treePointer createCompBinTree()
{
    char input[10];

    scanf("%s", &input);
    for (int i = 0; input[i]; i++)
        insert(&root, createNode(input[i]));

    printf("%s\n", input);
    return root;
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

void addq(treePointer item)
{
    if (rear == MAX_QUEUE_SIZE - 1)
        queueFull();
    queue[++rear] = item;
}

treePointer deleteq()
{
    if (front == rear)
        return deleteEmpty();
    return queue[++front];
}

void queueFull()
{
    if (front == -1) {
        fprintf(stderr, "Queue is full");
        exit(EXIT_FAILURE);
    }
    else { //큐의 항목들을 이동
        int num = front + 1; //front-(-1)=front+1
        front = -1;
        for (int i = 0; i < rear + 1 - num; i++)
            queue[i] = queue[num + i];
        rear = rear - num;
    }
}

treePointer deleteEmpty()
{
    fprintf(stderr, "Queue is empty");
    exit(EXIT_FAILURE);
    return NULL;
}

treePointer getFront()
{
    return queue[front + 1];
}

void insert(treePointer* pRoot, treePointer pNode)
{
    if (!(*pRoot))
        *pRoot = pNode;

    else {
        treePointer gfront = getFront();

        if (!(gfront->leftChild))
            gfront->leftChild = pNode;

        else if (!(gfront->rightChild))
            gfront->rightChild = pNode;

        if (hasBothChild(gfront))
            deleteq();
    }
    addq(pNode);
}

int hasBothChild(treePointer pNode)
{
    return pNode && pNode->leftChild && pNode->rightChild;
}
