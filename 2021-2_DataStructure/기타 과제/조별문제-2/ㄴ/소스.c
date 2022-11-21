#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct treeNode {     //  정의
    int data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

void inorder(treeNode* root) {  //중위순회
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

treeNode* createTree(int data) {//treenode 생성
    treeNode* newNode;
    newNode = (treeNode*)malloc(sizeof(treeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int findMax(int ary[10], int max, int n) {//max값 탐색횟수 ary배열에 저장
    int i, count = 0;
    for (i = 0; i < n; i++) {
        if (ary[i] == max) {
            count++;
            return count;
        }
        else
            count++;
    }
}

int main(void)
{
    int num, i, data, max = 0, sum = 0, count, j = 0, result;
    int ary[10] = { 0, };
    treeNode* root;
    root = (treeNode*)malloc(sizeof(treeNode));
    root->left = NULL;
    root->right = NULL;

   // srand(time(NULL));

   // num = rand() % 9 + 1;
    num = 5;
    printf("Tree size(random) : %d\n", num);
    printf("Tree node data :\n");

    for (i = 0; i < num; i++) {
       // data = rand() % 99 + 1;
        if (max < data)
            max = data;
        printf("%d\n", data);
        ary[j++] = data;
        switch (i) {

        case 0:
            data = 55;
            root = createTree(data);
            break;
        case 1:
            data = 34;
            root->left = createTree(data);
            break;
        case 2:
            data = 83;
            root->right = createTree(data);
            break;
        case 3:
            data = 18;
            root->left->left = createTree(data);
            break;
        case 4:
            data = 54;
            root->left->right = createTree(data);
            break;
        }
        sum = sum + data;
    }
    printf("The largest number : %d\n", max);

    count = findMax(ary, max, num);
    result = sum * count;
    inorder(root);
    printf("\nNumber of search : %d\n", count);
   // printf("Sum : %d\n", sum);
    printf("Result : %d\n", result);

    return 0;
}