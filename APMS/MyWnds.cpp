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

HWND MyWnds::ActInfoProc_hwnd;
UINT MyWnds::ActInfoProc_uMsg;
WPARAM MyWnds::ActInfoProc_wParam;
LPARAM MyWnds::ActInfoProc_lParam;
BYTE MyWnds::actInfoSysLinkFlag = 0;

HWND MyWnds::DevInfoProc_hwnd;
UINT MyWnds::DevInfoProc_uMsg;
WPARAM MyWnds::DevInfoProc_wParam;
LPARAM MyWnds::DevInfoProc_lParam;

HWND MyWnds::TradeInfoProc_hwnd;
UINT MyWnds::TradeInfoProc_uMsg;
WPARAM MyWnds::TradeInfoProc_wParam;
LPARAM MyWnds::TradeInfoProc_lParam;

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
			MyWnds::ActInfo();
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
			MyWnds::DevInfo();
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
			MyWnds::TradeInfo();
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
	BYTE tempFontFlag;
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;//设定临时指针接收附加信息
	MyWnds::defMainWndWidth = temp->cx;//获取窗口新的宽度
	MyWnds::defMainWndHeight = temp->cy;//获取窗口新的高度
	MyWnds::homePageWidth = int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth);
	MyWnds::homePageHeight = int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight);
	//调整各控件大小，使其与主窗口大小自适应
	if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; tempFontFlag = defSmallFont; }
	else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; tempFontFlag = defMidFont; }
	else { MyWnds::currentHFONT = MyWnds::defLargeHFont; tempFontFlag = defLargeFont; }
	switch (MyWnds::mainWndFlag)
	{
	case LoginUI: 
		MyWnds::adaptiveWndLoginUI(tempFontFlag);
		break;
	case RegisterUI:
		MyWnds::adaptiveWndRegisterUI(tempFontFlag);
		break;
	case HomeUI:
		MyWnds::adaptiveWndHomeUI(tempFontFlag);
		break;
	case ActInfoUI:
		MyWnds::adaptiveWndActInfoUI(tempFontFlag);
		break;
	case DevInfoUI: 
		MyWnds::adaptiveWndDevInfoUI(tempFontFlag);
		break;
	case TradeInfoUI: 
		MyWnds::adaptiveWndTradeInfoUI(tempFontFlag);
		break;
	}	
}

