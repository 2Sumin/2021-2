#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isPalindrome(char* str);

int main(void)
{
	int (*pd)(char*);
	char str[100];

	printf("Enter the string to check palindrome: ");
	gets(str);

	pd = isPalindrome;
	int res = pd(str);

	if (res == 1)
		printf("%s is palindrome\n", str);

	else if (res == 0)
		printf("%s is not palindrome\n", str);
	return 0;
}

int isPalindrome(char* str)
{
	int len = strlen(str);

	for (int i = 0; i < (len / 2); i++) {
		if (str[i] != str[len - i - 1])
			return 0;
	}
	return 1; //È¸¹®
}