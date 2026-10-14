#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX 21

int checkPalindrome(char str[]) {
	int len = strlen(str);
	for (int i = 0; i < len / 2; i++) {
		if (str[i] != str[len - 2 - i])//-2 is because '\n' and '\0' are at the end of the string
		{
			return 0; 
		}
	}
	return 1; // Is a palindrome
}
//this program is to check if an input string is a palindrome.
int main() {
	
	char str[MAX];

	printf("Enter a word of no more than 20 characters (or press Enter to quit): ");
	fgets(str, MAX, stdin);
	while(str[0] != '\n') {
		if (checkPalindrome(str)) {
			printf("The string is a palindrome.\n");
		} else {
			printf("The string is not a palindrome.\n");
		}
		printf("Enter a word of no more than 20 characters (or press Enter to quit): ");
		fgets(str, MAX, stdin);
	}
	return 0;
}
	