void MyWnds::adaptiveWndLoginUI(BYTE tempFontFlag) {
	if (tempFontFlag != MyWnds::fontFlag) {
		MyWnds::fontFlag = tempFontFlag;
		MyWnds::SendMessageToControl(MyWnds::MainWndProc_hwnd, {loginConfirmButtonID,registerButtonID,userNameStaticID,userNameEditID,passwdStaticID,passwdEditID});
		//重绘整个窗口
		InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
}
void MyWnds::adaptiveWndRegisterUI(BYTE tempFontFlag) {
	if (tempFontFlag != MyWnds::fontFlag) {
		MyWnds::fontFlag = tempFontFlag;
		MyWnds::SendMessageToControl(MyWnds::MainWndProc_hwnd, {loginButtonID,registerConfirmButtonID,actNameStaticID,actNameEditID,userNameStaticID,userNameEditID,passwdStaticID,passwdEditID});
		//重绘整个窗口
		InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), int(0.285 * MyWnds::defMainWndWidth), int(0.21 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
}
void MyWnds::adaptiveWndHomeUI(BYTE tempFontFlag) {
	if (tempFontFlag != MyWnds::fontFlag) {
		MyWnds::fontFlag = tempFontFlag;
		MyWnds::SendMessageToControl(MyWnds::MainWndProc_hwnd, {homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID});
		//重绘整个窗口
		InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, true);
}
void MyWnds::adaptiveWndActInfoUI(BYTE tempFontFlag) {
	if (tempFontFlag != MyWnds::fontFlag) {
		MyWnds::fontFlag = tempFontFlag;
		MyWnds::SendMessageToControl(MyWnds::MainWndProc_hwnd, {homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID});
		if (MyWnds::actInfoSysLinkFlag == 0) {
			MyWnds::SendMessageToControl(MyWnds::ActInfoProc_hwnd, {editActNameSysLinkID,editPasswdSysLinkID,creditSysLinkID,logoutSysLinkID});
			if(currentAct.mPer.mAdmin)SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		}
		else if (MyWnds::actInfoSysLinkFlag == 1|| MyWnds::actInfoSysLinkFlag == 2) {
			MyWnds::SendMessageToControl(MyWnds::ActInfoProc_hwnd, {editActInfoEditID,saveSysLinkID});
		}
		else if (MyWnds::actInfoSysLinkFlag == 4) {
			MyWnds::SendMessageToControl(MyWnds::ActInfoProc_hwnd, {actReturnSysLinkID,actInfoListID,actInfoSysLinkID});
		}
		//重绘整个窗口
		InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, true);
	if (MyWnds::actInfoSysLinkFlag == 0) {
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
		if (currentAct.mPer.mAdmin)
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
	}
	else if (MyWnds::actInfoSysLinkFlag == 1) {
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), int(0.2 * MyWnds::homePageWidth), int(0.14 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID), int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
	}
	else if (MyWnds::actInfoSysLinkFlag == 2) {
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), int(0.15 * MyWnds::homePageWidth), int(0.44 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID), int(0.5 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), TRUE);
	}
	else if (MyWnds::actInfoSysLinkFlag == 4) {
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, actReturnSysLinkID), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight), true);
		MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoSysLinkID), int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
	}

}
void MyWnds::adaptiveWndDevInfoUI(BYTE tempFontFlag) {
	if (tempFontFlag != MyWnds::fontFlag) {
		MyWnds::fontFlag = tempFontFlag;
		MyWnds::SendMessageToControl(MyWnds::MainWndProc_hwnd, {homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID});
		//重绘整个窗口
		InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, true);
}
void MyWnds::adaptiveWndTradeInfoUI(BYTE tempFontFlag){
	if (tempFontFlag != MyWnds::fontFlag) {
		MyWnds::fontFlag = tempFontFlag;
		MyWnds::SendMessageToControl(MyWnds::MainWndProc_hwnd, {homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID});
		//重绘整个窗口
		InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
	MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, true);
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
	SetBkMode(MyWnds::hDC, TRANSPARENT);
	MyWnds::hDC = NULL;
	return (INT_PTR)MyWnds::defHBrush;
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
		0,_T("mainWndClassName"),_T("游乐园管理系统"),WS_TILEDWINDOW,
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
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
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
		MyWnds::actInfoSysLinkFlag = 0;
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
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::HomePage(){
	//创建窗口---主页
	HWND homePageHwnd = CreateWindowEx(
		0, _T("homePageClassName"), _T("主页"), WS_TILED | WS_CHILD | WS_VISIBLE,
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
			0, _T("homePageClassName"), _T("主页"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(homePageWndID), MyWnds::hInstance, NULL
		);
		if (!homePageHwnd) {
			MessageBox(NULL, _T("创建窗口---主页，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//用户信息
LRESULT CALLBACK MyWnds::ActInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::ActInfoProc_hwnd = hwnd;
	MyWnds::ActInfoProc_uMsg = uMsg;
	MyWnds::ActInfoProc_wParam = wParam;
	MyWnds::ActInfoProc_lParam = lParam;
	switch (uMsg)
	{
	case WM_NOTIFY:
		MyWnds::ActInfoProc_WM_NOTIFY();
		break;
	case WM_PAINT:
		MyWnds::ActInfoProc_WM_PAINT();
		break;
	case WM_CREATE:
		MyWnds::ActInfoProc_WM_CREATE();
		break;
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::ActInfoProc_WM_NOTIFY() {
	switch (((LPNMHDR)MyWnds::ActInfoProc_lParam)->code)
	{
	case NM_CLICK:case NM_RETURN://单击
	{
		switch (LPNMHDR(MyWnds::ActInfoProc_lParam)->idFrom) {
		case actInfoListID:
		{
			MyWnds::x_Listview = LPNMITEMACTIVATE(MyWnds::ActInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(MyWnds::ActInfoProc_lParam)->iItem;
		}
		break;
		case actReturnSysLinkID:
		{
			//列表坐标初始化
			MyWnds::x_Listview = -1;
			MyWnds::y_Listview = 0;
			//销毁控件
			MyWnds::DestroyControl(MyWnds::ActInfoProc_hwnd, {actReturnSysLinkID,actInfoListID,actInfoSysLinkID});
			//创建控件
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), WM_CREATE, NULL, NULL);
			//更改标记
			MyWnds::actInfoSysLinkFlag = 0;
			//重绘整个窗口
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case browseActSysLinkID:
		{
			MyWnds::DestroyControl(MyWnds::ActInfoProc_hwnd, {editActNameSysLinkID,editPasswdSysLinkID,creditSysLinkID,logoutSysLinkID,browseActSysLinkID});
			//返回
			CreateWindowEx(
					0, _T("SysLink"), _T("<A HREF=\"返回\">返回</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
					int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
					MyWnds::ActInfoProc_hwnd, HMENU(actReturnSysLinkID), MyWnds::hInstance, NULL
				);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, actReturnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//更改用户信息
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"添加\">添加</A>")\
				_T(" <A HREF=\"修改\">修改</A>")\
				_T(" <A HREF=\"删除\">删除</A>"),
				WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(actInfoSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//用户信息列表
			CreateWindowEx(
				0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL |LVS_REPORT | LVS_SHOWSELALWAYS,
				int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, (HMENU)actInfoListID, MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID),  LVS_EX_COLUMNSNAPPOINTS |LVS_EX_CHECKBOXES| LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
			//插入列
			LVCOLUMN temp = { 0 };
			temp.mask = LVCF_TEXT | LVCF_FMT| LVCF_WIDTH| LVCF_MINWIDTH | LVCF_SUBITEM;
			temp.fmt = LVCFMT_CENTER;
			temp.cx = int(0.07 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("序号");
			temp.iSubItem = 0;
			temp.cxMin = int(0.07 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 0, &temp);

			temp.cx = int(0.16 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("用户昵称");
			temp.iSubItem = 1;
			temp.cxMin = int(0.16 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 1, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("用户名");
			temp.iSubItem = 2;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 2, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("密码");
			temp.iSubItem = 3;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 3, &temp);


			temp.cx = int(0.06 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("权限");
			temp.iSubItem = 4;
			temp.cxMin = int(0.06
				* MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 4, &temp);

			temp.cx = int(0.1 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("余额");
			temp.iSubItem = 5;
			temp.cxMin = int(0.1 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 5, &temp);

			temp.cx = int(0.2 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("注册时间");
			temp.iSubItem = 6;
			temp.cxMin = int(0.2 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 6, &temp);
			//插入行
			Account tempAct;//存放将要读取的用户数据
			DWORD tempDWORD = 0;//存放实际读取的字节数
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ , NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
			for (int x = 0; true;++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x+1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mName;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mID;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mPasswd;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mPer.mAdmin);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mCredit);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempAct.mRegTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempAct.mRegTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

			}
			CloseHandle(tempHANDLE);//关闭文件

			MyWnds::actInfoSysLinkFlag = 4;
			//重绘整个窗口
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case actInfoSysLinkID:
		{
			if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 0)//增加
			{
				dialogFlag = dialogActAdd;
				MyWnds::Dialog();

			}
			else if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 1)//修改
			{
				TCHAR tempTCHAR[20] = {};
				ListView_GetItemText(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), MyWnds::y_Listview, 4, tempTCHAR, 8);
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID))) {
					MessageBox(MyWnds::ActInfoProc_hwnd, _T("请选择要修改的用户"), _T("提示"), MB_ICONINFORMATION);
				}
				else if (currentAct.mPer.mAdmin <= _wtoi(tempTCHAR)) {
					MessageBox(MyWnds::ActInfoProc_hwnd, _T("您的权限不足，无法修改所选用户信息"), _T("权限不足"), MB_ICONERROR);
				}
				else {
					dialogFlag = dialogActModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 2)//删除
			{
				TCHAR tempTCHAR[20] = {};
				if (MessageBox(MyWnds::ActInfoProc_hwnd, _T("确定要删除这些用户吗？"), _T("提示"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y =  ListView_GetItemCount(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID)) - 1; y >=0 ; --y) {
						if (ListView_GetCheckState(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), y)) {
							ListView_GetItemText(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), y , 2, tempTCHAR, actUserName * 2);
							if (!_tcscmp(MyWnds::currentAct.mID, tempTCHAR))continue;
							Data<Account>::DataDelete(_T("Account.dat"), tempTCHAR);
						}
					}
				}
			}
			//准备刷新列表数据
			//删除所有行
			ListView_DeleteAllItems(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID));
			//插入行
			Account tempAct;//存放将要读取的用户数据
			DWORD tempDWORD = 0;//存放实际读取的字节数
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x + 1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mName;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mID;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mPasswd;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mPer.mAdmin);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mCredit);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempAct.mRegTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempAct.mRegTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), &tempINSERT);

			}
			CloseHandle(tempHANDLE);//关闭文件

			MyWnds::actInfoSysLinkFlag = 4;
			//重绘整个窗口
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);

		}
		break;
		case saveSysLinkID: 
		{
			TCHAR tempTCHAR[(actName>actPasswd)?actName:actPasswd];
			Edit_GetText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID)));//获取用户输入的昵称
			if (*tempTCHAR) {
				if (MyWnds::actInfoSysLinkFlag == 1) {
					_stprintf_s(MyWnds::currentAct.mName, tempTCHAR);
				}
				else if (MyWnds::actInfoSysLinkFlag == 2) {
					_stprintf_s(MyWnds::currentAct.mPasswd, tempTCHAR);
				}
				//修改用户
				Data<Account>::DataModify(_T("Account.dat"), MyWnds::currentAct);
				MyWnds::actInfoSysLinkFlag = 0;
				DestroyWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID));
				DestroyWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID));
				SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), SW_SHOW);
				SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), SW_SHOW);
				SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), SW_SHOW);
				SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), SW_SHOW);
				if (currentAct.mPer.mAdmin) {
					SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
					MoveWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
					ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), SW_SHOW);
				}
				//重绘整个窗口
				InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
				SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			}
			else {
				MessageBox(MyWnds::ActInfoProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
			}
		}
		break;
		case editActNameSysLinkID:
		{
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), SW_HIDE);
			if (currentAct.mPer.mAdmin)ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), SW_HIDE);
			//保存
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"保存\">保存</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(saveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//输入框
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mName , WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				int(0.2 * homePageWidth), int(0.14 * homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), _T("请输入新的用户昵称"));//设置编辑控件中的文本提示
			Edit_LimitText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), actName - 1); //限制可在编辑控件中输入的用户昵称的长度
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			MyWnds::actInfoSysLinkFlag = 1;
			//重绘整个窗口
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case editPasswdSysLinkID:
		{
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), SW_HIDE);
			if(currentAct.mPer.mAdmin)ShowWindow(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), SW_HIDE);
			//保存
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"保存\">保存</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.5 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(saveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//输入框
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				int(0.15 * homePageWidth), int(0.44 * homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), _T("请输入新的密码"));//设置编辑控件中的文本提示
			Edit_LimitText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), actPasswd - 1); //限制可在编辑控件中输入的用户昵称的长度
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			MyWnds::actInfoSysLinkFlag = 2;
		}
		break;
		case creditSysLinkID:
		{
			if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 0)//充值
			{
				MessageBox(MyWnds::ActInfoProc_hwnd, _T("新功能还在开发中(～￣▽￣)～"), _T("维护"), MB_OK | MB_ICONERROR);
				//ShellExecute(NULL, _T("open"), _T("https://github.com/ISQIShI/Amusement-Park-Management-System"), NULL, NULL, SW_SHOW);
			}
			else if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 1)//提现
			{
				MessageBox(MyWnds::ActInfoProc_hwnd, _T("没有做这个功能嘞╮（╯＿╰）╭\n便于后续扩展(如果是真的软件的话)"), _T("维护"), MB_OK | MB_ICONERROR);
			}
		}
		break;
		case logoutSysLinkID:
		{
			if (MessageBox(MyWnds::ActInfoProc_hwnd, _T("您确定注销用户吗？\n请注意此操作不可撤回！！！"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
			{
				Data<Account>::DataDelete(_T("Account.dat"), currentAct.mID);
				MyWnds::DestroyChildWnd();
				MyWnds::DestroyControl(MyWnds::MainWndProc_hwnd, {homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID});
				Door::Login();
			}
		}
		break;
		}
	}
	break;
	case NM_DBLCLK://双击
	{
		switch (LPNMHDR(MyWnds::ActInfoProc_lParam)->idFrom) {
		case actInfoListID:
		{

		}
		break;
		}
	}
	break;
	case NM_RCLICK://右击
	{
		switch (LPNMHDR(MyWnds::ActInfoProc_lParam)->idFrom) {
		case actInfoListID:
		{

		}
		break;
		}
	}
	break;
	}
}

