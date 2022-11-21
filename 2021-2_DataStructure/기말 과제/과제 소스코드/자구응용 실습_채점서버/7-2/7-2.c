//linked list->stack (stack 여러개)

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
	int id;	//학번
	int grade;	//성적
} element; //node의 data
typedef struct stack* stackPointer;
typedef struct stack {
	element data; //스택 내용물
	stackPointer link;
} Node;
stackPointer top[MAX_STACKS];
//Node들이 여러개 모여 하나의 스택을 이룸
//stackPointer top 각각이 1개의 스택을 가리킴 (총 MAX_STACKS개)
//top[i]은 스택[i]의 가장 위의 노드(스택의 원소)를 가리킴

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
			break; //서버 입력 종료
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
		while (top[i]) { //ith 스택에 값이 있으면
			item = pop(i);
			printf("%d %d %2d\n", i, item.id, item.grade);
		}
	}

	return 0;
}


void push(int i, element item)
{/* add item to the ith stack */
	
 //i=top의 index, item은 새로 만든 노드(temp)에 넣을 data영역
	//temp에 정보 입력 후 제일 위에 연결하고 top[i]를 위로 올리기
	stackPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = item;
	temp->link = top[i]; //기존의 top이었던 것을 가리키기
	//(temp를 기존의 top[i]위에 붙이기)
	top[i] = temp; // temp를 top으로
}

element pop(int i)
{/* remove top element from the ith stack */
	stackPointer temp = top[i]; //뽑아낼 Node
	element item;
	if (!temp) //top[i]가 값을 가지는지(가리키는 노드가 있는지)
		return stackEmpty();
	item = temp->data; //값 빼내기
	top[i] = temp->link; //temp 없애고 top[i] 아래로 내리기
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