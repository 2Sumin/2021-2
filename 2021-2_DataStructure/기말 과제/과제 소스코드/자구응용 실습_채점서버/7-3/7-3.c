//문제2번을 linked list를 활용한 Queue로 풀어보시오
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
	int id;	//학번
	int grade;	//성적
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
			break; //서버 입력 종료
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

//큐는 먼저 넣는 거 먼저 뺌 -> 넣을 때는 rear로, 뺄 때는 front로
void addq(int i, element item)
{/* add item to the rear of queue i */
	//추가할 노드 생성
	queuePointer tmp; 
	MALLOC(tmp, sizeof(*tmp));
	tmp->data = item;
	tmp->link = NULL;
	//비어있는 게 아니면
	if (front[i])
		rear[i]->link = tmp;
	//큐가 비어있는 상태면
	else //addition to empty queue
		front[i] = tmp;
	rear[i] = tmp; //rear 밀어주기 (tmp를 마지막 노드로)
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