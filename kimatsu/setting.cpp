#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>
#include "Setting.h"

#define CHARBUFF 124


void getGurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

void writeDouble(const char* section, const char* keyword, double returnValue, const char* filePath) {
	char returnValue1[10];
	sprintf_s(returnValue1, "%lf", returnValue);
	if (WritePrivateProfileString(section, keyword, returnValue1, filePath)) {
	}
	else {
		printf("failed to write [$s] %s to %s \n", section, keyword, filePath);
	}
}

double readDouble(const char* section, const char* keyword, double defaultValue, int returnValue, const char* filePath) {
	char keyValue[CHARBUFF];
	char* ends;
	double d;
	if (GetPrivateProfileString(section, keyword, "none", keyValue, returnValue, filePath) != 0) {
		d = strtod(keyValue, &ends);
		return d;
	}
	else {
		printf("%s doesn't contain [$s] %s\n", filePath, section, keyword);

	}
}