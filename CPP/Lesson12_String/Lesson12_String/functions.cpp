#include <iostream>
#include <iomanip>
using namespace std;

int my_strlen(const char* str) {
	int counter = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		counter++;
	}

	return counter;
}

void ReplaceSpacesWithStars(char* str) {
	int length = my_strlen(str);
	for (int i = 0; i < length; i++) {
		if (str[i] == ' ') {
			str[i] = '*';
		}
	}
}

void my_strcat(char* str1, char* str2) {
	char* p = str1;

	while (*p != '\0') { // str1
		p++;  // знаходимо реальний кінець першого рядка
	}
	
	int i;
	for (i = 0; str2[i] != '\0'; i++) {
		p[i] = str2[i];
	}

	p[i] = '\0';
}

int CountWords(const char* str) {
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] != ' ' && (str[i + 1] == ' ' || str[i + 1] == '\0')) {
			count++;
		}
	}

	return count;
}

void CopyString(char* dest, const char* src) {
	int i = 0;
	while (src[i] != '\0') {
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void StringReverse(char* str) {
	int length = my_strlen(str);
	for (int i = 0; i < length / 2; i++) {
		char temp = str[i];
		str[i] = str[length - 1 - i];
		str[length - 1 - i] = temp;
	}
}