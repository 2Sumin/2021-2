#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
} listNode;
listPointer first = NULL;
listPointer x = NULL;

void insert(listPointer* first, listPointer x, int num);
listPointer find(listPointer first);
void delete (listPointer* first, listPointer trail, listPointer x);
void printList(listPointer first);

int main(void)
{
	int num;
	int deletenum; //특정값 입력-노드 삭제

	MALLOC(first, sizeof(*first));
	MALLOC(x, sizeof(*x));

	for (int i = 0; i < 30; i++) {
		scanf("%d", &num);
		insert(&first, first, num);
	}
	delete(&first, NULL, first);
	printList(first);

	scanf("%d", &deletenum);

	x = first;
	while (x->link) {
		if (x->data <= deletenum)
			delete(&first, NULL, first);
		else if (x->link->data <= deletenum)
			delete(&first, x, x->link);
		else x = x->link;
	}

	printList(first); //삭제 후 출력

	free(first);
	free(x);

	return 0;
}

void insert(listPointer* first, listPointer x, int num)
{/* insert a new node with data = num into the chain
	first after node x */
	//first를 변경하기 위해 two pointer
	listPointer tmp;
	MALLOC(tmp, sizeof(*tmp));
	tmp->data = num; //새로 붙일 노드
	if (*first) {
		x = find(x); //맨 뒤에 노드 붙이기
		tmp->link = x->link; //tmp가 다음 것을 가리키게
		x->link = tmp; //이전 것(x)이 tmp를 가리키게
	}
	else { //first==NULL
		tmp->link = NULL;//tmp 말고 다른 노드 없음
		*first = tmp;//tmp 바로 앞의 노드가 *first
	}
}

void delete (listPointer* first, listPointer trail, listPointer x)
{/* delete x from the list, trail is the preceding node
	and *first is the front of the list */
	//x가 없앨 노드
	//trail: x의 앞선 노드

	//x가 첫 노드인지 아닌지에 따라 나뉨

	if (trail) //tmp 앞에 노드가 있으면
		trail->link = x->link;
	
	//삭제하려는 x가 *first가 가리키는 첫 노드이면
	//*first==x
	else //x가 첫 노드라서 앞에 연결된 노드 없으면
		//<=> *first=x라고 생각 
		//(*first가 가리키는 것과 x가 가리키는 것 같음)
		*first = (*first)->link;
	free(x);
}

void printList(listPointer first)
{//매개변수로 two pointer 아님->for문에서 옆으로 넘겨도 실제 first는 그대로
//마지막 노드의 link==NULL->for문 종료
	int cnt = 0;
	for (; first; first = first->link) { //옆으로 계속 넘어가면서 출력
		++cnt;
		if (cnt % 10 == 0)
			printf("%2d\n", first->data);
		else printf("%2d ", first->data);
	}
}

listPointer find(listPointer first)
{//연결된 노드 중 가장 마지막 노드 위치 찾기
	while (first->link != NULL)
		first = first->link;
	return first;
}
