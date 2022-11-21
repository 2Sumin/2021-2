#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include<stdlib.h>
#define size 100

//6�� ����
// ����� �� n�� �Է¹ް�
// n���� ���� �Է¹޾� ����Ž��Ʈ�� ����
// �ݺ����� ����Ͽ� ������ȸ�� ���

//< ���� ����>
//1)   Ʈ���� ���� ���� n�� �Է� �ް� n���� ���� �Է� �޴´�.
//2)   Binary Search Tree�� �����Ѵ�.
//3)   ������ȸ(Inorder) ����� ����Ͽ� ����Ѵ�.

//<����>
//* Inorder �Լ��� ��͸� ���� �ʰ� �ݺ����� ����Ͽ� �����Ѵ�.
//* �Լ��� insert, Iter_Inorder�� ������ ��, 
//�� �� Ʈ�� ������ �ʿ��� �Լ��� �����Ӱ� �ۼ�

typedef struct treeNode {     //  ����
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
//��ͻ������ �ʰ� �ݺ��� ����ϴ� �������� �Լ� 
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

    scanf("%d", &n); //����� ��
    for (i = 0; i < n; i++) {
        scanf("%d", &num); //��� data
        root = insert(root, num);
    }
    lter_inorder(root);
    return 0;
}