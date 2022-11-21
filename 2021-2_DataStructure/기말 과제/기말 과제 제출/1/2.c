#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
/***************************************************************
// 자료구조응용 Lab 13. Q1. 의 소스일부를 비워둠
// - creating a binary tree(Fig. 5.16) from a postfix arithmatic expression
// - binary tree traversal: inorder (Program 5.1)
// input.txt (postfix) : AB/C*D*E+
****************************************************************/
#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

#define MAX_STACK_SIZE 100

// tree node & header
typedef struct node* treePointer;
typedef struct node
{
	char data;		// operator or operand in char type
	treePointer leftChild, rightChild;
}node;
treePointer root = NULL;

// stack
treePointer stack[MAX_STACK_SIZE];
int top = -1;
void push(treePointer item);
void stackFull();
treePointer pop();
treePointer stackEmpty();

// postfix expression 
char expr[81];

// binary tree of an arithmetic expression
typedef enum {
	lparen, rparen, plus, minus, times, divide,
	mod, and, or , not, eos, operand
} precedence;
precedence getToken(char* symbol, int* n);
treePointer createBinTree(void);

// binary tree traversals
void inorder(treePointer ptr);

int main(void)
{
	int result;
	FILE* fp;

	if ((fp = fopen("input.txt", "r")) == NULL)
	{
		fprintf(stderr, "cannot open the file");
		exit(EXIT_FAILURE);
	}

	printf("the length of input string should be less than 80\n");
	fgets(expr, 80, fp);
	printf("input string (postfix expression) : %s\n", expr);

	printf("creating its binary tree\n\n");
	root = createBinTree();

	printf("%-20s : ", "inorder traversal");
	inorder(root); 	printf("\n");

	return 0;
}

// create a binary tree from a postfix arithmetic expression
treePointer createBinTree(void)
{
	treePointer pNode;
	precedence token;
	char symbol;
	int n = 0; /* counter for the expression string */
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) {
			// operand node
			// 이 부분을 채우시오
			MALLOC(pNode, sizeof(*pNode));
			pNode->data = symbol;
			pNode->leftChild = NULL;
			pNode->rightChild = NULL;

			push(pNode); /* stack insert */
		}
		else {
			// operator node
			// 이 부분을 채우시오
			if (token == not) {
				MALLOC(pNode, sizeof(*pNode));
				pNode->data = symbol;
				pNode->rightChild = pop();
				pNode->leftChild = NULL;
			}
			else {
				MALLOC(pNode, sizeof(*pNode));
				pNode->data = symbol;
				pNode->rightChild = pop();
				pNode->leftChild = pop();
			}
			push(pNode);
		}
		token = getToken(&symbol, &n);
	}
	return pop(); /* return result, that is, root pointer */
}

// Program 3.14: Function to get a token from the input string
precedence getToken(char* symbol, int* n)
{ /* get the next token, symbol is the character representation,
	whichis returned, the tokenis represented by its enumerated value,
	which is returned inthe function name */
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
		//case '('		: return lparen;
		//case ')'		:  return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '&': return and;
	case '|': return or ;
	case'~': return not;
	case '\0': return eos;
	default: return operand; /* no error checking, default is operand */
	}
}

///////////////////// binary tree traversals //////////////////////////////

// Program 5.1 : Inorder traversal of a binary tree
void inorder(treePointer ptr)
{
	if (ptr)
	{
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}

/////////////////////// stack operations ///////////////////////////////////
treePointer pop()
{/* delete and return the top int from the stack */
	if (top == -1)
		return stackEmpty();	/* returns an error key */
	return stack[top--];
}

treePointer stackEmpty()
{
	treePointer item;
	item = NULL;  // error key value - null pointer
	return item;
}

void push(treePointer item)
{/* add an item to the global stack */
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}

void stackFull()
{
	fprintf(stderr, "stack is full, cannot add item\n");
	exit(EXIT_FAILURE);
}
