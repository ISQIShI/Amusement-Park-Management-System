#include "MyWnds.h"
#include "Data.hpp"
#include "Door.h"
#include "Device.h"
#include "Trade.h"
#include "Recharge.h"
#include "Notification.h"
#include <CommCtrl.h>
#include <tchar.h>
#include <windowsx.h>


HINSTANCE MyWnds::hInstance;
int MyWnds::defScreenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
int MyWnds::defScreenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
int MyWnds::defMainWndWidth = int(0.7 * defScreenWidth);
int MyWnds::defMainWndHeight = int(0.7 * defScreenHeight);


int MyWnds::homePageWidth;
int MyWnds::homePageHeight;

HDC MyWnds::hDC;
HBRUSH MyWnds::defHBrush = CreateSolidBrush(RGB(133, 193, 233));//创建默认画刷

LOGFONT MyWnds::defLogFont;
HFONT MyWnds::defSmallHFont;
HFONT MyWnds::defMidHFont;
HFONT MyWnds::defLargeHFont;
HFONT MyWnds::currentHFONT;
BYTE MyWnds::fontFlag;
BYTE MyWnds::lastfontFlag;

BYTE MyWnds::mainWndStyle = LoginUI;
BYTE MyWnds::mainWndFlag = LoginUI;
Account MyWnds::currentAct = {0};
BYTE MyWnds::dialogFlag;

HWND MyWnds::MainWndProc_hwnd;
UINT MyWnds::MainWndProc_uMsg;
WPARAM MyWnds::MainWndProc_wParam;
LPARAM MyWnds::MainWndProc_lParam;

HWND MyWnds::HomePageProc_hwnd;
UINT MyWnds::HomePageProc_uMsg;
WPARAM MyWnds::HomePageProc_wParam;
LPARAM MyWnds::HomePageProc_lParam;

SHORT MyWnds::x_Listview = -1;
UINT MyWnds::y_Listview = 0;


//对话框的参数
HWND MyWnds::DialogProc_hwnd;
UINT MyWnds::DialogProc_uMsg;
WPARAM MyWnds::DialogProc_wParam;
LPARAM MyWnds::DialogProc_lParam;

