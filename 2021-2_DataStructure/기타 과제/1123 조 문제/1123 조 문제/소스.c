#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef int iType;
typedef struct {
    int key;
    iType item; 
}element;

typedef struct node* treePointer;
typedef struct node {
    element data;
    treePointer leftChild, rightChild;
}tNode;

void insert(treePointer* node, int k, iType theItem);
void delete(treePointer* node, int k);
treePointer modifiedSearch(treePointer nd, int k);
element* search(treePointer root, int k);
void display(int arr[], int num);//입력받은 순서대로 출력
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main(void)
{
    char command;
    element e;
    int printAry[100];
    int i = 0;
    treePointer root = NULL;
    element* tmp;
    char print;

    while (1) {
        printf("삽입(i), 탐색(s), 프린트(p), 삭제(d), 종료(q): ");

        scanf(" %c", &command);

        switch (command) {

        case 'i':
            printf("학번: ");
            scanf("%d", &e.item);
            printAry[i++] = e.item;
            e.key = e.item;
            insert(&root, e.key, e.item);
            break;

        case 'd':
            printf("학번: ");
            scanf("%d", &e.item);
            getchar();
            delete(&root, e.item);
            break;

        case 'p': 
            printf("순서대로 출력(p), 중위순회(i), 후위순회(o), 전위순회(r): ");
            scanf(" %c", &print);
            getchar();
            switch (print) {
            case 'p':
                display(printAry,i);
                break;
            case 'i':
                inorder(root);
                break;
            case 'o':
                postorder(root);
                break;
            case 'r':
                preorder(root);
                break;
            default:
                break;
            }
            printf("\n");
            break;

        case 's':
            printf("학번:");
            scanf(" %d", &e.item);
            getchar();
            tmp = search(root, e.item);
            if (tmp)
                printf("찾는 학번은 %d번째\n", tmp->key);
            else
                printf("데이터가 존재하지 않습니다.\n");
            break;

        case 'q':
            return 0;
            break;

        default:
            break;
        }
        printf("\n");
    }
    return 0;
}

treePointer modifiedSearch(treePointer nd, int k)
{
    treePointer p = NULL;

    while (nd) {
        if (k == nd->data.key)
            return NULL;

        if (k < nd->data.key){
            p = nd;
            nd = nd->leftChild;
        }
        else {
            p = nd;
            nd = nd->rightChild;
        }
    }
    return p;
}

void insert(treePointer* node, int k, iType theItem)
{
    treePointer ptr, tmp = modifiedSearch(*node, k);
    if (tmp || !(*node)) {
        MALLOC(ptr, sizeof(*ptr));
        ptr->data.key = k;
        ptr->data.item = theItem;
        ptr->leftChild = ptr->rightChild = NULL;
        if (*node) {
            if (k < tmp->data.key) tmp->leftChild = ptr;
            else tmp->rightChild = ptr;
        }
        else *node = ptr;
    }
}

void delete(treePointer* node, int k)
{
    if (*node) {
        if (k < (*node)->data.item) 
            delete(&(*node)->leftChild, k);
        
        else if (k > (*node)->data.item) 
            delete(&(*node)->rightChild, k);

        else if ((*node)->leftChild == NULL && (*node)->rightChild == NULL)
            *node = NULL;

        else if ((*node)->leftChild == NULL)
            *node = (*node)->rightChild;

        else if ((*node)->rightChild == NULL)
            *node = (*node)->leftChild;
       
        else 
            printf("impossible");
    }
}

element* search(treePointer root, int k)
{
    if (!root) return NULL;
    if (k == root->data.key) return &(root->data);
    if (k < root->data.key)
        return search(root->leftChild, k);
    return search(root->rightChild, k);
}

void display(int arr[],int num)
{
    for (int i = 0; i < num; i++)
        printf("%d ", arr[i]);
   
}

void inorder(treePointer ptr)
{ 
    if (ptr) {
        inorder(ptr->leftChild);
        printf("%d ", ptr->data.item);
        inorder(ptr->rightChild);
    }
}

void preorder(treePointer ptr)
{ 
    if (ptr) {
        printf("%d ", ptr->data.item);
        preorder(ptr->leftChild);
        preorder(ptr->rightChild);
    }
}

void postorder(treePointer ptr)
{ 
    if (ptr) {
        postorder(ptr->leftChild);
        postorder(ptr->rightChild);
        printf("%d ", ptr->data.item);
    }
}