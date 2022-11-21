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
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)
#define TRUE 1
#define FALSE 0

typedef struct polyNode* polyPointer;
typedef struct polyNode {
    int coef;//계수
    int expon;//지수
    polyPointer link;
} polyNode;
polyPointer a, b;
polyPointer c, lastA, lastB, avail = NULL;

void erase(polyPointer* ptr);
polyPointer getNode(); //빈 노드를 할당받고 그 메모리 주소값 반환
void retNode(polyPointer node);
void cerase(polyPointer* ptr);
polyPointer cpadd(polyPointer a, polyPointer b);

polyPointer inputPolyCL(polyPointer last, char input[]);
void printCList(polyPointer ptr);
void insertFront2(polyPointer* last, polyPointer node); //오름차순 입력
void insertLast(polyPointer* last, polyPointer node); //내림차순 입력
void attach(float coefficient, int exponent, polyPointer* ptr);

int main(void)
{
    char input[30];
    lastA = getNode();
    lastB = getNode();

    //헤더노드
    a = lastA; a->coef = 0; a->expon = -1; a->link = a;
    b = lastB; b->coef = 0; b->expon = -1; b->link = b;

    gets(input);
    lastA = inputPolyCL(lastA, input);
    //printf("A list print: ");
    //printCList(a);
    //printf("\n\n");

    gets(input);
    lastB = inputPolyCL(lastB, input);
    //printf("B list print: ");
    //printCList(b);
    //printf("\n\n");

    c = cpadd(a, b);

    printCList(c);

    cerase(&a);
    cerase(&b);
    cerase(&c);
    erase(&avail);

    return 0;
}

polyPointer inputPolyCL(polyPointer last, char input[30])
{
    int co = 0, ex = 0;
    char order = '\0'; //오름차순 내림차순
    char enter = '\0';
    int i = 0;
    polyPointer tmp = getNode();

    char inputc[30];

    strcpy(inputc, input);
    order = input[0];

    int cnt = 0; //��의 수
    char* tok = strtok(inputc, " ");
    for (int i = 0; i < strlen(input); i++)
        if (tok[i])
            ++cnt;
    cnt -= 1;
    int repeat = cnt / 2;
    repeat /= 2;
    //printf("항의 수:%d\n", repeat);

    if (order == 'a') {
        for (i = 0; i < repeat; i++) {
            tok = strtok(NULL, " ");
            co = atoi(tok);
            tok = strtok(NULL, " ");
            ex = atoi(tok);
            attach(co, ex, &tmp);
            insertFront2(&last, tmp);
        }
    }

    else if (order == 'd') {
        for (i = 0; i < repeat; i++) {
            tok = strtok(NULL, " ");
            co = atoi(tok);
            tok = strtok(NULL, " ");
            ex = atoi(tok);
            attach(co, ex, &tmp);
            insertLast(&last, tmp);
        }
    }

    //printf("입력 종료\n");

    return last;
}

polyPointer getNode() //MALLOC->빈 노드 하나씩 만들기
{/* provide a node for use */
    polyPointer node;
    if (avail) { //avail에 노드가 있으면 받아옴
        //제일 앞의 노드 가져가서 쓰니까 avail이 가리키는 거 옆으로 밀기
        node = avail;
        avail = avail->link;
    }
    else //avail: isempty->노드 새로 만들기
        MALLOC(node, sizeof(*node));
    return node; //avail에서 제일 앞의 노드 떼오기
}

void retNode(polyPointer node) //free 
{/* return a node to the available list */
    //노드 가져와서 avail 앞에 붙인 후
    //avail의 제일 앞 노드를 가져온 node로 변경
    node->link = avail;
    avail = node;  //지정된 노드를 avail로 반환
}

void attach(float coefficient, int exponent, polyPointer* ptr)
{/* create a new node with coef=coefficient
   and expon=exponent, attach it to the node pointed to by ptr.
   ptr is updated to point to this new node */
    //attach된 걸 avail에 넣기
    //ptr이 가리키는 노드 다음에 tmp 집어넣은 후
    //ptr이 마지막 노드인 tmp를 가리키도록 변경
    polyPointer tmp;
    tmp = getNode(); //tmp는 avail 다음 노드
    tmp->coef = coefficient;
    tmp->expon = exponent;
    //addq 할 때와 비슷, *ptr==rear
    (*ptr)->link = tmp; //ptr이 &firstC이면 제일 처음 노드
    *ptr = tmp; //ptr이 &lastC이면 tmp가 avail의 제일 끝 노드
}

