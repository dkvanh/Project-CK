#pragma once // tránh đụng độ thư viện khi gọi chồng file lên nhau
#include <stdio.h>
#include <iomanip>
#include <conio.h>
#include<ctime> /* thư viện hỗ trợ về thời gian thực */
#include "windows.h" // thư viện này bá đạo lắm nhé - chứa nhiều đồ chơi nek - cứ tìm hiểu dần dần 
//======= lấy tọa độ x của con trỏ hiện tại =============
#define KEY_NONE	-1
int whereX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.X;
	return -1;
}
//========= lấy tọa độ y của con trỏ hiện tại =======
int whereY()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
		return csbi.dwCursorPosition.Y;
	return -1;
}
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//============= đặt màu cho chữ =========
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
//======= trả về mã phím người dùng bấm =========
int inputKey()
{
	if (_kbhit()) //true
	{
		int key = _getch();

		if (key == 224)
		{
			key = _getch();
			return key + 1000;
		}

		return key;
	}
	else
	{
		return KEY_NONE;
	}
	return KEY_NONE;
}
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

//================= Vô hiệu hóa nút tắt, phóng to, thu nhỏ của chương trình=============//
void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);
    
    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

//========Chỉnh kích thước của cứa sổ được tạo ra =======//
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

//============== Vô hiệu hóa việc kéo để mở rộng cửa sổ=========//
void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void SetScreenBufferSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}


void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

/*
void printTexL(const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy vị trí hiện tại của con trỏ
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenInfo);
    COORD pos = screenInfo.dwCursorPosition;

    // Thiết lập vị trí mới với giá trị X cố định
    pos.X = 38;
	pos.Y+=1;

    // Thiết lập vị trí con trỏ
    SetConsoleCursorPosition(hConsole, pos);

    // Hiển thị câu văn bản tại vị trí chỉ định
    std::cout << text;
}
*/

void printTex(const std::string& text) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy vị trí hiện tại của con trỏ
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenInfo);
    COORD pos = screenInfo.dwCursorPosition;

    // Thiết lập vị trí mới với giá trị X cố định
    pos.X = 38;

    // Thiết lập vị trí con trỏ
    SetConsoleCursorPosition(hConsole, pos);

    // Hiển thị câu văn bản tại vị trí chỉ định
    std::cout << text;
}

void printNumL(double number) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy vị trí hiện tại của con trỏ
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenInfo);
    COORD pos = screenInfo.dwCursorPosition;

    // Thiết lập vị trí mới với giá trị X cố định
    pos.X = 38;
	pos.Y+=1;

    // Thiết lập vị trí con trỏ
    SetConsoleCursorPosition(hConsole, pos);

    // Hiển thị giá trị số thực tại vị trí chỉ định
    std::cout <<std::fixed << std::setprecision(4) <<number;
}
void printNum(double number) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy vị trí hiện tại của con trỏ
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenInfo);
    COORD pos = screenInfo.dwCursorPosition;

    // Thiết lập vị trí mới với giá trị X cố định
	pos.X=38;

    // Thiết lập vị trí con trỏ
    SetConsoleCursorPosition(hConsole, pos);

    // Hiển thị giá trị số thực tại vị trí chỉ định
    std::cout <<std::fixed << std::setprecision(4) <<number;
}

void daucach(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy vị trí hiện tại của con trỏ
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenInfo);
    COORD pos = screenInfo.dwCursorPosition;

    // Hàm hoạt động mô tả kí tự \t 
	pos.X = ((pos.X-38)/10 +1) *10 +38;

    // Thiết lập vị trí con trỏ
    SetConsoleCursorPosition(hConsole, pos);

}

void xuongdong(){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Lấy vị trí hiện tại của con trỏ
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenInfo);
    COORD pos = screenInfo.dwCursorPosition;

    // Thiết lập vị trí mới với giá trị X cố định
	pos.X=38;
	pos.Y+=1;

    // Thiết lập vị trí con trỏ
    SetConsoleCursorPosition(hConsole, pos);
}