//获取各数据记录个数
void MyWnds::GetDataCount() {
	LARGE_INTEGER temp;
	HANDLE tempHANLDE;
	//用户信息
	tempHANLDE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Account::mCount = 0; }
	else{
		GetFileSizeEx(tempHANLDE, &temp);
		Account::mCount = temp.QuadPart / sizeof(Account);
		CloseHandle(tempHANLDE);
	}
	//设备信息
	tempHANLDE = CreateFile(_T("Device.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Device::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Device::mCount = temp.QuadPart / sizeof(Device);
		CloseHandle(tempHANLDE);
	}
	//交易记录
	tempHANLDE = CreateFile(_T("Trade.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Trade::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Trade::mCount = temp.QuadPart / sizeof(Trade);
		CloseHandle(tempHANLDE);
	}
	//充值记录
	tempHANLDE = CreateFile(_T("Recharge.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Recharge::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Recharge::mCount = temp.QuadPart / sizeof(Recharge);
		CloseHandle(tempHANLDE);
	}
	//公告
	tempHANLDE = CreateFile(_T("Notification.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Notification::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Notification::mCount = temp.QuadPart / sizeof(Notification);
		CloseHandle(tempHANLDE);
	}
}

//创建字体
void MyWnds::CreateFont() {
	//创建默认字体
	MyWnds::defLogFont.lfEscapement = 0;//转义向量与设备的 x 轴之间的角度（以十分之一度为单位）
	MyWnds::defLogFont.lfOrientation = 0;//每个字符的基线和设备 x 轴之间的角度（以十分之一度为单位）
	MyWnds::defLogFont.lfWeight = 550;//字体的粗细
	MyWnds::defLogFont.lfItalic = FALSE;//斜体
	MyWnds::defLogFont.lfUnderline = FALSE;//下划线
	MyWnds::defLogFont.lfStrikeOut = FALSE;//删除线
	MyWnds::defLogFont.lfCharSet = GB2312_CHARSET;//字符集
	MyWnds::defLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;//输出精度
	MyWnds::defLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;//剪裁精度
	MyWnds::defLogFont.lfQuality = ANTIALIASED_QUALITY;//输出质量
	MyWnds::defLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;//字体的间距和系列
	_stprintf_s(MyWnds::defLogFont.lfFaceName, _T("宋体"));//字体名称
	//小字体
	MyWnds::hDC = GetDC(MyWnds::MainWndProc_hwnd);//获取设备环境句柄
	MyWnds::defLogFont.lfHeight = MulDiv(11, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//10是字号大小
	MyWnds::defLogFont.lfWidth = 0;//字体中字符的平均宽度（以逻辑单位为单位）
	MyWnds::defSmallHFont = CreateFontIndirect(&MyWnds::defLogFont);
	//中字体
	MyWnds::defLogFont.lfHeight = MulDiv(13, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//13是字号大小
	MyWnds::defLogFont.lfWidth = 0;
	MyWnds::defMidHFont = CreateFontIndirect(&MyWnds::defLogFont);
	//大字体
	MyWnds::defLogFont.lfHeight = MulDiv(17, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//17是字号大小
	MyWnds::defLogFont.lfWidth = 0;
	MyWnds::defLargeHFont = CreateFontIndirect(&MyWnds::defLogFont);
	ReleaseDC(MyWnds::MainWndProc_hwnd, MyWnds::hDC);//释放设备环境句柄
	MyWnds::hDC = NULL;//hDC置空
}

//构建窗口过程---主窗口
LRESULT CALLBACK MyWnds::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::MainWndProc_hwnd = hwnd;
	MyWnds::MainWndProc_uMsg = uMsg;
	MyWnds::MainWndProc_wParam = wParam;
	MyWnds::MainWndProc_lParam = lParam;
	switch (uMsg){
	case WM_COMMAND:
		MyWnds::MainWndProc_WM_COMMAND();
		break;
	case WM_WINDOWPOSCHANGING://准备更改窗口大小
		MyWnds::MainWndProc_WM_WINDOWPOSCHANGING();
		break;
	case WM_WINDOWPOSCHANGED://窗口大小完成更改
		MyWnds::MainWndProc_WM_WINDOWPOSCHANGED();
		break;
	case WM_CLOSE://关闭窗口
		MyWnds::MainWndProc_WM_CLOSE();
		break;
	case WM_DESTROY://销毁窗口
		MyWnds::MainWndProc_WM_DESTROY();
		break;
	case WM_CTLCOLORSTATIC://绘制static和edit(ES_READONLY)控件
		return MyWnds::MainWndProc_WM_CTLCOLORSTATIC();
	case WM_PAINT://绘制窗口更新区域
		MyWnds::MainWndProc_WM_PAINT();
		break;
	case WM_CREATE://创建窗口
	{
		MyWnds::GetDataCount();
		MyWnds::CreateFont();
		if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; MyWnds::fontFlag = defSmallFont; }
		else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; MyWnds::fontFlag = defMidFont; }
		else { MyWnds::currentHFONT = MyWnds::defLargeHFont; MyWnds::fontFlag = defLargeFont; }

		MyWnds::createLoginConfirmButton();
		MyWnds::createRegisterButton();
		MyWnds::createUserNameEdit_Static();
		MyWnds::createPasswdEdit_Static();

	}
	break;
	default://未自定义的其他消息
		return DefWindowProc(MyWnds::MainWndProc_hwnd, uMsg, wParam, MyWnds::MainWndProc_lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::MainWndProc_WM_COMMAND() {
	//处理点击按钮的消息
	if (HIWORD(MyWnds::MainWndProc_wParam) == BN_CLICKED) {
		switch (LOWORD(MyWnds::MainWndProc_wParam)) {
		case loginButtonID: {
			//销毁控件
			MyWnds::DestroyControl(MyWnds::MainWndProc_hwnd, { loginButtonID,registerConfirmButtonID,actNameStaticID,actNameEditID,userNameStaticID,userNameEditID,passwdStaticID,passwdEditID });
			Door::Login();
		}
		break;
		case loginConfirmButtonID: {
			Door::LoginConfirm();
		}
		break;
		case registerButtonID: {
			//销毁控件
			MyWnds::DestroyControl(MyWnds::MainWndProc_hwnd, {loginConfirmButtonID,registerButtonID,userNameStaticID,userNameEditID,passwdStaticID,passwdEditID});
			Door::Register();
		}
		break;
		case registerConfirmButtonID: {
			Door::RegisterConfirm();
		}
		break;
		case homePageButtonID: {
			MyWnds::DestroyChildWnd();
			MyWnds::HomePage();
			//更改窗口风格与标记
			MyWnds::mainWndStyle = HomeUI;
			MyWnds::mainWndFlag = HomeUI;
			//重绘整个窗口
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case actInfoButtonID: {
			MyWnds::DestroyChildWnd();
			Account::ActInfo();
			//更改窗口风格与标记
			MyWnds::mainWndStyle = ActInfoUI;
			MyWnds::mainWndFlag = ActInfoUI;
			//重绘整个窗口
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case devInfoButtonID: {
			MyWnds::DestroyChildWnd();
			Device::DevInfo();
			//更改窗口风格与标记
			MyWnds::mainWndStyle = DevInfoUI;
			MyWnds::mainWndFlag = DevInfoUI;
			//重绘整个窗口
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case tradeInfoButtonID: {
			MyWnds::DestroyChildWnd();
			Trade::TradeInfo();
			//更改窗口风格与标记
			MyWnds::mainWndStyle = TradeInfoUI;
			MyWnds::mainWndFlag = TradeInfoUI;
			//重绘整个窗口
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case exitButtonID: {
			int temp = MessageBox(MyWnds::MainWndProc_hwnd, _T("请选择\n是：退出系统\n否：退出登录"), _T("游乐园管理系统"), MB_YESNOCANCEL);
			if (temp == IDYES)
			{
				DeleteObject(MyWnds::defHBrush);//删除默认画刷
				DeleteObject(MyWnds::defSmallHFont);//删除小字体
				DeleteObject(MyWnds::defMidHFont);//删除中字体
				DeleteObject(MyWnds::defLargeHFont);//删除大字体
				MyWnds::DestroyChildWnd();
				DestroyWindow(MyWnds::MainWndProc_hwnd);//销毁窗口并发送WM_DESTROY消息
			}
			else if (temp == IDNO) {
				MyWnds::DestroyChildWnd();
				MyWnds::DestroyControl(MyWnds::MainWndProc_hwnd, {homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID});
				Door::Login();
			}
		}
		break;
		}
	}
}

void MyWnds::MainWndProc_WM_WINDOWPOSCHANGING(){
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;
	if (temp->cx < 960) {
		temp->cx = 960;
	}//如果新的窗口宽度小于960（像素），设定为960
	if (temp->cy < 540) {
		temp->cy = 540;
	}//如果新的窗口高度小于540（像素），设定为540
}

void MyWnds::MainWndProc_WM_WINDOWPOSCHANGED(){
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;//设定临时指针接收附加信息
	MyWnds::defMainWndWidth = temp->cx;//获取窗口新的宽度
	MyWnds::defMainWndHeight = temp->cy;//获取窗口新的高度
	MyWnds::homePageWidth = int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth);
	MyWnds::homePageHeight = int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight);
	MyWnds::lastfontFlag = MyWnds::fontFlag;
	//调整各控件大小，使其与主窗口大小自适应
	if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; MyWnds::fontFlag = defSmallFont; }
	else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; MyWnds::fontFlag = defMidFont; }
	else { MyWnds::currentHFONT = MyWnds::defLargeHFont; MyWnds::fontFlag = defLargeFont; }
	EnumChildWindows(MyWnds::MainWndProc_hwnd, MyWnds::EnumChildProc_AdaptiveWnd, NULL);
}


void MyWnds::MainWndProc_WM_CLOSE(){
	if (MessageBox(MyWnds::MainWndProc_hwnd, _T("是否确定退出系统？"), _T("游乐园管理系统"), MB_OKCANCEL) == IDOK)
	{
		DeleteObject(MyWnds::defHBrush);//删除默认画刷
		DeleteObject(MyWnds::defSmallHFont);//删除小字体
		DeleteObject(MyWnds::defMidHFont);//删除中字体
		DeleteObject(MyWnds::defLargeHFont);//删除大字体
		DestroyWindow(MyWnds::MainWndProc_hwnd);//销毁窗口并发送WM_DESTROY消息
	}
}

void MyWnds::MainWndProc_WM_DESTROY(){
	PostQuitMessage(0);//发布WM_QUIT消息
}

LRESULT MyWnds::MainWndProc_WM_CTLCOLORSTATIC(){
	MyWnds::hDC = (HDC)MyWnds::MainWndProc_wParam;
	SetTextColor(MyWnds::hDC, RGB(0, 0, 0));//文字前景色
	//SetBkColor(MyWnds::hDC, RGB(174, 214, 241));//文字背景色
	SetBkMode(MyWnds::hDC, TRANSPARENT);//背景透明
	MyWnds::hDC = NULL;
	return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
}

void MyWnds::MainWndProc_WM_PAINT(){
	switch (MyWnds::mainWndStyle) {
	case LoginUI: case RegisterUI:
	{
		//创建临时画刷
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//实例化绘图信息结构体对象
		PAINTSTRUCT ps;
		//获取主窗口的显示设备的环境句柄
		MyWnds::hDC = BeginPaint(MyWnds::MainWndProc_hwnd, &ps);
		//绘制更新区域
		//FillRect(MyWnds::hDC, &ps.rcPaint, defHBrush);
		//绘制中央区域
		RECT center = { int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), int(0.85 * MyWnds::defMainWndWidth), int(0.8 * MyWnds::defMainWndHeight) };
		FillRect(MyWnds::hDC, &center, tempBrush);
		//删除临时画刷
		DeleteObject(tempBrush);
		//释放主窗口的显示设备的环境句柄
		EndPaint(MyWnds::MainWndProc_hwnd, &ps);
		MyWnds::hDC = NULL;
	}
	 break;
	case HomeUI:case ActInfoUI:case DevInfoUI:case TradeInfoUI:
	{
		//创建临时画刷
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//实例化绘图信息结构体对象
		PAINTSTRUCT ps;
		//获取主窗口的显示设备的环境句柄
		MyWnds::hDC = BeginPaint(MyWnds::MainWndProc_hwnd, &ps);
		//绘制更新区域
		//FillRect(MyWnds::hDC, &ps.rcPaint, MyWnds::defHBrush);
		//绘制区域A
		RECT aRECT = { int(homePageButtonCoord_X / 2.0 * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((homePageButtonWidth + homePageButtonCoord_X * 3 / 2.0) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y * 3 / 2.0 + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight) };
		FillRect(MyWnds::hDC, &aRECT, tempBrush);
		//删除临时画刷
		DeleteObject(tempBrush);
		//释放主窗口的显示设备的环境句柄
		EndPaint(MyWnds::MainWndProc_hwnd, &ps);
		MyWnds::hDC = NULL;
	}
	break;
	}
}

WPARAM MyWnds::MainWnd() {
	//实例化窗口类对象---主窗口
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
	mainWndClass.lpfnWndProc = MyWnds::MainWndProc;//窗口过程
	mainWndClass.hInstance = MyWnds::hInstance;//程序实例
	mainWndClass.hbrBackground = MyWnds::defHBrush;//类背景画刷
	mainWndClass.lpszClassName = _T("mainWndClassName");//窗口类名
	mainWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
	//注册窗口类---主窗口
	if (!RegisterClassEx(&mainWndClass)) {
		MessageBox(NULL, _T("注册窗口类---主窗口，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//创建窗口---主窗口
	HWND mainHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT,_T("mainWndClassName"),_T("游乐园管理系统"),WS_TILEDWINDOW,
		int(0.15 * MyWnds::defScreenWidth),int( 0.15 * MyWnds::defScreenHeight), MyWnds::defMainWndWidth, MyWnds::defMainWndHeight,
		NULL,NULL, MyWnds::hInstance,NULL
	);
	if (!mainHwnd) {
		MessageBox(NULL, _T("创建窗口---主窗口，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//显示窗口---主窗口
	ShowWindow(mainHwnd, SW_SHOW);
	//构建消息循环
	MSG Msg = { 0 };
	BOOL bRet = 1;
	while (bRet = (GetMessage(&Msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
		{
			MessageBox(NULL, _T("消息检索失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		else
		{
			if (!IsDialogMessage(mainHwnd, &Msg)) //该函数处理键盘消息(如TAB切换控件焦点)
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
	}
	return Msg.wParam;
}

//销毁子窗口
void MyWnds::DestroyChildWnd() {
	switch (MyWnds::mainWndFlag) {
	case HomeUI: {
		DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID));
	}
	break;
	case ActInfoUI: {
		DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID));
		Account::actInfoSysLinkFlag = 0;
	}
	break;
	case DevInfoUI: {
		DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID));
	}
	break;
	case TradeInfoUI: {
		DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoWndID));
	}
	break;
	}
}

//主页
LRESULT CALLBACK MyWnds::HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	MyWnds::HomePageProc_hwnd = hwnd;
	MyWnds::HomePageProc_uMsg = uMsg;
	MyWnds::HomePageProc_wParam = wParam;
	MyWnds::HomePageProc_lParam = lParam;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//GitHub页面
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"GitHub链接\">https://github.com/ISQIShI/Amusement-Park-Management-System</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
			int(0.23 * MyWnds::homePageWidth), int(0.89 * MyWnds::homePageHeight), int(0.7 * MyWnds::homePageWidth), int(0.03 * MyWnds::homePageHeight),
			MyWnds::HomePageProc_hwnd, HMENU(gitHubSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::HomePageProc_hwnd, gitHubSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

		break;
	}
	case WM_NOTIFY:
	{
		switch (((LPNMHDR)MyWnds::HomePageProc_lParam)->code)
		{
		case NM_CLICK:case NM_RETURN://单击
		{
		case gitHubSysLinkID:
		{
			ShellExecute(NULL, _T("open"), _T("https://github.com/ISQIShI/Amusement-Park-Management-System"), NULL, NULL, SW_SHOW);
			break;
		}
			break;
		}
		}
		break;
	}
	case WM_PAINT:
	{
		TCHAR tempTCHAR[50];
		PAINTSTRUCT ps;
		MyWnds::hDC = BeginPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID), &ps);
		SelectObject(MyWnds::hDC, MyWnds::currentHFONT);
		SetTextColor(MyWnds::hDC, RGB(46, 134, 193));//文字前景色
		//SetBkColor(MyWnds::hDC, RGB(93, 173, 226));//文字背景色
		//SetBkMode(MyWnds::hDC, TRANSPARENT);//背景透明
		TextOut(MyWnds::hDC, int(0.4  * MyWnds::homePageWidth), int(0.1  * MyWnds::homePageHeight), _T("欢迎使用游乐园管理系统"), wcslen(_T("欢迎使用游乐园管理系统")));
		TextOut(MyWnds::hDC, int(0.28 * MyWnds::homePageWidth), int(0.13 * MyWnds::homePageHeight), _T("Welcome to the Amusement Park Management System"), wcslen(_T("Welcome to the Amusement Park Management System")));
		SetTextColor(MyWnds::hDC, RGB(52, 152, 219));//文字前景色

		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.25 * MyWnds::homePageHeight), _T("本系统的主要功能："), wcslen(_T("本系统的主要功能：")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.28 * MyWnds::homePageHeight), _T("普通账户↓"), wcslen(_T("普通账户↓")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.31 * MyWnds::homePageHeight), _T("查询/修改个人信息"), wcslen(_T("查询/修改个人信息")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.34 * MyWnds::homePageHeight), _T("查询游乐园设备信息"), wcslen(_T("查询游乐园设备信息：")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.37 * MyWnds::homePageHeight), _T("查询个人消费记录"), wcslen(_T("查询个人消费记录")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), _T("管理员账户↓"), wcslen(_T("管理员账户↓")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.43 * MyWnds::homePageHeight), _T("查询/修改个人信息"), wcslen(_T("查询/修改个人信息")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.46 * MyWnds::homePageHeight), _T("增加/修改/删除其他用户信息(需要权限高于对方账户)"), wcslen(_T("增加/修改/删除其他用户信息(需要权限高于对方账户)")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.49 * MyWnds::homePageHeight), _T("增加/修改/删除所有设备信息"), wcslen(_T("增加/修改/删除所有设备信息")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.52 * MyWnds::homePageHeight), _T("增加/修改/删除所有交易记录"), wcslen(_T("增加/修改/删除所有交易记录")));

		SetTextColor(MyWnds::hDC, RGB(46, 134, 193));//文字前景色
		TextOut(MyWnds::hDC, int(0.39 * MyWnds::homePageWidth), int(0.8  * MyWnds::homePageHeight), _T("本项目为大一下期课设项目"), wcslen(_T("本项目为大一下期课设项目")));
		TextOut(MyWnds::hDC, int(0.41 * MyWnds::homePageWidth), int(0.83 * MyWnds::homePageHeight), _T("Created By ISQIShI"), wcslen(_T("Created By ISQIShI")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.86 * MyWnds::homePageHeight), _T("项目详情请点击下方链接，进入我的GitHub页面查看"), wcslen(_T("项目详情请点击下方链接，进入我的GitHub页面查看")));

		EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID), &ps);
		MyWnds::hDC = NULL;
		break;
	}
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::HomePage(){
	//创建窗口---主页
	HWND homePageHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("homePageClassName"), _T("主页"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(homePageWndID), MyWnds::hInstance, NULL
	);
	if (!homePageHwnd) {
		//实例化窗口类对象---主页
		WNDCLASSEX homePageClass = { 0 };
		homePageClass.cbSize = sizeof(WNDCLASSEX);
		homePageClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		homePageClass.lpfnWndProc = MyWnds::HomePageProc;//窗口过程
		homePageClass.hInstance = MyWnds::hInstance;//程序实例
		homePageClass.hbrBackground = HBRUSH(6);//类背景画刷
		homePageClass.lpszClassName = _T("homePageClassName");//窗口类名
		homePageClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---主页
		if (!RegisterClassEx(&homePageClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---主页，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//创建窗口---主页
		homePageHwnd = CreateWindowEx(
			WS_EX_CONTROLPARENT, _T("homePageClassName"), _T("主页"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(homePageWndID), MyWnds::hInstance, NULL
		);
		if (!homePageHwnd) {
			MessageBox(NULL, _T("创建窗口---主页，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//创建模态对话框
LRESULT CALLBACK MyWnds::DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::DialogProc_hwnd = hwnd;
	MyWnds::DialogProc_uMsg = uMsg;
	MyWnds::DialogProc_wParam = wParam;
	MyWnds::DialogProc_lParam = lParam;

	switch (uMsg)
	{
	case WM_WINDOWPOSCHANGING:
	{
		WINDOWPOS* temp = (WINDOWPOS*)MyWnds::DialogProc_lParam;
		if (dialogFlag == dialogTradeSelect) {
			temp->cx = int(0.7 * MyWnds::defMainWndWidth);
			temp->cy = int(0.8 * MyWnds::defMainWndHeight);
		}
		else {
			temp->cx = int(0.7 * MyWnds::defMainWndHeight);
			temp->cy = int(0.8 * MyWnds::defMainWndHeight);
		}
	}
	break;
	case WM_COMMAND:
	{
		if (HIWORD(MyWnds::DialogProc_wParam) == BN_CLICKED) {
			switch (LOWORD(MyWnds::DialogProc_wParam)) {
			case confirmButtonID: {
				switch (dialogFlag) {
				case dialogActAdd: case dialogActModify:
				{
					TCHAR tempTCHAR[21];
					Account tempAct = { 0 };//存放用户数据
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), tempAct.mName, actName);//获取用户昵称
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), tempAct.mID, actUserName);//获取用户名
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), tempAct.mPasswd, actPasswd);//获取密码
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID)));//获取权限
					if ( !(*tempAct.mName)|| !(*tempAct.mID) || !(*tempAct.mPasswd) || !(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					tempAct.mPer.mAdmin = _wtoi(tempTCHAR);
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID)));//获取余额
					if (!(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					if (dialogFlag == dialogActAdd && Data<Account>::DataSearch(_T("Account.dat"), tempAct.mID)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您输入的用户名已存在，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					if (MyWnds::currentAct.mPer.mAdmin <= tempAct.mPer.mAdmin) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("设定的权限应小于您的权限"), _T("权限不足"), MB_ICONERROR);
						return 0;
					}
					tempAct.mCredit = _wtoi(tempTCHAR);
					//获取系统时间&设定录入时间
					SYSTEMTIME sysTime;
					GetLocalTime(&sysTime);
					_stprintf_s(tempAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
					_stprintf_s(tempAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
					if(dialogFlag == dialogActAdd) Data<Account>::DataAdd(_T("Account.dat"), tempAct);	//调用函数创建用户
					else Data<Account>::DataModify(_T("Account.dat"), tempAct);//调用函数修改用户
					//使用主窗口
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//销毁窗口并发送WM_DESTROY消息
					DestroyWindow(hwnd);
					break;
				}
				
				case dialogDevAdd: case dialogDevModify:
				{
					TCHAR tempTCHAR[21];
					Device tempDev = { 0 };//存放设备数据
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), tempDev.mName, devName);//获取设备名称
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), tempDev.mID, devID);//获取设备ID
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID)));//获取价格
					if (!(*tempDev.mName) || !(*tempDev.mID) || !(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					tempDev.mPrice = _wtoi(tempTCHAR);
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID)));//获取收费
					if (!(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					if (dialogFlag == dialogDevAdd && Data<Device>::DataSearch(_T("Device.dat"), tempDev.mID)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您输入的设备ID已存在，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					tempDev.mCharge = _wtoi(tempTCHAR);
					//获取系统时间&设定录入时间
					SYSTEMTIME sysTime;
					GetLocalTime(&sysTime);
					_stprintf_s(tempDev.mAddTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
					_stprintf_s(tempDev.mAddTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
					if (dialogFlag == dialogDevAdd) Data<Device>::DataAdd(_T("Device.dat"), tempDev);	//调用函数创建设备
					else Data<Device>::DataModify(_T("Device.dat"), tempDev);//调用函数修改设备
					//使用主窗口
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//销毁窗口并发送WM_DESTROY消息
					DestroyWindow(hwnd);
					break;
				}
				case dialogTradeAdd: case dialogTradeModify:
				{
					TCHAR tempTCHAR[21];
					Trade tempTrade = { 0 };//存放交易数据
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), tempTrade.mID, tradeID);//获取设备ID
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID)));//获取交易金额
					if (!(*tempTrade.mID) || !(*tempTCHAR)|| ComboBox_GetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID)) == -1 || ComboBox_GetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID)) == -1) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					
					if (dialogFlag == dialogTradeAdd && Data<Trade>::DataSearch(_T("Trade.dat"), tempTrade.mID)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("您输入的交易ID已存在，请重新输入"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					tempTrade.mMoney = _wtoi(tempTCHAR);
					ComboBox_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), tempTrade.mUserName, actUserName);
					ComboBox_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), tempTrade.mDevID, devID);
					SYSTEMTIME tempTime;
					DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), &tempTime);
					_stprintf_s(tempTrade.mTime.mDate, _T("%04d-%02d-%02d"), tempTime.wYear, tempTime.wMonth, tempTime.wDay);
					DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), &tempTime);
					_stprintf_s(tempTrade.mTime.mMoment, _T("%02d:%02d:%02d"), tempTime.wHour, tempTime.wMinute, tempTime.wSecond);
					if (dialogFlag == dialogTradeAdd) Data<Trade>::DataAdd(_T("Trade.dat"), tempTrade);	//调用函数创建交易记录
					else Data<Trade>::DataModify(_T("Trade.dat"), tempTrade);//调用函数修改交易记录
					//使用主窗口
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//销毁窗口并发送WM_DESTROY消息
					DestroyWindow(hwnd);
					break;
				}
				case dialogTradeSelect:
				{
					int y;
					bool flag = 0;
					TCHAR tempTCHAR[31] = {}, _tempTCHAR[31] = {};
					if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 3) && ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 4)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("不允许同时按用户总消费和设备总收入筛选"), _T("错误"), MB_ICONERROR);
						return 0;
					}
					//从前往后读取筛选列表的选项选择状态（不可随意更改顺序，后面的筛选依赖前面的筛选）
					for ( y = 0; y < ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID)); ++y) {
						if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), y)) {
							//获取筛选选项
							ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), y, 0, tempTCHAR, 21 );
							if (!_tcscmp(tempTCHAR, _T("按用户"))) {
								//对交易记录列表从后向前按用户删除(这样删除后面的记录前面的记录的索引不变)
								for (int yy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; yy >= 0; --yy) {
									//获取当前记录的用户名
									ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy, 3, tempTCHAR, actUserName );
									for (int yyy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID)) - 1; yyy >= 0; --yyy) {
										if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yyy)) {
											//获取筛选列表中选定的用户名
											ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yyy, 0, _tempTCHAR, actUserName );
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) { flag = 1; break; }
										}
									}
									//如果符合筛选条件，跳过该记录
									if (flag) { flag = 0; continue; }
									//不符合，删除记录
									ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy);
								}
							}
							else if (!_tcscmp(tempTCHAR, _T("按设备"))) {
								//对交易记录列表从后向前按设备删除(这样删除后面的记录前面的记录的索引不变)
								for (int yy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; yy >= 0; --yy) {
									//获取当前记录的设备ID
									ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy, 4, tempTCHAR, devID );
									for (int yyy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID)) - 1; yyy >= 0; --yyy) {
										if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yyy)) {
											//获取筛选列表中选定的设备ID
											ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yyy, 0, _tempTCHAR, devID );
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) { flag = 1; break; }
										}
									}
									//如果符合筛选条件，跳过该记录
									if (flag) { flag = 0; continue; }
									//不符合，删除记录
									ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy);
								}
							}
							else if (!_tcscmp(tempTCHAR, _T("按时间"))) {
								//对交易记录列表从后向前按时间删除(这样删除后面的记录前面的记录的索引不变)
								for (int yy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; yy >= 0; --yy) {
									//获取当前记录的时间
									ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy, 5, tempTCHAR, timeDate + timeMoment);
									TCHAR tempTimeA[timeDate + timeMoment] = {}, tempTimeB[timeDate + timeMoment] = {};
									//起始时间
									SYSTEMTIME tempTime;
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), &tempTime);
									_stprintf_s(tempTimeA, _T("%04d-%02d-%02d"), tempTime.wYear, tempTime.wMonth, tempTime.wDay);
									wcscat_s(tempTimeA, _T(" "));
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), &tempTime);
									_stprintf_s(_tempTCHAR, _T("%02d:%02d:%02d"), tempTime.wHour, tempTime.wMinute, tempTime.wSecond);
									wcscat_s(tempTimeA, _tempTCHAR);
									//终止时间
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateBTimeID), &tempTime);
									_stprintf_s(tempTimeB, _T("%04d-%02d-%02d"), tempTime.wYear, tempTime.wMonth, tempTime.wDay);
									wcscat_s(tempTimeB, _T(" "));
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentBTimeID), &tempTime);
									_stprintf_s(_tempTCHAR, _T("%02d:%02d:%02d"), tempTime.wHour, tempTime.wMinute, tempTime.wSecond);
									wcscat_s(tempTimeB, _tempTCHAR);

									//如果符合筛选条件，跳过该记录
									if (_tcscmp(tempTCHAR,tempTimeA)>=0 && _tcscmp(tempTCHAR,tempTimeB)<=0) continue;
									//不符合，删除记录
									ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy);
								}
							}
							else if (!_tcscmp(tempTCHAR, _T("按用户总消费"))) {
								int consume = 0;//游乐场总收入
								int itemCount = 0;
								//增加新的一列--用户总消费
								LVCOLUMN temp = { 0 };
								temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
								temp.fmt = LVCFMT_CENTER;
								temp.cx = int(0.2 * MyWnds::homePageWidth);
								temp.pszText = (LPTSTR)_T("用户总消费");
								temp.iSubItem = 6;
								temp.cxDefault = 1;
								temp.cxMin = int(0.2 * MyWnds::homePageWidth);
								ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 6, &temp);
								LVITEM tempINSERT = { 0 };
								tempINSERT.mask = LVIF_TEXT;
								//读取用户选择列表的每一个用户
								for (int yy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID)) - 1; yy >= 0; --yy) {
									//如果没选按用户，计算并显示每个用户的消费总额。如果选了按用户，只显示选择的用户的消费总额。
									if (!ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 0) || (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 0) && ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yy))) {
										//获取筛选列表中选定的用户名
										UINT totalConsume = 0;
										ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yy, 0, tempTCHAR, actUserName);
										for (int yyy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1 - itemCount; yyy >= 0; --yyy) {
											//获取当前记录的用户名
											ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 3, _tempTCHAR, actUserName);
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) {
												//获取交易金额
												ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 2, _tempTCHAR, 11);
												totalConsume += _wtoi(_tempTCHAR);
												//记录完该交易数据便删除这条记录
												ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy);
											}
										}
										consume += totalConsume;
										//在列表末尾插入新的数据
										tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
										tempINSERT.iSubItem = 0;
										_stprintf_s(_tempTCHAR, _T("%d"), 0);
										tempINSERT.pszText = _tempTCHAR;
										ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//用户名
										tempINSERT.iSubItem = 3;
										tempINSERT.pszText = tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//总消费
										tempINSERT.iSubItem = 6;
										_stprintf_s(_tempTCHAR, _T("%d"), totalConsume);
										tempINSERT.pszText = _tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);										
										++itemCount;
									}
								}
								//在列表末尾插入游乐场总消费
								tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
								tempINSERT.iSubItem = 0;
								_stprintf_s(_tempTCHAR, _T("%d"), 0);
								tempINSERT.pszText = _tempTCHAR;
								ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//用户名
								tempINSERT.iSubItem = 3;
								tempINSERT.pszText = (LPTSTR)_T("总消费");
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//总消费
								tempINSERT.iSubItem = 6;
								_stprintf_s(_tempTCHAR, _T("%d"), consume);
								tempINSERT.pszText = _tempTCHAR;
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//删除不需要的列
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 5);//交易时间
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 4);//设备ID
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 2);//金额
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 1);//交易ID
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 0);//序号
							}
							else if (!_tcscmp(tempTCHAR, _T("按设备总收入"))) {
								int income = 0;//游乐场总收入
								int itemCount = 0;
								//增加新的一列--设备总收入
								LVCOLUMN temp = { 0 };
								temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
								temp.fmt = LVCFMT_CENTER;
								temp.cx = int(0.2 * MyWnds::homePageWidth);
								temp.pszText = (LPTSTR)_T("设备总收入");
								temp.iSubItem = 6;
								temp.cxDefault = 1;
								temp.cxMin = int(0.2 * MyWnds::homePageWidth);
								ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 6, &temp);
								LVITEM tempINSERT = { 0 };
								tempINSERT.mask = LVIF_TEXT;
								//读取设备选择列表的每一个设备
								for (int yy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID)) - 1; yy >= 0; --yy) {
									//如果没选按设备，计算并显示每个设备的收入总额。如果选了按设备，只显示选择的设备的收入总额。
									if (!ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 1) || (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 1) && ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yy))) {
										//获取筛选列表中选定的设备ID
										UINT totalIncome = 0;
										ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yy, 0, tempTCHAR, devID);
										for (int yyy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1 - itemCount; yyy >= 0; --yyy) {
											//获取当前记录的设备ID
											ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 4, _tempTCHAR, devID);
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) {
												//获取交易金额
												ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 2, _tempTCHAR, 11);
												totalIncome += _wtoi(_tempTCHAR);
												//记录完该交易数据便删除这条记录
												ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy);
											}
										}
										income += totalIncome;
										//在列表末尾插入新的数据
										tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
										tempINSERT.iSubItem = 0;
										_stprintf_s(_tempTCHAR, _T("%d"), 0);
										tempINSERT.pszText = _tempTCHAR;
										ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//设备ID
										tempINSERT.iSubItem = 4;
										tempINSERT.pszText = tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//总收入
										tempINSERT.iSubItem = 6;
										_stprintf_s(_tempTCHAR, _T("%d"), totalIncome);
										tempINSERT.pszText = _tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										++itemCount;
									}
								}
								//在列表末尾插入总收入
								tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
								tempINSERT.iSubItem = 0;
								_stprintf_s(_tempTCHAR, _T("%d"), 0);
								tempINSERT.pszText = _tempTCHAR;
								ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//设备ID
								tempINSERT.iSubItem = 4;
								tempINSERT.pszText = (LPTSTR)_T("总收入");
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//总收入
								tempINSERT.iSubItem = 6;
								_stprintf_s(_tempTCHAR, _T("%d"), income);
								tempINSERT.pszText = _tempTCHAR;
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//删除不需要的列
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 5);//交易时间
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 3);//用户名
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 2);//金额
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 1);//交易ID
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 0);//序号
							}
						}
					}
					ShowWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, tradeSelectSysLinkID), SW_HIDE);
					ShowWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoSysLinkID), SW_HIDE);
					//返回
					CreateWindowEx(
						0, _T("SysLink"), _T("<A HREF=\"返回\">返回</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
						int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
						Trade::TradeInfoProc_hwnd, HMENU(returnSysLinkID), MyWnds::hInstance, NULL
					);
					SendMessage(GetDlgItem(Trade::TradeInfoProc_hwnd, returnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

					//使用主窗口
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//销毁窗口并发送WM_DESTROY消息
					DestroyWindow(hwnd);
					break;
				}
				}
			}
			break;
			case cancelButtonID: {
				if (MessageBox(MyWnds::DialogProc_hwnd, _T("关闭对话框？"), _T("游乐园管理系统"), MB_OKCANCEL) == IDOK)
				{
					//使用主窗口
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//销毁窗口并发送WM_DESTROY消息
					DestroyWindow(hwnd);
				}
			}
			break;
			}
		}
	}
	break;
	case WM_CLOSE:
	{
		if (MessageBox(MyWnds::DialogProc_hwnd, _T("关闭对话框？"), _T("游乐园管理系统"), MB_OKCANCEL) == IDOK)
		{
			//使用主窗口
			EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
			//销毁窗口并发送WM_DESTROY消息
			DestroyWindow(hwnd);
		}
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);//发布WM_QUIT消息
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		MyWnds::hDC = (HDC)MyWnds::DialogProc_wParam;
		SetTextColor(MyWnds::hDC, RGB(0, 0, 0));//文字前景色
		//SetBkColor(MyWnds::hDC, RGB(174, 214, 241));//文字背景色
		SetBkMode(MyWnds::hDC, TRANSPARENT);
		MyWnds::hDC = NULL;
		return (INT_PTR)MyWnds::defHBrush;
	}
	break;
	case WM_CREATE:
	{
		switch (dialogFlag) {
		case dialogActAdd:
			MyWnds::DialogActAdd();
			break;
		case dialogActModify:
			MyWnds::DialogActModify();
			break;
		case dialogDevAdd:
			MyWnds::DialogDevAdd();
			break;
		case dialogDevModify:
			MyWnds::DialogDevModify();
			break;
		case dialogTradeAdd:
			MyWnds::DialogTradeAdd();
			break;
		case dialogTradeModify:
			MyWnds::DialogTradeModify();
			break;
		case dialogTradeSelect:
			MyWnds::DialogTradeSelect();
			break;
		}
	}
	break;
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;

}

