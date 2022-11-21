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
	int deletenum; //Ư���� �Է�-��� ����

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

	printList(first); //���� �� ���

	free(first);
	free(x);

	return 0;
}

void insert(listPointer* first, listPointer x, int num)
{/* insert a new node with data = num into the chain
	first after node x */
	//first�� �����ϱ� ���� two pointer
	listPointer tmp;
	MALLOC(tmp, sizeof(*tmp));
	tmp->data = num; //���� ���� ���
	if (*first) {
		x = find(x); //�� �ڿ� ��� ���̱�
		tmp->link = x->link; //tmp�� ���� ���� ����Ű��
		x->link = tmp; //���� ��(x)�� tmp�� ����Ű��
	}
	else { //first==NULL
		tmp->link = NULL;//tmp ���� �ٸ� ��� ����
		*first = tmp;//tmp �ٷ� ���� ��尡 *first
	}
}

void delete (listPointer* first, listPointer trail, listPointer x)
{/* delete x from the list, trail is the preceding node
	and *first is the front of the list */
	//x�� ���� ���
	//trail: x�� �ռ� ���

	//x�� ù ������� �ƴ����� ���� ����

	if (trail) //tmp �տ� ��尡 ������
		trail->link = x->link;
	
	//�����Ϸ��� x�� *first�� ����Ű�� ù ����̸�
	//*first==x
	else //x�� ù ���� �տ� ����� ��� ������
		//<=> *first=x��� ���� 
		//(*first�� ����Ű�� �Ͱ� x�� ����Ű�� �� ����)
		*first = (*first)->link;
	free(x);
}

void printList(listPointer first)
{//�Ű������� two pointer �ƴ�->for������ ������ �Ѱܵ� ���� first�� �״��
//������ ����� link==NULL->for�� ����
	int cnt = 0;
	for (; first; first = first->link) { //������ ��� �Ѿ�鼭 ���
		++cnt;
		if (cnt % 10 == 0)
			printf("%2d\n", first->data);
		else printf("%2d ", first->data);
	}
}

listPointer find(listPointer first)
{//����� ��� �� ���� ������ ��� ��ġ ã��
	while (first->link != NULL)
		first = first->link;
	return first;
}
