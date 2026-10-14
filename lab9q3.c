#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#define LEN 16
#define MAX 25
int main() {
	FILE* fp = NULL;
	fp= fopen("C:\\Users\\thinkpad\\Desktop\\Bridging Courses\\C Programming\\Lab9\\words.inf", "r");
			
	char words[MAX][LEN];
	int count = 0;

	if (fp == NULL) {
		printf("Cannot open file.\n");
		return 1;
	}

	while (count < MAX &&
		fscanf(fp, "%15s", words[count]) == 1) {
		count++;
	}

	fclose(fp);
	for (int i = 0;i < count-1;i++) {
		for (int j = 0;j < count-1-i;j++) {
			if (strcmp(words[j], words[j + 1]) > 0) {
				char temp[LEN];
				strcpy(temp, words[j]);
				strcpy(words[j], words[j + 1]);
				strcpy(words[j + 1], temp);
			}
		}
	}
	printf("Sorted in a lexicographical order:\n");
	printf("==================================\n");
	for (int i = 0;i < count-1;i++) {
		printf("%-8d", i + 1);
		printf("%s\n", words[i]);

	}



	return 0;



}
