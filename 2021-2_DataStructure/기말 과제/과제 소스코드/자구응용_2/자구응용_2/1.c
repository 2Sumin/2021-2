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
	scanf("%d", &n);//노드 수

	printf("seed : ");
	scanf("%d", &seed);
	srand(seed);

	printf("\ncreating a BST from random numbers\n");
	for (int i = 0; i < n; i++) {
		num = rand() % 500 + 1;
		tmp.item = num; //key, item 동일하게 사용
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
	//k값을 key값으로 가지는 노드가 있는지 search
	treePointer tmp=tree;
	while (tree) { //k가 tree 안에 있는지 계속 찾기
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
	//tmp 값으로 k를 key값으로 가지는 노드가 들어가야하는
	//위치의 "부모 노드" 주소가 반환됨
}

void insert(treePointer * node, int k, iType theItem)
{
	treePointer ptr;
	treePointer temp = modifiedSearch(*node, k);
	//modiffiesSearch로 트리에 이미 key값으로 k가 존재하는지 검사
	//존재하거나 트리가 공백이면 temp=NULL
	//마지막까지 검사했는데 같은 값이 없으면 
	//마지막으로 검사한 노드의 포인터 반환

	if (temp || !(*node)) {
		//같은 키 값이 트리 안에 없어서 추가 가능한 경우
		//OR 트리가 공백인 경우
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;

		if (*node) { //트리에 노드 이미 존재
			//temp에는 삽입할 노드의 부모노드의 주소값
			if (k < temp->data.key)
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;
		}
		else//빈 트리면 젤 위에 붙이기
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