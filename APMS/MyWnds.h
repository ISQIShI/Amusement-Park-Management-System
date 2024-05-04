#pragma once
#include"general.h"
#include"Door.h"

//������ʹ��Win XP����ʽ�ؼ����
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define loginButtonID 1
#define loginConfirmButtonID 2
#define registerButtonID 3
#define registerConfirmButtonID 4
#define logoutButtonID 4
#define userNameEditID 101
#define passwdEditID 102
#define actNameEditID 103
#define userNameStaticID 201
#define passwdStaticID 202
#define actNameStaticID 203
#define LoginUI 0
#define RegisterUI 1
#define HomeUI 3

class MyWnds {
public:
	//����Ӧ�ó���ĵ�ǰʵ���ľ��
	static _In_ HINSTANCE hInstance;
	//��Ļ�����
	static int defScreenWidth;
	//��Ļ���߶�
	static int defScreenHeight;
	//������Ĭ�Ͽ��
	static int defMainWndWidth;
	//������Ĭ�ϸ߶�
	static int defMainWndHeight;
	static HDC hDC;
	static LOGFONT defLogFont;
	static HFONT defHFont;
	static HBRUSH defHBrush;
	//��Ϊ���ڷ��ı��
	static BYTE mainWndStyle;
	//��Ϊ���ڽ���ı��
	static BYTE mainWndFlag;

	static HWND MainWndProc_hwnd;
	static UINT MainWndProc_uMsg;
	static WPARAM MainWndProc_wParam;
	static LPARAM MainWndProc_lParam;

	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void MainWndProc_WM_COMMAND();
	static void MainWndProc_WM_WINDOWPOSCHANGING();
	static void MainWndProc_WM_WINDOWPOSCHANGED();
	static void MainWndProc_WM_CLOSE();
	static void MainWndProc_WM_DESTROY();
	static LRESULT MainWndProc_WM_CTLCOLORSTATIC();
	static void MainWndProc_WM_PAINT();
	static WPARAM MainWnd();
};