void MyWnds::DialogActAdd() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	//昵称
	CreateWindowEx(
		0, WC_STATIC, _T("昵称"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight),int(0.1 * DialogWidth),int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), _T("请输入用户昵称"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), actName - 1); //限制可在编辑控件中输入的用户昵称的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//用户名
	CreateWindowEx(
		0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), _T("请输入用户名"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), actUserName - 1); //限制可在编辑控件中输入的用户名的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//密码
	CreateWindowEx(
		0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), _T("请输入密码"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), actPasswd - 1); //限制可在编辑控件中输入的密码的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//权限
	CreateWindowEx(
		0, WC_STATIC, _T("权限"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actPerStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actPerEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), _T("请输入权限"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), 3); //限制可在编辑控件中输入的权限的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//余额
	CreateWindowEx(
		0, WC_STATIC, _T("余额"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.71 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("请输入余额"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), 10); //限制可在编辑控件中输入的余额的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogActModify() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Account tempAct = { 0 };//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	TCHAR tempTCHAR[21] = {};
	//获取点击位置的用户信息
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	//文件指针移动到该用户数据之前
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = (long long)(sizeof(Account)) * MyWnds::y_Listview;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
	CloseHandle(tempHANDLE);//关闭文件
	//昵称
	CreateWindowEx(
		0, WC_STATIC, _T("昵称"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), _T("请输入用户昵称"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), actName - 1); //限制可在编辑控件中输入的用户名的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//用户名
	CreateWindowEx(
		0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mID, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetReadOnly(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), TRUE);//设置只读状态
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//密码
	CreateWindowEx(
		0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), _T("请输入密码"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), actPasswd - 1); //限制可在编辑控件中输入的密码的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//权限
	CreateWindowEx(
		0, WC_STATIC, _T("权限"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actPerStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	_stprintf_s(tempTCHAR, _T("%d"), tempAct.mPer.mAdmin);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actPerEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), _T("请输入权限"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), 3); //限制可在编辑控件中输入的权限的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//余额
	CreateWindowEx(
		0, WC_STATIC, _T("余额"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.71 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	_stprintf_s(tempTCHAR, _T("%d"), tempAct.mCredit);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("请输入余额"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), 10); //限制可在编辑控件中输入的余额的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

}

