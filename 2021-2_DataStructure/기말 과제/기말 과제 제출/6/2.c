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

	fscanf(fp, "%d", &num); //�л� �� num
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
	//�����Ϸ��� ��(e)���� �۰ų� ���� �ε���(i)�� ã�Ƽ�
	//�� ���� �ε����� e ����
	//�� �� ���Һ��� ��
	a[0] = e; //e�� ���� ���� ��쿡�� ���� ���� ���� whileŻ��
	while (e.key < a[i].key) { //a[i].key�� e���� ������ index=i
		a[i + 1] = a[i]; //��ĭ���� �б� (e�� �� �� ����)
		i--; //�� ���� ���ҿ� ��
	}
	a[i + 1] = e;
}

void insertionSort(element a[], int n)
{
	//�� ���ҿ� ���� insert ����
	//ù��° ���Ҵ� �� ��� �����ϱ� �׳� �Ѿ��
	for (int j = 2; j <= n; j++) {
		element temp = a[j];
		//temp�� a�迭�� �̹� ���ĵ� j-1���� ���ҿ� ���ؼ�
		//������ ��ġ�� ����
		insert(temp, a, j - 1); 
	}
}