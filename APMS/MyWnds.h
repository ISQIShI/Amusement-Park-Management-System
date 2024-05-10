#pragma once
#include"general.h"
#include"Account.h"
#include<Windows.h>
#include<initializer_list>

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
#define tradeInfoButtonID 108//交易记录按钮
#define exitButtonID 109//退出系统
//编辑框
#define userNameEditID 201//用户名
#define passwdEditID 202//密码
#define actNameEditID 203//用户昵称
#define editActInfoEditID 204//编辑用户信息
//静态文本
#define userNameStaticID 301//用户名
#define passwdStaticID 302//密码
#define actNameStaticID 303//昵称
//SysLink
#define editActNameSysLinkID 401//编辑用户昵称
#define editPasswdSysLinkID 402//修改密码
#define creditSysLinkID 403//充值/提现
#define logoutSysLinkID 404//注销用户
#define saveSysLinkID 405//保存
#define browseActSysLinkID 406//查看所有用户（需要权限）
#define actReturnSysLinkID 407//返回
#define actInfoSysLinkID 408//更改用户信息

//ListView
#define actInfoListID 501//用户信息列表

//UI界面
#define LoginUI 1
#define RegisterUI 2
#define HomeUI 3
#define ActInfoUI 4
#define DevInfoUI 5
#define TradeInfoUI 6

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

	//作为窗口风格的标记
	static BYTE mainWndStyle;
	//作为窗口界面的标记
	static BYTE mainWndFlag;
	//当前用户
	static Account currentAct;

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

	//用户信息的参数
	static HWND ActInfoProc_hwnd;
	static UINT ActInfoProc_uMsg;
	static WPARAM ActInfoProc_wParam;
	static LPARAM ActInfoProc_lParam;

	//设备信息的参数
	static HWND DevInfoProc_hwnd;
	static UINT DevInfoProc_uMsg;
	static WPARAM DevInfoProc_wParam;
	static LPARAM DevInfoProc_lParam;

	//交易记录的参数
	static HWND TradeInfoProc_hwnd;
	static UINT TradeInfoProc_uMsg;
	static WPARAM TradeInfoProc_wParam;
	static LPARAM TradeInfoProc_lParam;

	//获取各数据的个数
	static void GetDataCount();
	//创建字体
	static void CreateFont();

	//主窗口
	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void MainWndProc_WM_COMMAND();
	static void MainWndProc_WM_WINDOWPOSCHANGING();
	static void MainWndProc_WM_WINDOWPOSCHANGED();
	static void adaptiveWndLoginUI(BYTE tempFontFlag);
	static void adaptiveWndRegisterUI(BYTE tempFontFlag);
	static void adaptiveWndHomeUI(BYTE tempFontFlag);
	static void adaptiveWndActInfoUI(BYTE tempFontFlag);
	static void adaptiveWndDevInfoUI(BYTE tempFontFlag);
	static void adaptiveWndTradeInfoUI(BYTE tempFontFlag);
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

	//用户信息
	static BYTE actInfoSysLinkFlag;
	static LRESULT CALLBACK ActInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void ActInfoProc_WM_NOTIFY();
	static void ActInfoProc_WM_PAINT();
	static void ActInfoProc_WM_CREATE();
	static void ActInfo();

	//设备信息
	static LRESULT CALLBACK DevInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void DevInfo();

	//交易记录
	static LRESULT CALLBACK TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void TradeInfo();

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

	//快速连续销毁多个控件&子窗口
	static void DestroyControl(HWND hWnd,const std::initializer_list<int>& controlID);
	//快速连续给多个控件发送相同消息 (默认为设定字体的消息)
	static void SendMessageToControl(HWND hWnd, const std::initializer_list<int>& controlID, UINT Msg = WM_SETFONT, WPARAM wParam = (WPARAM)MyWnds::currentHFONT, LPARAM lParam = TRUE);
};
