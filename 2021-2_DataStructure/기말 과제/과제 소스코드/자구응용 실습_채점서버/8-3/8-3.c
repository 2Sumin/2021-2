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

typedef struct node* nodePointer;
typedef struct node {
    nodePointer llink;
    int data;
    nodePointer rlink;
} node;
nodePointer header = NULL;
nodePointer newnode;
//�������� llink) ����� ������ ����� �ּ�
//�������� rlink) ����� ù��° ����� �ּ�
//����� ù��° ����� llink) ������
//����� ù��° ����� rlink) ������ 


void dinsert(nodePointer node, nodePointer newnode);
void dinsertList(nodePointer node, nodePointer newnode, int data);
void ddelete(nodePointer node, nodePointer deleted);
void ddeleteList(int delNum, nodePointer list);
void printList(nodePointer node);
void invertPrint(nodePointer node);

int main(void)
{
    nodePointer List = NULL, tmp = NULL;
    int data, delNum;

    MALLOC(header, sizeof(*header));
    header->rlink = header;
    header->llink = header;

    for (int i = 0; i < 30; i++) { //30�� �Է�
        scanf("%d", &data);
        MALLOC(tmp, sizeof(*tmp));
        dinsertList(header->llink, tmp, data);
    }

    printList(header); //������
    invertPrint(header); //������

    scanf("%d", &delNum);
    List = header->rlink;
    ddeleteList(delNum, List);

    printList(header); //���� �� ������
    invertPrint(header); //���� �� ������

    return 0;
}

void dinsert(nodePointer node, nodePointer newnode)
{/* insert newnode to the right of node */
    //node�� newnode ���� (�ٷ� ��)���
    //newnode �� llink�� ���� �� ��ġ ��� �ּ�
    //           rlink��  ���� �� ��ġ ��� �ּ� �ֱ�
    newnode->llink = node;
    newnode->rlink = node->rlink;
    //ptr=ptr->llink->rlink=ptr->rlink->llink �̿� 
    node->rlink->llink = newnode; //newnode �ٷ� ���� ����� llink�� newnode ����
    node->rlink = newnode; //newnode �ٷ� �� ����� rlink�� newnode ����
}

void dinsertList(nodePointer node, nodePointer newnode, int data)
{
    newnode->data = data;

    if (header->llink == header) {
        header->llink = newnode;
        header->rlink = newnode;
        newnode->llink = header;
        newnode->rlink = header;
    }

    else if (header->llink->llink == header) {
        header->llink = newnode;
        node->rlink = newnode;
        newnode->rlink = header;
        newnode->llink = node;
    }

    else
        dinsert(node, newnode);
}

void ddelete(nodePointer node, nodePointer deleted)
{/* delete from the doubly linked list */
    if (node == deleted)
        printf("Deletion of header node not permitted.\n");
    else {
        //������� �ճ���� rlink�� ������� �޳�� �ּ�
        deleted->llink->rlink = deleted->rlink;
        //������� �޳���� llink�� ������� �ճ�� �ּ�
        deleted->rlink->llink = deleted->llink;
        free(deleted);
    }
}

void ddeleteList(int delNum, nodePointer list)
{
    nodePointer x = NULL, tmp;
    tmp = list;

    while (tmp->rlink != header) {
        if (delNum >= tmp->data) {
            x = tmp;
            tmp = tmp->rlink;
            ddelete(header, x);
        }
        else
            tmp = tmp->rlink;
    }
}

void printList(nodePointer node)
{
    nodePointer tmp;
    int cnt = 0;
    tmp = node;
    tmp = tmp->rlink;
    while (tmp != header) {
        ++cnt;
        if (cnt % 10 == 0 && cnt > 0)
            printf("%2d\n", tmp->data);
        else if (tmp->rlink == header)
            printf("%2d", tmp->data);
        else printf("%2d ", tmp->data);
        tmp = tmp->rlink;
    }
    if (cnt % 10)
        printf("\n");
}

void invertPrint(nodePointer node)
{
    nodePointer tmp;
    int cnt = 0;
    tmp = node;
    tmp = tmp->llink;
    while (tmp != header) {
        ++cnt;
        if (cnt % 10 == 0 && cnt > 0)
            printf("%2d\n", tmp->data);
        else if (tmp->llink == header)
            printf("%2d", tmp->data);
        else printf("%2d ", tmp->data);
        tmp = tmp->llink;
    }
    if (cnt % 10)
        printf("\n");
}

//������ ��� ã�� �ڵ�
nodePointer FindNode(nodePointer pNode, int data)
{
    if (pNode == NULL)
        return NULL;
    nodePointer pFindNode = pNode;

    while (pFindNode != NULL) {//����� ��� ���������� �ݺ�
        if (pFindNode->data == data)
            return pFindNode; //ã�� ��� ��ȯ
        else
            pFindNode = pFindNode->rlink;
    }
    return NULL; //�� ã������ null
}

