#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define NAME_SIZE 30

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int key;
	char name[NAME_SIZE];
	int grade;
}element;

void insert(element e, element a[], int i);
void insertionSort(element a[], int n);

int main(void)
{
	int num;
	element* student;
	FILE* fp=fopen("input.txt", "r");

	fscanf(fp, "%d", &num); //학생 수 num
	MALLOC(student, sizeof(*student) * (num + 1));

	printf("<<<<<<<<<< input List >>>>>>>>>>\n");
	for (int i = 1; i <= num; i++) {
		fscanf(fp, "%d %s %d", &student[i].key, &student[i].name, &student[i].grade);
		printf("( %d, %s, %d )\n", student[i].key, student[i].name, student[i].grade);
	}
	fclose(fp);

	insertionSort(student, num);

	fp=fopen("output.txt", "w");
	printf("\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (int i = 1; i <= num; i++) {
		printf("( %d, %s, %d )\n", student[i].key, student[i].name, student[i].grade);
		fprintf(fp, "( %d, %s, %d )\n", student[i].key, student[i].name, student[i].grade);
	}
	fclose(fp);

	return 0;
}

void insert(element e, element a[], int i)
{
	//삽입하려는 값(e)보다 작거나 같은 인덱스(i)를 찾아서
	//그 다음 인덱스에 e 삽입
	//맨 뒤 원소부터 비교
	a[0] = e; //e가 가장 작은 경우에도 별도 조건 없이 while탈출
	while (e.key < a[i].key) { //a[i].key가 e보다 작으면 index=i
		a[i + 1] = a[i]; //뒷칸으로 밀기 (e가 들어갈 곳 마련)
		i--; //그 앞의 원소와 비교
	}
	a[i + 1] = e;
}

void insertionSort(element a[], int n)
{
	//각 원소에 대해 insert 수행
	//첫번째 원소는 비교 대상 없으니까 그냥 넘어가기
	for (int j = 2; j <= n; j++) {
		element temp = a[j];
		//temp를 a배열의 이미 정렬된 j-1개의 원소와 비교해서
		//들어가야할 위치에 삽입
		insert(temp, a, j - 1); 
	}
}