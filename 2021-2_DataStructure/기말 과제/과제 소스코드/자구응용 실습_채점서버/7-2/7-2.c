//linked list->stack (stack ������)

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STACKS 3
#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int id;	//�й�
	int grade;	//����
} element; //node�� data
typedef struct stack* stackPointer;
typedef struct stack {
	element data; //���� ���빰
	stackPointer link;
} Node;
stackPointer top[MAX_STACKS];
//Node���� ������ �� �ϳ��� ������ �̷�
//stackPointer top ������ 1���� ������ ����Ŵ (�� MAX_STACKS��)
//top[i]�� ����[i]�� ���� ���� ���(������ ����)�� ����Ŵ

void push(int i, element item);
element pop(int i);
element stackEmpty();

int main(void)
{
	int stacknum, id_, grade_;
	element item;
	while (1) {
		scanf("%d %d %d", &stacknum, &id_, &grade_);
		if (stacknum == 0 && id_ == 0 && grade_ == 0)
			break; //���� �Է� ����
		item.id = id_;
		item.grade = grade_;
		switch (stacknum) {
		case 0:
			push(0, item);
			break;
		case 1:
			push(1, item);
			break;
		case 2:
			push(2, item);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 3; i++) {
		while (top[i]) { //ith ���ÿ� ���� ������
			item = pop(i);
			printf("%d %d %2d\n", i, item.id, item.grade);
		}
	}

	return 0;
}


void push(int i, element item)
{/* add item to the ith stack */
	
 //i=top�� index, item�� ���� ���� ���(temp)�� ���� data����
	//temp�� ���� �Է� �� ���� ���� �����ϰ� top[i]�� ���� �ø���
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top[i]; //������ top�̾��� ���� ����Ű��
	//(temp�� ������ top[i]���� ���̱�)
	top[i] = temp; // temp�� top����
}

element pop(int i)
{/* remove top element from the ith stack */
	stackPointer temp = top[i]; //�̾Ƴ� Node
	element item;
	if (!temp) //top[i]�� ���� ��������(����Ű�� ��尡 �ִ���)
		return stackEmpty();
	item = temp->data; //�� ������
	top[i] = temp->link; //temp ���ְ� top[i] �Ʒ��� ������
	free(temp);
	return item;
}

element stackEmpty()
{
	exit(EXIT_FAILURE);
	element empty;
	empty.id = -1;
	return empty;
}