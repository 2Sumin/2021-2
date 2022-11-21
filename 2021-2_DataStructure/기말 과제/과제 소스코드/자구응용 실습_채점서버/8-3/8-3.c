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
//헤더노드의 llink) 연결된 마지막 노드의 주소
//헤더노드의 rlink) 연결된 첫번째 노드의 주소
//연결된 첫번째 노드의 llink) 헤더노드
//연결된 첫번째 노드의 rlink) 헤더노드 


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

    for (int i = 0; i < 30; i++) { //30개 입력
        scanf("%d", &data);
        MALLOC(tmp, sizeof(*tmp));
        dinsertList(header->llink, tmp, data);
    }

    printList(header); //순방향
    invertPrint(header); //역방향

    scanf("%d", &delNum);
    List = header->rlink;
    ddeleteList(delNum, List);

    printList(header); //삭제 후 순방향
    invertPrint(header); //삭제 후 역방향

    return 0;
}

void dinsert(nodePointer node, nodePointer newnode)
{/* insert newnode to the right of node */
    //node는 newnode 왼쪽 (바로 전)노드
    //newnode 의 llink에 삽입 전 위치 노드 주소
    //           rlink에  삽입 후 위치 노드 주소 넣기
    newnode->llink = node;
    newnode->rlink = node->rlink;
    //ptr=ptr->llink->rlink=ptr->rlink->llink 이용 
    node->rlink->llink = newnode; //newnode 바로 다음 노드의 llink에 newnode 연결
    node->rlink = newnode; //newnode 바로 전 노드의 rlink에 newnode 연결
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
        //삭제노드 앞노드의 rlink에 삭제노드 뒷노드 주소
        deleted->llink->rlink = deleted->rlink;
        //삭제노드 뒷노드의 llink에 삭제노드 앞노드 주소
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

//데이터 노드 찾는 코드
nodePointer FindNode(nodePointer pNode, int data)
{
    if (pNode == NULL)
        return NULL;
    nodePointer pFindNode = pNode;

    while (pFindNode != NULL) {//연결된 노드 없을때까지 반복
        if (pFindNode->data == data)
            return pFindNode; //찾은 노드 반환
        else
            pFindNode = pFindNode->rlink;
    }
    return NULL; //못 찾았으면 null
}

