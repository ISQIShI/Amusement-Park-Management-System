#pragma once
#include"general.h"
#include"Door.h"

//编译器使用Win XP的新式控件风格
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//子窗口标识符
#define homePageWndID 1//主页
#define actInfoWndID 2//用户信息
#define devInfoWndID 3//设备信息
#define tradeInfoWndID 4//交易记录（需要权限）

//按钮
#define loginButtonID 101//登录
#define loginConfirmButtonID 102//确认登录
#define registerButtonID 103//注册
#define registerConfirmButtonID 104//确认注册
#define homePageButtonID 105//主页按钮
#define actInfoButtonID 106//用户信息按钮
#define devInfoButtonID 107//设备信息按钮
#define tradeInfoButtonID 108//交易记录按钮（需要权限）
#define exitButtonID 109//退出系统
//编辑框
#define userNameEditID 201//用户名
#define passwdEditID 202//密码
#define actNameEditID 203//用户昵称
//静态文本
#define userNameStaticID 301//用户名
#define passwdStaticID 302//密码
#define actNameStaticID 303//昵称

//UI界面
#define LoginUI 1
#define RegisterUI 2
#define HomeUI 3

//字体
#define defSmallFont 1
#define defMidFont 2
#define defLargeFont 3

//各控件坐标
#define homePageButtonCoord_X 0.05
#define homePageButtonCoord_Y 0.125
#define homePageButtonWidth 0.1
#define homePageButtonHeight 0.1

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

	//作为窗口风格的标记
	static BYTE mainWndStyle;
	//作为窗口界面的标记
	static BYTE mainWndFlag;

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

	//主页
	static LRESULT CALLBACK HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void HomePageProc_WM_COMMAND();
	static void HomePageProc_WM_WINDOWPOSCHANGING();
	static void HomePageProc_WM_WINDOWPOSCHANGED();
	static void HomePageProc_WM_CLOSE();
	static void HomePageProc_WM_DESTROY();
	static LRESULT HomePageProc_WM_CTLCOLORSTATIC();
	static void HomePageProc_WM_PAINT();
	static void HomePage();

	//控件
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
};
