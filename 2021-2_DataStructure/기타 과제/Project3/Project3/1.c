#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(1);\
   }
#define COMPARE(x,y) (((x)<(y))?-1:((x)==(y))?0:1)


typedef struct polyNode* polyPointer;

typedef struct polyNode {
    int coef;
    int expon;
    polyPointer link;
} polyNode;

polyPointer a, b;
polyPointer c, lastA, lastB, avail = NULL;

void erase(polyPointer*);
polyPointer getNode();
void retNode(polyPointer);
void cerase(polyPointer*);
polyPointer cpadd(polyPointer, polyPointer);
void attach(float, int, polyPointer*);
polyPointer inputPolyCL(polyPointer, char input[]);
void printCList(polyPointer);
void insertFront2(polyPointer*, polyPointer);
void insertLast(polyPointer*, polyPointer);


int main()
{
    char input[100];

    lastA = getNode();
    lastB = getNode();


    a = lastA;
    a->coef = 0;
    a->expon = -1;
    a->link = a;

    b = lastB;
    b->coef = 0;
    b->expon = -1;
    b->link = b;

    gets(input);
    lastA = inputPolyCL(lastA, input);


    gets(input);
    lastB = inputPolyCL(lastB, input);

    c = cpadd(a, b);

    printCList(c);

    cerase(&a); cerase(&b); cerase(&c);
    erase(&avail);

    return 0;
}

polyPointer inputPolyCL(polyPointer last, char input[])
{
    int coef = 0;
    int expo = 0;
    char inpu = '\0';

    polyPointer tmp = getNode();

    char inputt[100];

    strcpy(inputt, input);
    inpu = input[0];

    int num = 0;
    char* token = strtok(inputt, " ");
    for (int i = 0; i < strlen(input); i++)
        if (token[i])
            ++num;
    num -= 1;
    int inport;
    inport = num / 2;
    inport /= 2;


    if (inpu == 'a')
    {

        for (int i = 0; i < inport; i++) {
            token = strtok(NULL, " ");
            coef = atoi(token);
            token = strtok(NULL, " ");
            expo = atoi(token);
            attach(coef, expo, &tmp);
            insertFront2(&last, tmp);
        }
    }

    else if (inpu == 'd')
    {
        for (int i = 0; i < inport; i++)
        {
            token = strtok(NULL, " ");
            coef = atoi(token);

            token = strtok(NULL, " ");
            expo = atoi(token);

            attach(coef, expo, &tmp);
            insertLast(&last, tmp);
        }
    }
    return last;
}

polyPointer getNode()
{
    polyPointer node;
    if (avail) {
        node = avail;
        avail = avail->link;
    }
    else
        MALLOC(node, sizeof(*node));

    return node;
}

void attach(float coefficient, int exponent, polyPointer* ptr)
{
    polyPointer temp;
    temp = getNode();
    temp->coef = coefficient;
    temp->expon = exponent;
    (*ptr)->link = temp;
    *ptr = temp;
}

void erase(polyPointer* ptr)
{
    polyPointer temp;
    while (*ptr) {
        temp = *ptr;
        *ptr = (*ptr)->link;
        free(temp);
    }
}

void retNode(polyPointer node)
{
    node->link = avail;
    avail = node;
}

void cerase(polyPointer* ptr)
{
    polyPointer tmp;
    if (*ptr) {
        tmp = (*ptr)->link;
        (*ptr)->link = avail;
        avail = tmp;
        *ptr = NULL;
    }
}

void insertLast(polyPointer* last, polyPointer node)
{
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
void insertFront2(polyPointer* last, polyPointer node)
{
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
polyPointer cpadd(polyPointer a, polyPointer b)
{
    polyPointer startA, c, lastC;
    int sum, done = FALSE;
    startA = a;
    a = a->link;
    b = b->link;
    c = getNode();
    c->expon = -1; lastC = c;
    do {
        switch (COMPARE(a->expon, b->expon)) {
        case -1:
            attach(b->coef, b->expon, &lastC);
            b = b->link;
            break;
        case 0:
            if (startA == a) done = TRUE;
            else {
                sum = a->coef + b->coef;
                if (sum) attach(sum, a->expon, &lastC);
                a = a->link; b = b->link;
            }
            break;
        case 1:
            attach(a->coef, a->expon, &lastC);
            a = a->link;
            break;
        }
    } while (!done);
    lastC->link = c;
    return c;
}