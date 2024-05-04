#pragma once
#include"general.h"

//编译器使用Win XP的新式控件风格
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define loginButtonID 1
#define registerButtonID 2
#define logoutButtonID 3
#define userNameEditID 101
#define passwdEditID 102
#define userNameStaticID 201
#define passwdStaticID 202

extern HDC hDC;
extern LOGFONT defLogFont;
extern HFONT defHFont;
extern HBRUSH defHBrush;
extern UINT newMainWndWidth, newMainWndHeight;

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class MyWnds {
public:
	static WPARAM MainWnd();
};