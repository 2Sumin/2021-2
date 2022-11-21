#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include<stdlib.h>
#define size 100

//6조 문제
// 노드의 수 n을 입력받고
// n개의 값을 입력받아 이진탐색트리 구현
// 반복문을 사용하여 중위순회로 출력

//< 구현 내용>
//1)   트리를 만들 개수 n을 입력 받고 n개의 값을 입력 받는다.
//2)   Binary Search Tree를 구현한다.
//3)   중위순회(Inorder) 방법을 사용하여 출력한다.

//<조건>
//* Inorder 함수는 재귀를 쓰지 않고 반복문을 사용하여 구현한다.
//* 함수는 insert, Iter_Inorder를 구현할 것, 
//그 외 트리 구성에 필요한 함수는 자유롭게 작성

typedef struct treeNode {     //  정의
    int data;
    struct treeNode* left;
    struct treeNode* right;
}treeNode;

int top = -1;
treeNode* stack[size];

void push(treeNode* p) 
{
    if (top < size - 1 && p != NULL)
        stack[++top] = p;
}

treeNode* pop() 
{
    treeNode* p = NULL;
    if (top >= 0)
        p = stack[top--];
    return p;
}

void lter_inorder(treeNode* root) 
//재귀사용하지 않고 반복문 사용하는 중위연산 함수 
{
    while (1) {
        for (; root != NULL; root = root->left)
            push(root);
        root = pop();
        if (root == NULL)
            break;
        printf("%d ", root->data);
        root = root->right;
    }
}

treeNode* insert(treeNode* root, int data) 
{
    treeNode* newnode;
    if (root == NULL) {
        newnode = (treeNode*)malloc(sizeof(treeNode));
        newnode->data = data;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    }

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

int main(void)
{
    int n, i, num;
    treeNode* root = NULL;

    scanf("%d", &n); //노드의 수
    for (i = 0; i < n; i++) {
        scanf("%d", &num); //노드 data
        root = insert(root, num);
    }
    lter_inorder(root);
    return 0;
}