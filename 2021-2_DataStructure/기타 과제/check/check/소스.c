#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{

    char input[30],inputc[30];
    gets(input);
    strcpy(inputc, input);

    int cnt = 0; //항의 수

    char* tok = strtok(inputc, " ");
    printf("tok: %s\n", tok);

    for (int i = 0; i < strlen(input); i++)
        if (input[i]!=" ")
            ++cnt;

    printf("strlen(input)=%d\n", strlen(input));
    printf("strlen(inputc)=%d\n", strlen(inputc));
    tok = strtok(NULL, " ");
    printf("%s\n", tok);
    tok = strtok(NULL, " ");
    printf("%s\n", tok);
    tok = strtok(NULL, " ");
    printf("%s\n", tok);

    printf("cnt=%d\n", cnt);
    cnt -= 1;
    int repeat = cnt / 2;
    repeat /= 2;
    printf("항의 수: %d", repeat);
}