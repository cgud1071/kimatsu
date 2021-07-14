#pragma once
#include <stdio.h>
#include <locale.h>


struct Location {
	double x;
	double y;
};


void getGurrentDirectory(char* currentDirectory);
void writeDouble(const char* section, const char* keyword, double returnValue, const char* filePath);
double readDouble(const char* section, const char* keyword, double defaultValue, int returnValue, const char* filePath);
double people();
void ddelete();
void shuffle(int array[], int size);