void erase(polyPointer* ptr)
{/* erase the polynomial pointed to by ptr */
    //ptr이 가리키는 "노드 하나" 삭제
    polyPointer tmp; //지우기용
    while (*ptr) {
        tmp = *ptr; //지울 꺼
        *ptr = (*ptr)->link; //다음 노드 가리킨 후
        free(tmp);
    }
}

void cerase(polyPointer* ptr) //원형리스트 제거 (a,b,c)
{/* erase the circular list pointed to by ptr */
    //avail에 원형리스트 붙여서 제거
    //원형리스트 ptr이 avail로 넘어감
    polyPointer tmp;
    if (*ptr) {
        tmp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = tmp;
        *ptr = NULL; 
    }
}

polyPointer cpadd(polyPointer a, polyPointer b)
{/* polynomials a and b are singly linked circular lists
 with a header node. Return a polynomial which is
 the sum of a and b */
    //a+b 를 avail에 넣는 게 목적
    polyPointer startA, c, lastC;
    int sum, done = FALSE;
    startA = a; //나중에 한 바퀴 돈 거 확인용. startA는 헤더노드
    a = a->link; //skip header node for a and b (제일 앞 노드는 header)
    b = b->link;
    c = getNode(); //avail=NULL인 상태에서 시작. get a header node for sum
    c->expon = -1; lastC = c; //header node의 expon=-1, c=header node
    //c와 lastC가 같은데 따로 c를 만드는 이유
    //: lastC가 기존에 가리키던 헤더노드를 삭제하기 위해
    do { //처음 시행되는 거는 header node 뒤에 붙임
        switch (COMPARE(a->expon, b->expon)) {
            //compare를 하므로 둘 중 하나만 먼저 끝났으면 case 0으로
            //들어갈 수 없음
            // 하나가 계산이 완료되어서 expon=-1이 되어도
            // 나머지 하나가 전부 계산될 때까지 종료 안 됨
            //둘 다 한 바퀴 돌아서 expon==-1이 돼서야
            //(startA==a) 인지 검사 가능
        case -1: /* a->expon < b->expon */
            attach(b->coef, b->expon, &lastC); //lastC가 가리키는 노드 아래로
            b = b->link;
            break;
        case 0: /* a->expon == b->expon */
            if (startA == a) done = TRUE; //a,b의 expon이 둘 다 -1
            else {
                sum = a->coef + b->coef;
                if (sum) attach(sum, a->expon, &lastC);
                a = a->link; b = b->link;
            }
            break;
        case 1: /* a->expon > b->expon */
            attach(a->coef, a->expon, &lastC);
            a = a->link;
            break;
        }
    } while (!done);
    lastC->link = c;//lastC와 c 이어서 원형리스트 형성
    return c;
}

void insertFront2(polyPointer* last, polyPointer node)
{
    polyPointer tmp = getNode();
    tmp->coef = node->coef;
    tmp->expon = node->expon;

    if (!(*last)) {//아무것도 없는 상태면 그냥 붙이기
        *last = tmp; //tmp를 리스트에 넣고
        tmp->link = tmp; //원형 리스트니까 한 바퀴 돌리기
    }
    else { 
        //(*last)->link는 첫번째 노드
        tmp->link = (*last)->link; //tmp를 첫 번째 노드 앞에 붙이고 
        (*last)->link = tmp; //원형 리스트니까 마지막 노드랑 tmp붙이기
    }
}

void insertLast(polyPointer* last, polyPointer node)
{
    //insertFront2와 같은 구조인데 *last가 가리키는 것만 변경
    polyPointer tmp = getNode();
    tmp->coef = node->coef;
    tmp->expon = node->expon;

    if (!(*last)) {
        *last = tmp;
        tmp->link = tmp;
    }
    else {
        tmp->link = (*last)->link;
        (*last)->link = tmp;
        *last = tmp; 
    }

}

void printCList(polyPointer ptr)
{
    polyPointer tmp = ptr->link;
    while (tmp->link != ptr) {
        printf("%d %d ", tmp->coef, tmp->expon);
        tmp = tmp->link;
    }
    printf("%d %d", tmp->coef, tmp->expon);
}
