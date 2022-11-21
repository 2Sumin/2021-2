//����2���� linked list�� Ȱ���� Queue�� Ǯ��ÿ�
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_QUEUES 3
#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int id;	//�й�
	int grade;	//����
} element;
typedef struct queue* queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
} Node;
queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void addq(int i, element item);
element deleteq(int i);
element queueEmpty();

int main(void)
{
	int queuenum, id_, grade_;
	element item;
	while (1) {
		scanf("%d %d %d", &queuenum, &id_, &grade_);
		if (queuenum == 0 && id_ == 0 && grade_ == 0)
			break; //���� �Է� ����
		item.id = id_;
		item.grade = grade_;
		switch (queuenum) {
		case 0:
			addq(0, item);
			break;
		case 1:
			addq(1, item);
			break;
		case 2:
			addq(2, item);
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < 3; i++) {
		while (front[i]) {
			item = deleteq(i);
			printf("%d %d %2d\n", i, item.id, item.grade);
		}
	}

	return 0;
}

//ť�� ���� �ִ� �� ���� �� -> ���� ���� rear��, �� ���� front��
void addq(int i, element item)
{/* add item to the rear of queue i */
	//�߰��� ��� ����
	queuePointer tmp; 
	MALLOC(tmp, sizeof(*tmp));
	tmp->data = item;
	tmp->link = NULL;
	//����ִ� �� �ƴϸ�
	if (front[i])
		rear[i]->link = tmp;
	//ť�� ����ִ� ���¸�
	else //addition to empty queue
		front[i] = tmp;
	rear[i] = tmp; //rear �о��ֱ� (tmp�� ������ ����)
}

element deleteq(int i)
{ /* delete an element from queue i */
	queuePointer tmp = front[i];
	element item;
	if (!tmp)
		return queueEmpty();
	item = tmp->data;
	front[i] = tmp->link;
	free(tmp);
	return item;
}

element queueEmpty()
{
	exit(EXIT_FAILURE);
	element empty;
	empty.id = -1;
	return empty;
}