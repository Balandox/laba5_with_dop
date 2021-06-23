#define _CRT_SECURE_NO_WARNINGS
#define ABBR_SIZE 3
#define SIZE 100
#include <stdio.h>
#include <stdlib.h>

const char* abbr[ABBR_SIZE] = { "etc.", "i.e.", "cuz" };
const char* full[ABBR_SIZE] = { "et cetera", "id est", "because" };

int input_validation(int** dst, int* a, int* b, int* c) {
	int k = 0, j = 0, n = 0;
	if (scanf("%d", &k) != 1 || (k != 0 && k != 1 && k != 2)) {
		printf("Error! Incorrect input.");
		exit(1);
	}
	printf("Input the entry number: ");
	if (scanf("%d", &n) != 1 || n <= 0) {
		printf("Error!Incorrect input");
		exit(1);
	}
	switch (k) {
	case 0:
		if (*a == 0 || n > *a) {
			printf("Error!Incorrect input"); // проверка на выбор корректного сокращения
			exit(1);
		}
		break;
	case 1:
		if (*b == 0 || n > *b) {
			printf("Error!Incorrect input");
			exit(1);
		}
		break;
	case 2:
		if (*c == 0 || n > *c) {
			printf("Error!Incorrect input");
			exit(1);
		}
		break;
	}
	j = dst[k][n - 1];
	return j;
}

int abbr_idx(char* str, int** dst)
{
	int count1 = 0, count2 = 0, count3 = 0, idx = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		int n = -1;
		for (int j = 0; j < ABBR_SIZE; j++) {
			if (isSubstr(&str[i], abbr[j]))
				n = j;
		}
		if (n != -1) {
			if (in_word(str, abbr[n], &i) == 1)
				continue;
			switch (n) {
			case 0:
				dst[0][count1] = i;
				count1++;
				break;
			case 1:
				dst[1][count2] = i;
				count2++;
				break;
			case 2:
				dst[2][count3] = i;
				count3++;
				break;
			}
		}
	}
	if (count1 == 0 && count2 == 0 && count3 == 0) {
		printf("\nThere are no abbreviations in the string.");
		exit(1);
	}
	Amount_abbr(&count1, &count2, &count3);
	//printf("Amount of abbreviations:\netc. = %d\ni.e. = %d\ncuz = %d\n\n", count1, count2, count3);
	count_print(&count1, &count2, &count3);
	idx = input_validation(dst, &count1, &count2, &count3);
	return idx;
}
int count_print(int* a, int* b, int *c) {
	printf("Select an abbreviation from the list using the notation below:\n ");
	if (*a == 0) {
		printf("");
	}
	else {
		printf("etc. = 0\n");
	}
	if (*b == 0) {
		printf("");
	}
	else
		printf("i.e. = 1\n");
	if (*c == 0)
		printf("");
	else
		printf("cuz = 2\n");
}
int Amount_abbr(int* a, int* b, int* c) {
	printf("Amount of abbreviations:\n");
	if (*a == 0) {
		printf("");
	}
	else {
		printf("etc. = %d\n", *a);
	}
	if (*b == 0) {
		printf("");
	}
	else
		printf("i.e. = %d\n", *b);
	if (*c == 0)
		printf("");
	else
		printf("cuz = %d\n", *c);
	printf("\n");
}
int in_word(char* str1, char* str2, int* i)
{
	int size = len(str2);
	if ((str1[*i - 1] >= 'A' && str1[*i - 1] <= 'Z') || (str1[*i - 1] >= 'a' && str1[*i - 1] <= 'z'))
		return 1;
	if ((str1[*i + size] >= 'A' && str1[*i + size] <= 'Z') || (str1[*i + size] >= 'a' && str1[*i + size] <= 'z'))
		return 1;
}
char* readLine()
{
	char* line = NULL;
	int n = 0;
	char c;
	do {
		c = getchar();
		line = (char*)realloc(line, (n + 1) * sizeof(char));
		if (line == NULL) {
			printf("Allocation error!");
			exit(1);
		}
		line[n] = c;
		n++;
	} while (c != '\n');
	line[n - 1] = '\0';
	return line;
}
int isSubstr(const char* str1, const char* str2)
{
	while (*str1 != '\0' && *str2 != '\0') {
		if (*str1 != *str2)
			return 0;
		str1++;
		str2++;
	}
	if (*str2 != '\0')
		return 0;
	else
		return 1;
}
int len(const char* str)
{
	int n = 0;
	while (*str != '\0') {
		n++;
		str++;
	}
	return n;
}
char* makeFull(char* str)
{
	int k = -1;
	int idx = 0;
	int** p;
	p = (int**)malloc(ABBR_SIZE * sizeof(int*));
	for (int i = 0; i < ABBR_SIZE; i++)
		p[i] = (int*)malloc(SIZE * sizeof(int));
	idx = abbr_idx(str, p); // индекс сокращения, которое хотим заменить
	switch (str[idx]) {
	case 'e':
		k = 0;
		break;
	case 'i':
		k = 1;
		break;
	case 'c':
		k = 2;
		break;
	}
	int fullSize = len(full[k]);
	int strSize = len(str);
	int size = fullSize - len(abbr[k]);
	str = (char*)realloc(str, (strSize + size + 1) * sizeof(char));
	if (str == NULL) {
		printf("Allocation error!");
		exit(1);
	}
	for (int j = strSize + size; j >= idx + fullSize; j--) {
		str[j] = str[j - size];
	}
	for (int j = idx, f = 0; f < fullSize; j++, f++)
		str[j] = full[k][f];

	for (int i = 0; i < ABBR_SIZE; i++)
		free(p[i]);
	free(p);
	return str;
}

int main()
{
	printf("List of abbreviations:\n etc. = et cetera \n i.e. = id est\n cuz = because\n\n");
	printf("Input string:\n");
	char* str = readLine();
	str = makeFull(str);
	printf("\n");
	printf("%s\n", str);
	free(str);
	return 0;
}