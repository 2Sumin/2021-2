#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200 

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef int iType;
typedef struct {
	int key;
	iType item;
} element;
typedef struct node* treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
} tNode;
treePointer root;

treePointer modifiedSearch(treePointer tree, int k); 
void insert(treePointer* node, int k, iType theItem);
element* search(treePointer root, int k);
void inorder(treePointer ptr);

void main()
{
	int seed, n, num, searchkey;
	element tmp;

	printf("random number generation <1 ~ 500>\n");
	printf("the number of nodes in BST <less than and equal to 50> : ");
	scanf("%d", &n);//��� ��

	printf("seed : ");
	scanf("%d", &seed);
	srand(seed);

	printf("\ncreating a BST from random numbers\n");
	for (int i = 0; i < n; i++) {
		num = rand() % 500 + 1;
		tmp.item = num; //key, item �����ϰ� ���
		tmp.key = num;
		insert(&root, tmp.key, tmp.item);
	}

	printf("the key to search : ");
	scanf("%d", &searchkey);
	search(root, searchkey);

	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorder(root);
	printf("\n");
}

treePointer modifiedSearch(treePointer tree, int k) 
{
	//k���� key������ ������ ��尡 �ִ��� search
	treePointer tmp=tree;
	while (tree) { //k�� tree �ȿ� �ִ��� ��� ã��
		if (k == tree->data.key)
			return NULL;
		if (k < tree->data.key) {
			tmp = tree;
			tree = tree->leftChild;
		}
		else {
			tmp = tree;
			tree = tree->rightChild;
		}
	}
	return tmp; 
	//tmp ������ k�� key������ ������ ��尡 �����ϴ�
	//��ġ�� "�θ� ���" �ּҰ� ��ȯ��
}

void insert(treePointer * node, int k, iType theItem)
{
	treePointer ptr;
	treePointer temp = modifiedSearch(*node, k);
	//modiffiesSearch�� Ʈ���� �̹� key������ k�� �����ϴ��� �˻�
	//�����ϰų� Ʈ���� �����̸� temp=NULL
	//���������� �˻��ߴµ� ���� ���� ������ 
	//���������� �˻��� ����� ������ ��ȯ

	if (temp || !(*node)) {
		//���� Ű ���� Ʈ�� �ȿ� ��� �߰� ������ ���
		//OR Ʈ���� ������ ���
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node) { //Ʈ���� ��� �̹� ����
			//temp���� ������ ����� �θ����� �ּҰ�
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else//�� Ʈ���� �� ���� ���̱�
			*node = ptr;
	}
}

element* search(treePointer root, int k)
{
	if (!root) {
		printf("there is no such an element\n\n");
		return NULL;
	}

	if (k == root->data.key) {
		printf("the element's item is %d\n\n", k);
		return &(root->data);
	}

	if (k < root->data.key)
		return search(root->leftChild, k);

	return search(root->rightChild, k);
}

void inorder(treePointer ptr)
{
	if (ptr) {
		inorder(ptr->leftChild);
		printf(" %3d", ptr->data.key);
		inorder(ptr->rightChild);
	}
}