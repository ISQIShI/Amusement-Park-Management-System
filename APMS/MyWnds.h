#pragma once
#include"general.h"
#include"Account.h"
#include<Windows.h>
#include<initializer_list>

//编译器使用Win XP的新式控件风格
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

class MyWnds {
public:
	//接受应用程序的当前实例的句柄
	static _In_ HINSTANCE hInstance;
	//屏幕最大宽度
	static int defScreenWidth;
	//屏幕最大高度
	static int defScreenHeight;
	//主窗口默认宽度
	static int defMainWndWidth;
	//主窗口默认高度
	static int defMainWndHeight;

	static int homePageWidth;
	static int homePageHeight;

	//存放设备环境句柄
	static HDC hDC;
	//默认画刷
	static HBRUSH defHBrush;

	//字体
	static LOGFONT defLogFont;
	static HFONT defSmallHFont;
	static HFONT defMidHFont;
	static HFONT defLargeHFont;
	static HFONT currentHFONT;
	static BYTE fontFlag;
	static BYTE lastfontFlag;

	//作为窗口风格的标记
	static BYTE mainWndStyle;
	//作为窗口界面的标记
	static BYTE mainWndFlag;
	//当前用户
	static Account currentAct;

	//对话框的标记
	static BYTE dialogFlag;

	//主窗口过程的参数
	static HWND MainWndProc_hwnd;
	static UINT MainWndProc_uMsg;
	static WPARAM MainWndProc_wParam;
	static LPARAM MainWndProc_lParam;

	//主页过程的参数
	static HWND HomePageProc_hwnd;
	static UINT HomePageProc_uMsg;
	static WPARAM HomePageProc_wParam;
	static LPARAM HomePageProc_lParam;

	//对话框的参数
	static HWND DialogProc_hwnd;
	static UINT DialogProc_uMsg;
	static WPARAM DialogProc_wParam;
	static LPARAM DialogProc_lParam;

	//Listview 点击坐标
	static SHORT x_Listview;//列标
	static UINT y_Listview;//行标

	//获取各数据的个数
	static void GetDataCount();
	//创建字体
	static void CreateFont();

	//主窗口
	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void MainWndProc_WM_COMMAND();
	static void MainWndProc_WM_WINDOWPOSCHANGING();
	static void MainWndProc_WM_WINDOWPOSCHANGED();
	static void MainWndProc_WM_CLOSE();
	static void MainWndProc_WM_DESTROY();
	static LRESULT MainWndProc_WM_CTLCOLORSTATIC();
	static void MainWndProc_WM_PAINT();
	static WPARAM MainWnd();

	//根据上一个 mainWndFlag 销毁对应子窗口
	static void DestroyChildWnd();

	//主页
	static LRESULT CALLBACK HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//static void HomePageProc_WM_COMMAND();
	//static void HomePageProc_WM_WINDOWPOSCHANGING();
	//static void HomePageProc_WM_WINDOWPOSCHANGED();
	//static void HomePageProc_WM_CLOSE();
	//static void HomePageProc_WM_DESTROY();
	//static LRESULT HomePageProc_WM_CTLCOLORSTATIC();
	//static void HomePageProc_WM_PAINT();
	static void HomePage();

	//创建模态对话框
	static LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static WPARAM Dialog();
	static void DialogActAdd();
	static void DialogActModify();
	static void DialogDevAdd();
	static void DialogDevModify();

	//创建子控件
	static void createLoginButton();
	static void createLoginConfirmButton();
	static void createRegisterButton();
	static void createRegisterConfirmButton();
	static void createHomePageButton();
	static void createActInfoButton();
	static void createDevInfoButton();
	static void createTradeInfoButton();
	static void createExitButton();

	static void createUserNameEdit_Static();
	static void createPasswdEdit_Static();
	static void createActNameEdit_Static();

	//枚举所有子窗口（自适应大小和字体）
	static BOOL CALLBACK EnumChildProc_AdaptiveWnd(HWND hwndChild, LPARAM lParam);
	//快速连续销毁多个控件&子窗口
	static void DestroyControl(HWND hWnd,const std::initializer_list<int>& controlID);
	//快速连续给多个控件发送相同消息 (默认为设定字体的消息)
	static void SendMessageToControl(HWND hWnd, const std::initializer_list<int>& controlID, UINT Msg = WM_SETFONT, WPARAM wParam = (WPARAM)MyWnds::currentHFONT, LPARAM lParam = TRUE);

};
