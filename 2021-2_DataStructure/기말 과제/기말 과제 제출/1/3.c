#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
    int key;
} element;
element heap[MAX_ELEMENTS];
int n = 0;

void push(element item, int* n); //heap에 원소 삽입
element pop(int* n); //heap의 가장 큰 원소 삭제
void Print(int* n); //heap에 들어있는 것 출력

int main(void)
{
    element num,del;
    FILE* fp = fopen("input.txt", "r");
    printf("***** insertion into a max heap *****\n");
    while (!feof(fp)) {
        fscanf(fp, "%d ", &num.key);
        push(num, &n);//maxheap에 넣기
        Print(&n);//maxheap출력
    }
    printf("***** deletion from a max heap *****\n");
    while (heap) {
        del = pop(&n);//제일 큰 원소 없애고 
        Print(&n);//남은 heap 출력
    }

    return 0;
}

void push(element item, int* n) //n은 heap 내 원소의 수
{
    int i;
    if (HEAP_FULL(*n)) {
        fprintf(stderr,"The heap is full.\n");
        exit(EXIT_FAILURE);
    }
    i = ++(*n); //인덱스는 1부터 시작
    //n에 1을 더함->i는 원소의 수+1
    // \\새로 들어오는 원소를 넣을 빈 공간까지 확보한 상태의 노드 수가 i
   
    //i가 1이면 n은 0이었다->힙 안에 들어있는 게 없었다
    //->그냥 바로 heap[1]=item(whileX)
      
    //인덱스를 2로 나누면(i/2) 부모노드를 가리킴
    //heap[i/2]와 넣으려는 값(item) 비교해서 
    //\\maxheap은 클수록 위에가니까
    //넣으려는 값이 부모노드보다 더 크면
    //원래 부모노드에 있던 값을 밑에 새로 생긴 노드로 밀고
    //item값을 비교하던 부모노드의 부모노드와 비교(i/=2)
    //그 후 제자리를 찾을 때까지 그 위의 부모노드와 또 비교
    while ((i != 1) && (item.key > heap[i / 2].key)) {
        heap[i] = heap[i / 2]; //부모노드를 아래로 내리고
        i /= 2;//복합대입연산자->원본값(i) 수정됨 -> 계속 위로 올라가기
    }
    //item값이 부모노드보다 더 작으면 바로 item 넣기
    heap[i] = item; //조정된 i 위치에 값을 넣는다
}

element pop(int* n)
{
    int parent, child;
    element item, temp;
    if (HEAP_EMPTY(*n)) {
        //fprintf(stderr, "The heap is empty.\n");
        exit(EXIT_FAILURE);
    }
    //item에 루트 노드, temp에 제일 끝의 노드 넣기

    item = heap[1]; //제일 위의(root) 값 item에 넣기(빼내기)
    temp = heap[(*n)--]; //제일 마지막 노드 위치 이동
    //후위연산->처음에는 n값을 그대로 하고 그 다음에 빼기
    //temp에 마지막 노드의 값을 넣은 후 원소의 수(*n)을 1 빼기
    parent = 1; //\\빈 공간이 항상 parent
    child = 2; //child+1=그 옆의 자식노드
    //root 를 빼주면 그 빈자리를 메우고, 다시 또 그 빈자리를 메우면서
    // 재배치하기 위해 while문 돌림
    
    //자식 둘 중 더 큰 것 위로 올리기
    while (child <= *n) {
        //child와 그 옆의 자식(형제노드)와 temp를 비교
        //if문에서 child<*n 이유는 child==*n이면 오른쪽 (형제)자식노드 없이
        //그 child가 트리의 마지막 노드->형제끼리 비교할 필요 없음
        //->첫번째 if문 그냥 넘어가기
        if ((child < *n) && (heap[child].key < heap[child + 1].key))
            child++; //자식이 두명 있을 때&& 둘 중 더 큰 자식이 child
        if (temp.key >= heap[child].key) break;
        //temp의 값보다 child의 값이 더 크면 child를 위로 올리기
        //제일 첫 단계에서는 chlld의 값이 temp보다 크겠지만
        //계속 진행하다 보면 temp보다 작은 child가 생김
        heap[parent] = heap[child];
        parent = child; //원래있던 child를 그 위의 부모 자리로 넣어서
        //child자리가 빈 자리니까 거기를 parent로 재설정해서
        //처음 과정 다시 진행
        child *= 2; //왼쪽 자식노드를 child로 재설정
    }
    heap[parent] = temp; //temp를 child에 넣기
    return item;
}

void Print(int* n)
{
    for (int i = 1; i <= *n; i++) 
        printf(" %2d", heap[i]);
    printf("\n");
}
