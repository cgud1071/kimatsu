// kimatsu.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <string.h>
#include <time.h>
#include <thread>
#include "Setting.h"



#define CHARBUFF 124
#define USEMUTEX

HANDLE threadMutex;
DWORD WINAPI  People(LPVOID arg);
DWORD WINAPI  Daruma(LPVOID arg);
DWORD WINAPI  Countdown(LPVOID arg);

int end = 0;
int wl = 0;
int a = 1;

DWORD WINAPI  Countdown(LPVOID arg) {
	int time1 = 20;
	int number = 0;
	mvaddstr(3, 90, "CountDown");
	while (a == 1) {
		number++;
		if (number % 50000 == 0) {
			time1--;
		}
		
		char time_name[50];
		sprintf_s(time_name, 50, "%d", time1);
		mvaddstr(3, 100, "   ");
		mvaddstr(3, 101, "   ");
		mvaddstr(3, 102, "   ");
		mvaddstr(3, 100, time_name);
		if (time1 <= 0) {
			wl = 1;
			a = 2;
		}
		refresh();
	}
	return wl;
}


DWORD WINAPI People(LPVOID arg) {
	int key;
	int count = 0;
	Location L;

	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	char keyWord[CHARBUFF];
	char settingFile[CHARBUFF];
	sprintf_s(section, "people");
	sprintf_s(settingFile, "%s/Setting.ini", currentDirectory);
	sprintf_s(keyWord, "y");
	


	while (a == 1) {

		mvaddstr(24, 9, "start");
		mvaddstr(24, 98, "goal");
		for (int i = 9;i <= 102;i++) {
			mvaddstr(23, i,"__");
		}
		count++;
		L.y = people();

		key = getch();

		if (key == KEY_RIGHT) {
			if (end == 1) {
				wl = 1;
				a = 2;

			}
			L.y++;
			writeDouble(section, keyWord, L.y, settingFile);
			ddelete();

		}

		if (L.y == 98) {

			people();
			wl = 0;
			refresh();
			a = 2;

		}
		
	}
	return wl;
}
DWORD WINAPI  Daruma(LPVOID arg) {

	while (a == 1) {

		char daruma[36] = "d,a,r,u,m,a,s,a,n,g,a,k,o,r,o,n,d,a";
		int t[6] = {1,2,3,4,5};
		shuffle(t, 5);
		int count = 0;
		char* ptr;
		char* p;
		// カンマを区切りに文字列を分割
		// 1回目
		for (int i = 7;i < 50;i++) {
			mvaddstr(5, i, " ");
		}
		
		end = 0;
		ptr = strtok_s(daruma, ",", &p);
		mvaddstr(5, 7, ptr);
		

		// 画面を更新
		refresh();

		// 2回目以降
		while (ptr != NULL) {
			count++;
			Sleep(t[1] * 40);
			// strtok関数により変更されたNULLのポインタが先頭
			ptr = strtok_s(NULL, ",", &p);

			// ptrがNULLの場合エラーが発生するので対処
			if (ptr != NULL) {
				mvaddstr(5, 7 + 2*count, ptr);
				// 画面を更新
				refresh();
			}
			
		}
		end = 1;
		if (a == 1) {
			Sleep(t[1] * 800);
		}
		
	}
	return wl;
}
	
int main(int argc, char* argv[])
{
	HANDLE HandleCountdown;
	HANDLE HandlePeople;
	HANDLE HandleDaruma;

	char currentDirectory[CHARBUFF];
	getGurrentDirectory(currentDirectory);
	char section[CHARBUFF];
	char keyWord[CHARBUFF];
	char settingFile[CHARBUFF];
	sprintf_s(section, "people");
	sprintf_s(settingFile, "%s/Setting.ini", currentDirectory);
	sprintf_s(keyWord, "y");


	if (initscr() == NULL) {
		return 1;
	}
	curs_set(1);
	keypad(stdscr, TRUE);
	setlocale(LC_ALL, "");




	threadMutex = CreateMutex(NULL, FALSE, NULL);//ミューテックスの生成
	HandlePeople = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)People, NULL, 0, NULL);
	HandleDaruma = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Daruma, NULL, 0, NULL);
	HandleCountdown = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Countdown, NULL, 0, NULL);

	WaitForSingleObject(HandleCountdown, INFINITE);
	CloseHandle(HandleCountdown);

	WaitForSingleObject(HandlePeople, INFINITE);
	CloseHandle(HandlePeople);

	WaitForSingleObject(HandleDaruma, INFINITE);
	CloseHandle(HandleDaruma);

	CloseHandle(threadMutex);

	if (wl == 0) {
		mvaddstr(7, 7, "! ! win ! !");
	}
	else if (wl == 1) {
		mvaddstr(7, 7, "! ! lose ! !");
	}
	
	refresh();
	writeDouble(section, keyWord, 10, settingFile);
	Sleep(1000);
}





// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
