#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100
#define logB(x,base) log(x)/log(base)

#define MALLOC(p,s) \
   if (!((p)=malloc(s))) {\
      fprintf(stderr, "Insufficient memory");\
      exit(EXIT_FAILURE);\
   }

typedef struct {
	int key;
}element;

void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);

int main(void)
{
	element data[MAX_SIZE];
	int num;
	FILE* f=fopen("input.txt", "r");

	printf("<<<<<<<<<<<<<<< Input List >>>>>>>>>>>>>>>\n");
	fscanf(f, "%d", &num); //입력키의 수
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d", &data[i].key);
		printf("%3d", data[i].key);
	}
	fclose(f);

	printf("\n\n<<<<<<<<<< executing iterative merge sort >>>>>>>>>>\n");
	mergeSort(data, num);

	printf("<<<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>>>\n");
	for (int i = 1; i <= num; i++)
		printf("%3d", data[i].key);
	printf("\n");

	return 0;
}

void merge(element initList[], element mergedList[], int i, int m, int n)
{
	//i부터 시작하는 정렬된 부분집합과 m+1부터 시작하는 정렬된 부분집합을 
	// 정렬해서 작은것부터 mergedList에 넣기
	//부분집합 한 뭉텅이를 merge해서 정렬
	//initList[i:m]+[m+1:n]
	int j, k, t;
	j = m + 1;
	k = i; //mergedList index i부터 시작

	while (i <= m && j <= n) { //하나라도 끝까지 가면 종료
		//앞의 부분집합과 뒤의 부분집합. 각자의 부분집합 내에서 이동
		//i와 j 중 작은 거부터 mergedList에 넣기
		if (initList[i].key <= initList[j].key)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	//남는 데이터 삽입
	//앞부분과 뒷부분의 리스트 중 남는 거 append
	if (i > m)  //앞부분이 먼저 종료->뒷부분 그대로 붙이기
		for (t = j; t <= n; t++)
			mergedList[k++] = initList[t];

	else //뒷부분이 먼저 종료->앞부분 그대로 붙이기
		for (t = i; t <= m; t++)
			mergedList[k++] = initList[t];
	
	//mergedList[k + t - i] = initList[t]; ->피피티 내용
	//앞부분에 있던 거니까 mergedList랑 인덱스 달라짐
	//현재 mergedList의 인덱스 k
	//=뒷부분 원소 개수(n-m-1)+정렬된 앞부분 원소 개수(i)
	//앞부분 원소 인덱스=t부터 시작
}

void mergePass(element initList[], element mergedList[], int n, int s)
{
	int i, j;
	//initList를 2s개씩 뭉텅이로 잘라서 merge 수행
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) 
		//sublist 1개의 크기가 s->2개씩 합치니까 증감식에서 2s 더하기
		// 2s개 원소->merge 끝나는 부분이 i+2s-1 -> 조건식에서 이 부분이 n보다 작다
		// i+2s-1<=n <=> i<=n-2s+1
	//merge(initList, mergedList, 시작, 첫 segment 끝, 두번째 segment 끝)
		merge(initList, mergedList, i,    i + s - 1,     i + 2 * s - 1);

	//2s개씩 뭉텅이 내서 merge 하고 나서 남은 부분 처리
	//
	// 남은 부분이 s개 보다 더 많을 때
	//남은 부분 중 앞부분은 s크기로 자르고 뒷부분은 다른 크기일 때
	//남은 부분 첫 인덱스를 i로 두고 initList 끝(n)까지 merge
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	//남은 부분이 s보다 적을 때
	//이미 정렬된 상태니까 따로 합병할 필요없이 그대로 mergedList에 삽입(복사)
	else
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];

	printf("segment size :%3d\n", s);

	int num = logB(s,2); //s가 2의 몇 제곱인지->짝수 제곱승이면 a,extra 순서
	if (num % 2 ==0) {
		//merge 전
		printf("\t   %s :", "a");
		for (int h = 1; h <= n; h++)
			printf("%3d", initList[h].key);
		printf("\n");
		//merge 후
		printf("\t%s:", "extra");
		for (int h = 1; h <= n; h++)
			printf("%3d", mergedList[h].key);
		printf("\n\n");
	}
	else {
		//merge 전
		printf("\t%s:", "extra");
		for (int h = 1; h <= n; h++)
			printf("%3d", initList[h].key);
		printf("\n");
		//merge 후
		printf("\t   %s :", "a");
		for (int h = 1; h <= n; h++)
			printf("%3d", mergedList[h].key);
		printf("\n\n");
	}
}

void mergeSort(element a[], int n)
{
	int s = 1; //current segment size
	element extra[MAX_SIZE];

	while (s < n) { //부분집합이 전체 원소 수보다 큰 동안 진행. 같아지면 종료
//mergePass( initList, mergedList, int n, int s)
		//a(전체 데이터)를 extra라는 sublist에 정렬해서 넣음
		//->extra 배열 속의 데이터는 2s개씩 끊어서 모두 정렬된 상태
		//printf("mergePass(a,extra)");
		mergePass(a, extra, n, s);
		s *= 2;
		//정렬된 extra가 이번에는 a 역할
		//s개 단위로 정렬되어있는 extra를 2s개씩 묶어 정렬 후 a로 merge
		//printf("mergePass(extra,a)");
		mergePass(extra, a, n, s);
		s *= 2;
	}
}