void MyWnds::DialogDevAdd() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	//设备名称
	CreateWindowEx(
		0, WC_STATIC, _T("设备名称"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), _T("请输入设备名称"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), devName - 1); //限制可在编辑控件中输入的设备名称的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//设备ID
	CreateWindowEx(
		0, WC_STATIC, _T("设备ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), _T("请输入设备ID"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), devID - 1); //限制可在编辑控件中输入的设备ID的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//价格
	CreateWindowEx(
		0, WC_STATIC, _T("价格"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devPriceStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devPriceEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), _T("请输入价格"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), 10); //限制可在编辑控件中输入的价格的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//收费
	CreateWindowEx(
		0, WC_STATIC, _T("收费"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devChargeStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devChargeEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), _T("请输入收费"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), 10); //限制可在编辑控件中输入的收费的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogDevModify() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Device tempDev = { 0 };//存放将要读取的设备数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	TCHAR tempTCHAR[21] = {};
	//获取点击位置的设备信息
	HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	//文件指针移动到该设备数据之前
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = (long long)(sizeof(Device)) * MyWnds::y_Listview;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//读取文件
	CloseHandle(tempHANDLE);//关闭文件
	//设备名称
	CreateWindowEx(
		0, WC_STATIC, _T("设备名称"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempDev.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), _T("请输入设备名称"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), devName - 1); //限制可在编辑控件中输入的设备名称的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//设备ID
	CreateWindowEx(
		0, WC_STATIC, _T("设备ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempDev.mID, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDEditID), MyWnds::hInstance, NULL
	);
	Edit_SetReadOnly(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), TRUE);//设置只读状态
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//价格
	CreateWindowEx(
		0, WC_STATIC, _T("价格"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devPriceStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	_stprintf_s(tempTCHAR, _T("%d"), tempDev.mPrice);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devPriceEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), _T("请输入价格"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), 10); //限制可在编辑控件中输入的价格的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//收费
	CreateWindowEx(
		0, WC_STATIC, _T("收费"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devChargeStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	_stprintf_s(tempTCHAR, _T("%d"), tempDev.mCharge);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devChargeEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), _T("请输入收费"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), 10); //限制可在编辑控件中输入的收费的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogTradeAdd(){
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	//交易ID
	CreateWindowEx(
		0, WC_STATIC, _T("交易ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeIDEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), _T("请输入交易ID"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), tradeID - 1); //限制可在编辑控件中输入的交易ID的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//交易金额
	CreateWindowEx(
		0, WC_STATIC, _T("金额"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.05 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMoneyStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMoneyEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), _T("请输入交易金额"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), 10); //限制可在编辑控件中输入的交易金额的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//用户名
	CreateWindowEx(
		0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		0, WC_COMBOBOX, _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST| WS_VSCROLL,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.5 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameComboBoxID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//向组合框中添加所有用户信息
	Account tempAct;//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), tempAct.mID);
	}
	CloseHandle(tempHANDLE);//关闭文件
	//设备ID
	CreateWindowEx(
		0, WC_STATIC, _T("设备ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		0, WC_COMBOBOX, _T(""), WS_CHILD | WS_VISIBLE  | CBS_DROPDOWNLIST| WS_VSCROLL,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.5 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDComboBoxID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	Device tempDev;//存放将要读取的设备数据
	tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//读取文件
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), tempDev.mID);
	}
	CloseHandle(tempHANDLE);//关闭文件
	//交易时间
	CreateWindowEx(
		0, WC_STATIC, _T("交易时间"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.71 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeAStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeAStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//日期
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE ,
		int(0.2 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//时刻
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.52 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogTradeModify(){
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Trade tempTrade = { 0 };//存放将要读取的交易数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	TCHAR tempTCHAR[21] = {};
	//获取点击位置的交易记录
	HANDLE tempHANDLE = CreateFile(_T("Trade.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	//文件指针移动到该交易数据之前
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = (long long)(sizeof(Trade)) * MyWnds::y_Listview;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	ReadFile(tempHANDLE, &tempTrade, sizeof(Trade), &tempDWORD, NULL);//读取文件
	CloseHandle(tempHANDLE);//关闭文件
	//交易ID
	CreateWindowEx(
		0, WC_STATIC, _T("交易ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempTrade.mID, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP | ES_READONLY,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeIDEditID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//交易金额
	CreateWindowEx(
		0, WC_STATIC, _T("金额"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.05 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMoneyStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	_stprintf_s(tempTCHAR, _T("%d"), tempTrade.mMoney);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMoneyEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), _T("请输入交易金额"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), 10); //限制可在编辑控件中输入的交易金额的长度
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//用户名
	CreateWindowEx(
		0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		0, WC_COMBOBOX, _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.5 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameComboBoxID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//向组合框中添加所有用户信息
	Account tempAct;//存放将要读取的用户数据
	tempDWORD = 0;//存放实际读取的字节数
	int index = 0;//记录所选数据的索引
	tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), tempAct.mID);
		if (!_tcscmp(tempAct.mID, tempTrade.mUserName)) index = x;
	}
	CloseHandle(tempHANDLE);//关闭文件
	ComboBox_SetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), index);
	//设备ID
	CreateWindowEx(
		0, WC_STATIC, _T("设备ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		0, WC_COMBOBOX, _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.5 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDComboBoxID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	Device tempDev;//存放将要读取的设备数据
	tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//读取文件
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), tempDev.mID);
		if (!_tcscmp(tempDev.mID, tempTrade.mDevID)) index = x;
	}
	CloseHandle(tempHANDLE);//关闭文件
	ComboBox_SetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), index);
	//交易时间
	CreateWindowEx(
		0, WC_STATIC, _T("交易时间"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.71 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeAStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeAStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//日期
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE,
		int(0.2 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	SYSTEMTIME tempTime = {0};
	tempTime.wYear = _wtoi(tempTrade.mTime.mDate);
	tempTime.wMonth = _wtoi(tempTrade.mTime.mDate + 5);
	tempTime.wDay = _wtoi(tempTrade.mTime.mDate + 8);
	tempTime.wHour = _wtoi(tempTrade.mTime.mMoment);
	tempTime.wMinute = _wtoi(tempTrade.mTime.mMoment + 3);
	tempTime.wSecond = _wtoi(tempTrade.mTime.mMoment + 6);
	DateTime_SetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), GDT_VALID, &tempTime);
	//时刻
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.52 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	DateTime_SetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), GDT_VALID, &tempTime);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogTradeSelect(){
	int DialogWidth = int(0.7 * MyWnds::defMainWndWidth), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	
	//筛选选项
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.1 * DialogWidth), int(0.05 * DialogHeight), int(0.2 * DialogWidth), int(0.25 * DialogHeight),
		MyWnds::DialogProc_hwnd, (HMENU)selectListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//插入列
	LVCOLUMN temp = { 0 };
	temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
	temp.fmt = LVCFMT_CENTER;
	temp.cx = int(0.2 * DialogWidth);
	temp.pszText = (LPTSTR)_T("筛选选项");
	temp.iSubItem = 0;
	temp.cxDefault = 0;
	temp.cxMin = int(0.2 * DialogWidth);
	ListView_InsertColumn(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 0, &temp);
	//插入行
	LVITEM tempINSERT = { 0 };
	tempINSERT.mask = LVIF_TEXT;
	tempINSERT.iItem = 0;
	tempINSERT.iSubItem = 0;
	tempINSERT.pszText = (LPTSTR)_T("按用户");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("按设备");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("按时间");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("按用户总消费");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("按设备总收入");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	//起始时间
	CreateWindowEx(
		0, WC_STATIC, _T("起始时间"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.1 * DialogWidth), int(0.33 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeAStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeAStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//日期
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE,
		int(0.1 * DialogWidth), int(0.37 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//时刻
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.1 * DialogWidth), int(0.42 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//终止时间
	CreateWindowEx(
		0, WC_STATIC, _T("终止时间"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.1 * DialogWidth), int(0.48 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeBStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeBStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//日期
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE,
		int(0.1 * DialogWidth), int(0.52 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateBTimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateBTimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//时刻
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.1 * DialogWidth), int(0.57 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentBTimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentBTimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);


	//用户名
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.4 * DialogWidth), int(0.05 * DialogHeight), int(0.2 * DialogWidth), int(0.8 * DialogHeight),
		MyWnds::DialogProc_hwnd, (HMENU)userNameSelectListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//插入列
	temp.pszText = (LPTSTR)_T("用户名");
	temp.cxDefault = 0;
	ListView_InsertColumn(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), 0, &temp);
	Account tempAct;//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	int index = 0;//记录所选数据的索引
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
		if (!tempDWORD)break;
		tempINSERT.iItem = x;
		tempINSERT.iSubItem = 0;
		tempINSERT.pszText = tempAct.mID;
		ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), &tempINSERT);
	}
	CloseHandle(tempHANDLE);//关闭文件


	//设备ID
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.7 * DialogWidth), int(0.05 * DialogHeight), int(0.2 * DialogWidth), int(0.8 * DialogHeight),
		MyWnds::DialogProc_hwnd, (HMENU)devIDSelectListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//插入列
	temp.pszText = (LPTSTR)_T("设备ID");
	temp.cxDefault = 0;
	ListView_InsertColumn(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), 0, &temp);
	Device tempDev;//存放将要读取的设备数据
	tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//读取文件
		if (!tempDWORD)break;
		tempINSERT.iItem = x;
		tempINSERT.iSubItem = 0;
		tempINSERT.pszText = tempDev.mID;
		ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), &tempINSERT);
	}
	CloseHandle(tempHANDLE);//关闭文件

	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.1 * DialogWidth), int(0.67 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.1 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

}



