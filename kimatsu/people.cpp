#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <string.h>
#include "Setting.h"

#define CHARBUFF 124

//iniファイルを読み込みグラフを作成

double people() {


	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	char keyWord[CHARBUFF];
	char settingFile[CHARBUFF];
	sprintf_s(section, "people");
	sprintf_s(keyWord, "x");
	sprintf_s(settingFile, "%s/Setting.ini", currentDirectory);
	Location L;
	L.x = readDouble(section, keyWord, -1.0, CHARBUFF, settingFile);
	sprintf_s(keyWord, "y");
	L.y = readDouble(section, keyWord, -1.0, CHARBUFF, settingFile);
	mvaddstr(L.x, L.y, "( * * )");
	mvaddstr(L.x + 2, L.y + 1, " -");
	mvaddstr(L.x + 2, L.y + 4, "-");
	mvaddstr(L.x + 1, L.y + 2, " V");
	mvaddstr(L.x + 2, L.y + 3, "|");
	mvaddstr(L.x + 3, L.y + 2, "/ |");
	
	// 画面を更新
	refresh();

	return L.y;
}