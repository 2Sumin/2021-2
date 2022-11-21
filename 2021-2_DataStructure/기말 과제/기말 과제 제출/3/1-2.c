#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct node* tListNodePointer;
typedef struct node {
	char data;
	tListNodePointer link;
} tListNode;
tListNodePointer head = NULL;

tListNodePointer createNode(char data);
tListNodePointer invert(tListNodePointer lead);
tListNodePointer initList(char* str);
void printLinkedList(tListNodePointer ptr);
tListNodePointer copyNode(tListNodePointer lead);
int isPalindrome(tListNodePointer head);

int main(void)
{
	char str[100];
	printf("Enter the string to check palindrome: ");
	gets(str);

	head = initList(str);

	int pal = isPalindrome(head);

	if (pal == 1)
		printf("%s is palindrome\n", str);
	else if (!pal)
		printf("%s is not palindrome\n", str);

	return 0;
}

tListNodePointer createNode(char data)
{
	tListNodePointer newnode;
	MALLOC(newnode, sizeof(*newnode));
	newnode->data = data;
	newnode->link = NULL;
	return newnode;
}

tListNodePointer invert(tListNodePointer lead)
{
	tListNodePointer middle, trail;
	middle = NULL;
	while (lead) {
		trail = middle;
		middle = lead;
		lead = lead->link;
		middle->link = trail;
	}
	return middle;
}

tListNodePointer initList(char* str)
{//�ڿ� �����ϱ�
	tListNodePointer newNode, lead, tmp;
	int i = 0;
	lead = createNode(str[i]);
	for (str[++i]; str[i]; i++) {
		newNode = createNode(str[i]);
		//tmp�� newNode �ٷ� �� ���
		tmp = lead;
		while (tmp->link)
			tmp = tmp->link;
		//tmp �ڿ� newNode ����
		tmp->link = newNode;
	}
	return lead;
}

void printLinkedList(tListNodePointer ptr)
{
	while (ptr) {
		printf("%c ", ptr->data);
		ptr = ptr->link;
	}
	printf("\n");
}

tListNodePointer copyNode(tListNodePointer lead)
{//lead�� copyLead�� ����
	tListNodePointer copyLead = createNode(lead->data);
	//ù��° ������ ����
	lead = lead->link;
	tListNodePointer newNode, tmp;
	while (lead) {
		newNode = createNode(lead->data);
		//tmp�� ���� ������ ��� �ٷ� �� ���
		tmp = copyLead;
		while (tmp->link)
			tmp = tmp->link;
		//tmp �ڿ� newNode ����
		tmp->link = newNode;
		lead = lead->link;
	}
	return copyLead;
}

int isPalindrome(tListNodePointer head)
{
	tListNodePointer tmp, copyHead, inv;

	printf("initial linked list : ");
	printLinkedList(head);

	copyHead = copyNode(head);

	inv = invert(copyHead);
	printf("inverted linked list: ");
	printLinkedList(inv);

	while (head && inv) {
		//���� ���Ḯ��Ʈ(inv)�� ������ �ϳ��� �ٸ��� ȸ�� �ƴ�
		if (head->data != inv->data)
			return 0;
		//���� ��� ��
		head = head->link;
		inv = inv->link;
	}
	//while�� ��� ��������� ȸ��
	return 1;
}