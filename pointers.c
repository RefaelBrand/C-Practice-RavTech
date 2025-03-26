#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void question4_1() {
	int arr[10];
	int* p = arr;

	printf("sizeof(arr) = %lu\n", sizeof(arr));
	printf("sizeof(p) = %lu\n", sizeof(p));
	printf("sizeof(*p) = %lu\n", sizeof(*p));
}

int* allocateMemory(int* arr, const int size) {
	int* newArr = (int*)malloc(sizeof(int) * size);
	for (int i = 0; i < size; i++)
		newArr[i] = arr[i];
	return newArr;
}

void question4_2() {
	int arr[100];
	for (int i = 0; i < 100; i++)
		arr[i] = i + 1;
	int* dynamicArr = allocateMemory(arr, 100);
}

void question4_3() {
	printf("please enter a string\n");
	char str[100];
	scanf("%s", str);
	char* left = str;
	char* right = str + strlen(str) - 1;
	while(left < right) {
		if (*left != *right) {
			printf("not a palindrome\n");
			return;
		}
		left++;
		right--;
	}
	printf("palindrome\n");
}

void helpFunction4_4(int** pp) {
	**pp = **pp + 1;
}

void question4_4() {
	int num = 1;
	printf("num = %d\n", num);
	int* p = &num;
	int** pp = &p;
	helpFunction4_4(pp);
	printf("num = %d\n", num);
}

void question4_5() {
	int n = 3;
	int m = 3;

	int** matrix = (int**)malloc(n * sizeof(int*));

	for (int i = 0; i < n; i++)
		matrix[i] = (int*)malloc(m * sizeof(int));

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			matrix[i][j] = rand() % 10;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			printf("%d ", matrix[i][j]);

	for (int i = 0; i < n; i++)
		free(matrix[i]);
	free(matrix);
}

int main() {
	while (1) {
		printf("Welcome to practice number 4!,\nchoose a question between 1 and 4 you want to run.\nPress 0 to exit\n");
		int question;
		scanf("%d", &question);
		switch (question) {
			case 0: return 0;
			case 1: question4_1(); break;
			case 2: question4_2(); break;
			case 3: question4_3(); break;
			case 4: question4_4(); break;
			case 5: question4_5(); break;
			default: printf("ERROR - invalid question number\n");
		}
	}
	return 0;
}