WPARAM MyWnds::Dialog() {
	int x, y, cx, cy;
	if (dialogFlag == dialogTradeSelect) {
		x = int(0.3 * MyWnds::defScreenWidth);
		y = int(0.2 * MyWnds::defScreenHeight);
		cx = int(0.7 * MyWnds::defMainWndWidth);
		cy = int(0.8 * MyWnds::defMainWndHeight);
	}
	else {
		x = int(0.45 * MyWnds::defScreenWidth);
		y = int(0.2 * MyWnds::defScreenHeight);
		cx = int(0.7 * MyWnds::defMainWndHeight);
		cy = int(0.8 * MyWnds::defMainWndHeight);
	}
	//创建对话框
	HWND dialogHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("dialogClassName"), _T("对话框"), WS_TILEDWINDOW | WS_VISIBLE ,
		x, y, cx, cy,
		MyWnds::MainWndProc_hwnd, NULL, MyWnds::hInstance, NULL
	);
	if (!dialogHwnd) {
		//实例化窗口类对象---对话框
		WNDCLASSEX dialogClass = { 0 };
		dialogClass.cbSize = sizeof(WNDCLASSEX);
		dialogClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		dialogClass.lpfnWndProc = MyWnds::DialogProc;//窗口过程
		dialogClass.hInstance = MyWnds::hInstance;//程序实例
		dialogClass.hbrBackground = HBRUSH(6);//类背景画刷
		dialogClass.lpszClassName = _T("dialogClassName");//窗口类名
		dialogClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---对话框
		if (!RegisterClassEx(&dialogClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---对话框，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//创建窗口---对话框
		dialogHwnd = CreateWindowEx(
			WS_EX_CONTROLPARENT, _T("dialogClassName"), _T("对话框"), WS_TILEDWINDOW | WS_VISIBLE,
			x, y, cx, cy,
			MyWnds::MainWndProc_hwnd, NULL, MyWnds::hInstance, NULL
		);
		if (!dialogHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---对话框，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
	//禁用主窗口
	EnableWindow(MyWnds::MainWndProc_hwnd, FALSE);
	//构建消息循环
	MSG Msg = { 0 };
	BOOL bRet = 1;
	while (bRet = (GetMessage(&Msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
		{
			MessageBox(MyWnds::MainWndProc_hwnd, _T("消息检索失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		else
		{
			if (!IsDialogMessage(dialogHwnd, &Msg)) //该函数处理键盘消息
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
		}
	}
	//强制主窗口显示在前台
	ShowWindowAsync(MyWnds::MainWndProc_hwnd, SW_HIDE);
	ShowWindowAsync(MyWnds::MainWndProc_hwnd, SW_SHOW);
	return Msg.wParam;
}


//创建登录按钮
void MyWnds::createLoginButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("已有账号？点此登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建登录确认按钮
void MyWnds::createLoginConfirmButton() {
	CreateWindowEx(
		0, WC_BUTTON, _T("登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.27 * MyWnds::MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建注册按钮
void MyWnds::createRegisterButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("没有账号？点此注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建注册确认按钮
void MyWnds::createRegisterConfirmButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建主页按钮
void MyWnds::createHomePageButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("主页"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(homePageButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建用户信息按钮
void MyWnds::createActInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("用户信息"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建设备信息按钮
void MyWnds::createDevInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("设备信息"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(devInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建交易记录按钮
void MyWnds::createTradeInfoButton(){
	TCHAR tempTCHAR[5] = _T("消费记录");//普通用户显示消费记录
	if (MyWnds::currentAct.mPer.mAdmin) {
		_stprintf_s(tempTCHAR, _T("交易记录"));//有管理权限的用户显示交易记录
	}
	CreateWindowEx(
		0, WC_BUTTON, tempTCHAR , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建退出系统按钮
void MyWnds::createExitButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("退出系统"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(exitButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

//创建用户名输入框
void MyWnds::createUserNameEdit_Static(){
	CreateWindowEx(
		0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL| WS_TABSTOP,
		int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), _T("请输入用户名"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), actUserName - 1); //限制可在编辑控件中输入的用户名的长度
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建密码输入框
void MyWnds::createPasswdEdit_Static(){
	CreateWindowEx(
		0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD| WS_TABSTOP,
		int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), _T("请输入密码"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), actPasswd - 1); //限制可在编辑控件中输入的密码的长度
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建用户昵称输入框
void MyWnds::createActNameEdit_Static(){
	CreateWindowEx(
		0, WC_STATIC, _T("昵称"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.285 * MyWnds::defMainWndWidth), int(0.21 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), _T("请输入用户昵称"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), actName - 1); //限制可在编辑控件中输入的用户名的长度
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

//枚举所有子窗口（自适应大小和字体）
BOOL CALLBACK MyWnds::EnumChildProc_AdaptiveWnd(HWND hwndChild, LPARAM lParam) {
	
	if (MyWnds::lastfontFlag != MyWnds::fontFlag) {
		//更新字体
		SendMessage(hwndChild, WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		//重绘整个窗口
		InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	//更新大小
	switch (GetDlgCtrlID(hwndChild))
	{
	case loginConfirmButtonID:
		MoveWindow(hwndChild, int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), TRUE);
		break;
	case registerButtonID:
		MoveWindow(hwndChild, int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), TRUE);
		break;
	case userNameStaticID:
		MoveWindow(hwndChild, int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), TRUE);
		break;
	case userNameEditID:
		MoveWindow(hwndChild, int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), TRUE);
		break;
	case passwdStaticID:
		MoveWindow(hwndChild, int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), TRUE);
		break;
	case passwdEditID:
		MoveWindow(hwndChild, int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), TRUE);
		break;
	case loginButtonID:
		MoveWindow(hwndChild, int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), TRUE);
		break;
	case registerConfirmButtonID:
		MoveWindow(hwndChild, int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), TRUE);
		break;
	case actNameStaticID:
		MoveWindow(hwndChild, int(0.285 * MyWnds::defMainWndWidth), int(0.21 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), TRUE);
		break;
	case actNameEditID:
		MoveWindow(hwndChild, int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), TRUE);
		break;
	case homePageButtonID:
		MoveWindow(hwndChild, int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), TRUE);
		break;
	case actInfoButtonID:
		MoveWindow(hwndChild, int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), TRUE);
		break;
	case devInfoButtonID:
		MoveWindow(hwndChild, int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), TRUE);
		break;
	case tradeInfoButtonID:
		MoveWindow(hwndChild, int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), TRUE);
		break;
	case exitButtonID:
		MoveWindow(hwndChild, int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), TRUE);
		break;

	case homePageWndID://主页
		MoveWindow(hwndChild, int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, TRUE);
		break;
	case gitHubSysLinkID:
		MoveWindow(hwndChild, int(0.23 * MyWnds::homePageWidth), int(0.89 * MyWnds::homePageHeight), int(0.7 * MyWnds::homePageWidth), int(0.03 * MyWnds::homePageHeight), TRUE);
		break;

	case actInfoWndID://用户信息
		MoveWindow(hwndChild, int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, TRUE);
		break;
	case editActNameSysLinkID:
		MoveWindow(hwndChild, int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case editPasswdSysLinkID:
		MoveWindow(hwndChild, int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case creditSysLinkID:
		MoveWindow(hwndChild, int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case logoutSysLinkID:
		MoveWindow(hwndChild, int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case browseActSysLinkID:
		if (currentAct.mPer.mAdmin)
		MoveWindow(hwndChild, int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case editActInfoEditID: 
		{
		if (Account::actInfoSysLinkFlag == 1)
			MoveWindow(hwndChild, int(0.2 * MyWnds::homePageWidth), int(0.14 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		else if (Account::actInfoSysLinkFlag == 2)
			MoveWindow(hwndChild, int(0.15 * MyWnds::homePageWidth), int(0.44 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
		}
	case actSaveSysLinkID: 
		{
		if (Account::actInfoSysLinkFlag == 1)
			MoveWindow(hwndChild, int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		else if (Account::actInfoSysLinkFlag == 2)
			MoveWindow(hwndChild, int(0.5 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
		}
	case returnSysLinkID:
		MoveWindow(hwndChild, int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
		
	case devInfoWndID://设备信息
		MoveWindow(hwndChild, int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, TRUE);
		break;
	case editDevIntroSysLinkID:
		MoveWindow(hwndChild, int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case devSaveSysLinkID:
		MoveWindow(hwndChild, int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;
	case devIntroEditID:
		MoveWindow(hwndChild, int(0.1 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.65 * MyWnds::homePageWidth), int(0.5 * MyWnds::homePageHeight), TRUE);
		break;

	case tradeInfoWndID://交易记录
		MoveWindow(hwndChild, int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, TRUE);
		break;
	case tradeSelectSysLinkID:
		MoveWindow(hwndChild, int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;

	case dataInfoListID:
		MoveWindow(hwndChild, int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight), TRUE);
		break;
	case dataInfoSysLinkID:
		MoveWindow(hwndChild, int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		break;

	}



	return TRUE;
}
//快速连续销毁多个控件&子窗口
void MyWnds::DestroyControl(HWND hWnd,const std::initializer_list<int>& controlID) {
	for (auto cID : controlID) {
		DestroyWindow(GetDlgItem(hWnd, cID));
	}
}
//快速连续给多个控件发送相同消息 (默认为设定字体的消息)
void MyWnds::SendMessageToControl(HWND hWnd, const std::initializer_list<int>& controlID, UINT Msg, WPARAM wParam, LPARAM lParam) {
	for (auto cID : controlID) {
		SendMessage(GetDlgItem(hWnd, cID), Msg, wParam, lParam);
	}
}


HWND ListCompareHandle = NULL;
bool ListCompareFlag = 1;
//用于列表中项的比较
int CALLBACK ListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
	TCHAR tempTCHAR[51], _tempTCHAR[51];
	ListView_GetItemText(GetDlgItem(ListCompareHandle, dataInfoListID), lParam1, LPNMLISTVIEW(lParamSort)->iSubItem, tempTCHAR, 51);
	ListView_GetItemText(GetDlgItem(ListCompareHandle, dataInfoListID), lParam2, LPNMLISTVIEW(lParamSort)->iSubItem, _tempTCHAR, 51);
	LVCOLUMN temp;
	ListView_GetColumn(GetDlgItem(ListCompareHandle, dataInfoListID), LPNMLISTVIEW(lParamSort)->iSubItem, &temp);
	if (temp.cxDefault) {
		//判定数据是字符型还是数值型
		if (ListCompareFlag)
		{
			return _wtoi(tempTCHAR) - _wtoi(_tempTCHAR);//升序
		}
		else {
			return _wtoi(_tempTCHAR) - _wtoi(tempTCHAR);//降序
		}
	}
	if (ListCompareFlag) {
		return _tcscmp(tempTCHAR, _tempTCHAR);//升序
	}
	else {
		return _tcscmp(_tempTCHAR, tempTCHAR);//降序
	}
}