void MyWnds::ActInfoProc_WM_PAINT() {
	TCHAR tempTCHAR[50];
	PAINTSTRUCT ps;
	MyWnds::hDC = BeginPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID),&ps);
	SelectObject(MyWnds::hDC, MyWnds::currentHFONT);
	if (actInfoSysLinkFlag == 4) {

	}
	else {
		if (actInfoSysLinkFlag == 1)_stprintf_s(tempTCHAR, _T("用户昵称："));
		else _stprintf_s(tempTCHAR, _T("用户昵称：%s"), currentAct.mName);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.15 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户名：%s"), currentAct.mID);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.3 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("密码："));
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.45 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户权限：%d"), currentAct.mPer.mAdmin);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.6 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户余额：%d"), currentAct.mCredit);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.75 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户注册时间：%s %s"), currentAct.mRegTime.mDate, currentAct.mRegTime.mMoment);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.9 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
	}
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), &ps);
	MyWnds::hDC = NULL;
}

void MyWnds::ActInfoProc_WM_CREATE() {
	//编辑用户昵称
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"编辑\">编辑</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(editActNameSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//更改密码
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"更改密码\">更改密码</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(editPasswdSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//充值/提现
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"充值\">充值</A>")\
		_T("|<A HREF=\"提现\"> 提现 </A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(creditSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//注销用户
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"注销用户\">注销用户</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(logoutSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//查看所有用户（需要权限）
	if (currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"查看所有用户\">查看所有用户</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
			int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			MyWnds::ActInfoProc_hwnd, HMENU(browseActSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
}

void MyWnds::ActInfo() {
	//创建窗口---用户信息
	HWND actInfoHwnd = CreateWindowEx(
		0, _T("actInfoClassName"), _T("用户信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
	);
	if (!actInfoHwnd) {
		//实例化窗口类对象---用户信息
		WNDCLASSEX actInfoClass = { 0 };
		actInfoClass.cbSize = sizeof(WNDCLASSEX);
		actInfoClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		actInfoClass.lpfnWndProc = MyWnds::ActInfoProc;//窗口过程
		actInfoClass.hInstance = MyWnds::hInstance;//程序实例
		actInfoClass.hbrBackground = HBRUSH(6);//类背景画刷
		actInfoClass.lpszClassName = _T("actInfoClassName");//窗口类名
		actInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---用户信息
		if (!RegisterClassEx(&actInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---用户信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}

		//创建窗口---用户信息
		actInfoHwnd = CreateWindowEx(
			0, _T("actInfoClassName"), _T("用户信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
		);
		if (!actInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---用户信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//设备信息
LRESULT CALLBACK MyWnds::DevInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::DevInfoProc_hwnd = hwnd;
	MyWnds::DevInfoProc_uMsg = uMsg;
	MyWnds::DevInfoProc_wParam = wParam;
	MyWnds::DevInfoProc_lParam = lParam;
	switch (uMsg)
	{
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::DevInfo() {
	//创建窗口---设备信息
	HWND devInfoHwnd = CreateWindowEx(
		0, _T("devInfoClassName"), _T("设备信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
	);
	if (!devInfoHwnd) {
		//实例化窗口类对象---设备信息
		WNDCLASSEX devInfoClass = { 0 };
		devInfoClass.cbSize = sizeof(WNDCLASSEX);
		devInfoClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		devInfoClass.lpfnWndProc = MyWnds::DevInfoProc;//窗口过程
		devInfoClass.hInstance = MyWnds::hInstance;//程序实例
		devInfoClass.hbrBackground = HBRUSH(6);//类背景画刷
		devInfoClass.lpszClassName = _T("devInfoClassName");//窗口类名
		devInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---设备信息
		if (!RegisterClassEx(&devInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---设备信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//创建窗口---设备信息
		devInfoHwnd = CreateWindowEx(
			0, _T("devInfoClassName"), _T("设备信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
		);
		if (!devInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---设备信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//交易记录
LRESULT CALLBACK MyWnds::TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::TradeInfoProc_hwnd = hwnd;
	MyWnds::TradeInfoProc_uMsg = uMsg;
	MyWnds::TradeInfoProc_wParam = wParam;
	MyWnds::TradeInfoProc_lParam = lParam;
	switch (uMsg)
	{
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::TradeInfo() {
	//创建窗口---交易记录
	HWND tradeInfoHwnd = CreateWindowEx(
		0, _T("tradeInfoClassName"), _T("交易记录"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
	);
	if (!tradeInfoHwnd) {
		//实例化窗口类对象---交易记录
		WNDCLASSEX tradeInfoClass = { 0 };
		tradeInfoClass.cbSize = sizeof(WNDCLASSEX);
		tradeInfoClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		tradeInfoClass.lpfnWndProc = MyWnds::TradeInfoProc;//窗口过程
		tradeInfoClass.hInstance = MyWnds::hInstance;//程序实例
		tradeInfoClass.hbrBackground = HBRUSH(6);//类背景画刷
		tradeInfoClass.lpszClassName = _T("tradeInfoClassName");//窗口类名
		tradeInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---交易记录
		if (!RegisterClassEx(&tradeInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---交易记录，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//创建窗口---交易记录
		tradeInfoHwnd = CreateWindowEx(
			0, _T("tradeInfoClassName"), _T("交易记录"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
		);
		if (!tradeInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---交易记录，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
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
	case WM_COMMAND:
	{
		if (HIWORD(MyWnds::DialogProc_wParam) == BN_CLICKED) {
			switch (LOWORD(MyWnds::DialogProc_wParam)) {
			case confirmButtonID: {
				switch (dialogFlag) {
				case dialogActAdd: case dialogActModify:
				{
					TCHAR tempTCHAR[20];
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
					//获取系统时间&设定注册时间
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
				}
				break;
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
			DialogActAdd();
			break;
		case dialogActModify:
			DialogActModify();
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("请输入余额"));//设置编辑控件中的文本提示
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogActModify() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Account tempAct = { 0 };//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	TCHAR tempTCHAR[20] = {};
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mID, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetReadOnly(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), TRUE);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//密码
	CreateWindowEx(
		0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER,
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("请输入余额"));//设置编辑控件中的文本提示
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//确认
	CreateWindowEx(
		0, WC_BUTTON, _T("确认"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//取消
	CreateWindowEx(
		0, WC_BUTTON, _T("取消"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

}


WPARAM MyWnds::Dialog() {
	//创建对话框
	HWND dialogHwnd = CreateWindowEx(
		0, _T("dialogClassName"), _T("对话框"), WS_TILEDWINDOW | WS_VISIBLE ,
		int(0.45 * MyWnds::defScreenWidth), int(0.2 * MyWnds::defScreenHeight), int(0.7 * MyWnds::defMainWndHeight), int(0.8 * MyWnds::defMainWndHeight),
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
			0, _T("dialogClassName"), _T("对话框"), WS_TILEDWINDOW | WS_VISIBLE,
			int(0.45 * MyWnds::defScreenWidth), int(0.2 * MyWnds::defScreenHeight), int(0.7 * MyWnds::defMainWndHeight), int(0.8 * MyWnds::defMainWndHeight),
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
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
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
		0, WC_BUTTON, _T("已有账号？点此登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建登录确认按钮
void MyWnds::createLoginConfirmButton() {
	CreateWindowEx(
		0, WC_BUTTON, _T("登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建注册按钮
void MyWnds::createRegisterButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("没有账号？点此注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建注册确认按钮
void MyWnds::createRegisterConfirmButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建主页按钮
void MyWnds::createHomePageButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("主页"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(homePageButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建用户信息按钮
void MyWnds::createActInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("用户信息"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建设备信息按钮
void MyWnds::createDevInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("设备信息"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
		0, WC_BUTTON, tempTCHAR , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//创建退出系统按钮
void MyWnds::createExitButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("退出系统"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), _T("请输入用户昵称"));//设置编辑控件中的文本提示
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), actName - 1); //限制可在编辑控件中输入的用户名的长度
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
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