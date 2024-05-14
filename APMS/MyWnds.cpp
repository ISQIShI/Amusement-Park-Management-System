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
HBRUSH MyWnds::defHBrush = CreateSolidBrush(RGB(133, 193, 233));//����Ĭ�ϻ�ˢ

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


//�Ի���Ĳ���
HWND MyWnds::DialogProc_hwnd;
UINT MyWnds::DialogProc_uMsg;
WPARAM MyWnds::DialogProc_wParam;
LPARAM MyWnds::DialogProc_lParam;

//��ȡ�����ݼ�¼����
void MyWnds::GetDataCount() {
	LARGE_INTEGER temp;
	HANDLE tempHANLDE;
	//�û���Ϣ
	tempHANLDE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Account::mCount = 0; }
	else{
		GetFileSizeEx(tempHANLDE, &temp);
		Account::mCount = temp.QuadPart / sizeof(Account);
		CloseHandle(tempHANLDE);
	}
	//�豸��Ϣ
	tempHANLDE = CreateFile(_T("Device.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Device::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Device::mCount = temp.QuadPart / sizeof(Device);
		CloseHandle(tempHANLDE);
	}
	//���׼�¼
	tempHANLDE = CreateFile(_T("Trade.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Trade::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Trade::mCount = temp.QuadPart / sizeof(Trade);
		CloseHandle(tempHANLDE);
	}
	//��ֵ��¼
	tempHANLDE = CreateFile(_T("Recharge.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Recharge::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Recharge::mCount = temp.QuadPart / sizeof(Recharge);
		CloseHandle(tempHANLDE);
	}
	//����
	tempHANLDE = CreateFile(_T("Notification.dat"), GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANLDE == INVALID_HANDLE_VALUE) { Notification::mCount = 0; }
	else {
		GetFileSizeEx(tempHANLDE, &temp);
		Notification::mCount = temp.QuadPart / sizeof(Notification);
		CloseHandle(tempHANLDE);
	}
}

//��������
void MyWnds::CreateFont() {
	//����Ĭ������
	MyWnds::defLogFont.lfEscapement = 0;//ת���������豸�� x ��֮��ĽǶȣ���ʮ��֮һ��Ϊ��λ��
	MyWnds::defLogFont.lfOrientation = 0;//ÿ���ַ��Ļ��ߺ��豸 x ��֮��ĽǶȣ���ʮ��֮һ��Ϊ��λ��
	MyWnds::defLogFont.lfWeight = 550;//����Ĵ�ϸ
	MyWnds::defLogFont.lfItalic = FALSE;//б��
	MyWnds::defLogFont.lfUnderline = FALSE;//�»���
	MyWnds::defLogFont.lfStrikeOut = FALSE;//ɾ����
	MyWnds::defLogFont.lfCharSet = GB2312_CHARSET;//�ַ���
	MyWnds::defLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;//�������
	MyWnds::defLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;//���þ���
	MyWnds::defLogFont.lfQuality = ANTIALIASED_QUALITY;//�������
	MyWnds::defLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;//����ļ���ϵ��
	_stprintf_s(MyWnds::defLogFont.lfFaceName, _T("����"));//��������
	//С����
	MyWnds::hDC = GetDC(MyWnds::MainWndProc_hwnd);//��ȡ�豸�������
	MyWnds::defLogFont.lfHeight = MulDiv(11, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//10���ֺŴ�С
	MyWnds::defLogFont.lfWidth = 0;//�������ַ���ƽ����ȣ����߼���λΪ��λ��
	MyWnds::defSmallHFont = CreateFontIndirect(&MyWnds::defLogFont);
	//������
	MyWnds::defLogFont.lfHeight = MulDiv(13, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//13���ֺŴ�С
	MyWnds::defLogFont.lfWidth = 0;
	MyWnds::defMidHFont = CreateFontIndirect(&MyWnds::defLogFont);
	//������
	MyWnds::defLogFont.lfHeight = MulDiv(17, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//17���ֺŴ�С
	MyWnds::defLogFont.lfWidth = 0;
	MyWnds::defLargeHFont = CreateFontIndirect(&MyWnds::defLogFont);
	ReleaseDC(MyWnds::MainWndProc_hwnd, MyWnds::hDC);//�ͷ��豸�������
	MyWnds::hDC = NULL;//hDC�ÿ�
}

//�������ڹ���---������
LRESULT CALLBACK MyWnds::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::MainWndProc_hwnd = hwnd;
	MyWnds::MainWndProc_uMsg = uMsg;
	MyWnds::MainWndProc_wParam = wParam;
	MyWnds::MainWndProc_lParam = lParam;
	switch (uMsg){
	case WM_COMMAND:
		MyWnds::MainWndProc_WM_COMMAND();
		break;
	case WM_WINDOWPOSCHANGING://׼�����Ĵ��ڴ�С
		MyWnds::MainWndProc_WM_WINDOWPOSCHANGING();
		break;
	case WM_WINDOWPOSCHANGED://���ڴ�С��ɸ���
		MyWnds::MainWndProc_WM_WINDOWPOSCHANGED();
		break;
	case WM_CLOSE://�رմ���
		MyWnds::MainWndProc_WM_CLOSE();
		break;
	case WM_DESTROY://���ٴ���
		MyWnds::MainWndProc_WM_DESTROY();
		break;
	case WM_CTLCOLORSTATIC://����static��edit(ES_READONLY)�ؼ�
		return MyWnds::MainWndProc_WM_CTLCOLORSTATIC();
	case WM_PAINT://���ƴ��ڸ�������
		MyWnds::MainWndProc_WM_PAINT();
		break;
	case WM_CREATE://��������
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
	default://δ�Զ����������Ϣ
		return DefWindowProc(MyWnds::MainWndProc_hwnd, uMsg, wParam, MyWnds::MainWndProc_lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::MainWndProc_WM_COMMAND() {
	//��������ť����Ϣ
	if (HIWORD(MyWnds::MainWndProc_wParam) == BN_CLICKED) {
		switch (LOWORD(MyWnds::MainWndProc_wParam)) {
		case loginButtonID: {
			//���ٿؼ�
			MyWnds::DestroyControl(MyWnds::MainWndProc_hwnd, { loginButtonID,registerConfirmButtonID,actNameStaticID,actNameEditID,userNameStaticID,userNameEditID,passwdStaticID,passwdEditID });
			Door::Login();
		}
		break;
		case loginConfirmButtonID: {
			Door::LoginConfirm();
		}
		break;
		case registerButtonID: {
			//���ٿؼ�
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
			//���Ĵ��ڷ������
			MyWnds::mainWndStyle = HomeUI;
			MyWnds::mainWndFlag = HomeUI;
			//�ػ���������
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case actInfoButtonID: {
			MyWnds::DestroyChildWnd();
			MyWnds::ActInfo();
			//���Ĵ��ڷ������
			MyWnds::mainWndStyle = ActInfoUI;
			MyWnds::mainWndFlag = ActInfoUI;
			//�ػ���������
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case devInfoButtonID: {
			MyWnds::DestroyChildWnd();
			MyWnds::DevInfo();
			//���Ĵ��ڷ������
			MyWnds::mainWndStyle = DevInfoUI;
			MyWnds::mainWndFlag = DevInfoUI;
			//�ػ���������
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case tradeInfoButtonID: {
			MyWnds::DestroyChildWnd();
			MyWnds::TradeInfo();
			//���Ĵ��ڷ������
			MyWnds::mainWndStyle = TradeInfoUI;
			MyWnds::mainWndFlag = TradeInfoUI;
			//�ػ���������
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case exitButtonID: {
			int temp = MessageBox(MyWnds::MainWndProc_hwnd, _T("��ѡ��\n�ǣ��˳�ϵͳ\n���˳���¼"), _T("����԰����ϵͳ"), MB_YESNOCANCEL);
			if (temp == IDYES)
			{
				DeleteObject(MyWnds::defHBrush);//ɾ��Ĭ�ϻ�ˢ
				DeleteObject(MyWnds::defSmallHFont);//ɾ��С����
				DeleteObject(MyWnds::defMidHFont);//ɾ��������
				DeleteObject(MyWnds::defLargeHFont);//ɾ��������
				MyWnds::DestroyChildWnd();
				DestroyWindow(MyWnds::MainWndProc_hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ
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
	}//����µĴ��ڿ��С��960�����أ����趨Ϊ960
	if (temp->cy < 540) {
		temp->cy = 540;
	}//����µĴ��ڸ߶�С��540�����أ����趨Ϊ540
}

void MyWnds::MainWndProc_WM_WINDOWPOSCHANGED(){
	BYTE tempFontFlag;
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;//�趨��ʱָ����ո�����Ϣ
	MyWnds::defMainWndWidth = temp->cx;//��ȡ�����µĿ��
	MyWnds::defMainWndHeight = temp->cy;//��ȡ�����µĸ߶�
	MyWnds::homePageWidth = int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth);
	MyWnds::homePageHeight = int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight);
	//�������ؼ���С��ʹ���������ڴ�С����Ӧ
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
		//�ػ���������
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
		//�ػ���������
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
		//�ػ���������
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
		//�ػ���������
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
		//�ػ���������
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
		//�ػ���������
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
	if (MessageBox(MyWnds::MainWndProc_hwnd, _T("�Ƿ�ȷ���˳�ϵͳ��"), _T("����԰����ϵͳ"), MB_OKCANCEL) == IDOK)
	{
		DeleteObject(MyWnds::defHBrush);//ɾ��Ĭ�ϻ�ˢ
		DeleteObject(MyWnds::defSmallHFont);//ɾ��С����
		DeleteObject(MyWnds::defMidHFont);//ɾ��������
		DeleteObject(MyWnds::defLargeHFont);//ɾ��������
		DestroyWindow(MyWnds::MainWndProc_hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ
	}
}

void MyWnds::MainWndProc_WM_DESTROY(){
	PostQuitMessage(0);//����WM_QUIT��Ϣ
}

LRESULT MyWnds::MainWndProc_WM_CTLCOLORSTATIC(){
	MyWnds::hDC = (HDC)MyWnds::MainWndProc_wParam;
	SetTextColor(MyWnds::hDC, RGB(0, 0, 0));//����ǰ��ɫ
	//SetBkColor(MyWnds::hDC, RGB(174, 214, 241));//���ֱ���ɫ
	SetBkMode(MyWnds::hDC, TRANSPARENT);
	MyWnds::hDC = NULL;
	return (INT_PTR)MyWnds::defHBrush;
}

void MyWnds::MainWndProc_WM_PAINT(){
	switch (MyWnds::mainWndStyle) {
	case LoginUI: case RegisterUI:
	{
		//������ʱ��ˢ
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//ʵ������ͼ��Ϣ�ṹ�����
		PAINTSTRUCT ps;
		//��ȡ�����ڵ���ʾ�豸�Ļ������
		MyWnds::hDC = BeginPaint(MyWnds::MainWndProc_hwnd, &ps);
		//���Ƹ�������
		//FillRect(MyWnds::hDC, &ps.rcPaint, defHBrush);
		//������������
		RECT center = { int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), int(0.85 * MyWnds::defMainWndWidth), int(0.8 * MyWnds::defMainWndHeight) };
		FillRect(MyWnds::hDC, &center, tempBrush);
		//ɾ����ʱ��ˢ
		DeleteObject(tempBrush);
		//�ͷ������ڵ���ʾ�豸�Ļ������
		EndPaint(MyWnds::MainWndProc_hwnd, &ps);
		MyWnds::hDC = NULL;
	}
	 break;
	case HomeUI:case ActInfoUI:case DevInfoUI:case TradeInfoUI:
	{
		//������ʱ��ˢ
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//ʵ������ͼ��Ϣ�ṹ�����
		PAINTSTRUCT ps;
		//��ȡ�����ڵ���ʾ�豸�Ļ������
		MyWnds::hDC = BeginPaint(MyWnds::MainWndProc_hwnd, &ps);
		//���Ƹ�������
		//FillRect(MyWnds::hDC, &ps.rcPaint, MyWnds::defHBrush);
		//��������A
		RECT aRECT = { int(homePageButtonCoord_X / 2.0 * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((homePageButtonWidth + homePageButtonCoord_X * 3 / 2.0) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y * 3 / 2.0 + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight) };
		FillRect(MyWnds::hDC, &aRECT, tempBrush);
		//ɾ����ʱ��ˢ
		DeleteObject(tempBrush);
		//�ͷ������ڵ���ʾ�豸�Ļ������
		EndPaint(MyWnds::MainWndProc_hwnd, &ps);
		MyWnds::hDC = NULL;
	}
	break;
	}
}

WPARAM MyWnds::MainWnd() {
	//ʵ�������������---������
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
	mainWndClass.lpfnWndProc = MyWnds::MainWndProc;//���ڹ���
	mainWndClass.hInstance = MyWnds::hInstance;//����ʵ��
	mainWndClass.hbrBackground = MyWnds::defHBrush;//�౳����ˢ
	mainWndClass.lpszClassName = _T("mainWndClassName");//��������
	mainWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
	//ע�ᴰ����---������
	if (!RegisterClassEx(&mainWndClass)) {
		MessageBox(NULL, _T("ע�ᴰ����---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//��������---������
	HWND mainHwnd = CreateWindowEx(
		0,_T("mainWndClassName"),_T("����԰����ϵͳ"),WS_TILEDWINDOW,
		int(0.15 * MyWnds::defScreenWidth),int( 0.15 * MyWnds::defScreenHeight), MyWnds::defMainWndWidth, MyWnds::defMainWndHeight,
		NULL,NULL, MyWnds::hInstance,NULL
	);
	if (!mainHwnd) {
		MessageBox(NULL, _T("��������---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//��ʾ����---������
	ShowWindow(mainHwnd, SW_SHOW);
	//������Ϣѭ��
	MSG Msg = { 0 };
	BOOL bRet = 1;
	while (bRet = (GetMessage(&Msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
		{
			MessageBox(NULL, _T("��Ϣ����ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
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

//�����Ӵ���
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

//��ҳ
LRESULT CALLBACK MyWnds::HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	MyWnds::HomePageProc_hwnd = hwnd;
	MyWnds::HomePageProc_uMsg = uMsg;
	MyWnds::HomePageProc_wParam = wParam;
	MyWnds::HomePageProc_lParam = lParam;
	switch (uMsg)
	{
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::HomePage(){
	//��������---��ҳ
	HWND homePageHwnd = CreateWindowEx(
		0, _T("homePageClassName"), _T("��ҳ"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(homePageWndID), MyWnds::hInstance, NULL
	);
	if (!homePageHwnd) {
		//ʵ�������������---��ҳ
		WNDCLASSEX homePageClass = { 0 };
		homePageClass.cbSize = sizeof(WNDCLASSEX);
		homePageClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		homePageClass.lpfnWndProc = MyWnds::HomePageProc;//���ڹ���
		homePageClass.hInstance = MyWnds::hInstance;//����ʵ��
		homePageClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		homePageClass.lpszClassName = _T("homePageClassName");//��������
		homePageClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---��ҳ
		if (!RegisterClassEx(&homePageClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---��ҳ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//��������---��ҳ
		homePageHwnd = CreateWindowEx(
			0, _T("homePageClassName"), _T("��ҳ"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(homePageWndID), MyWnds::hInstance, NULL
		);
		if (!homePageHwnd) {
			MessageBox(NULL, _T("��������---��ҳ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//�û���Ϣ
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
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::ActInfoProc_WM_NOTIFY() {
	switch (((LPNMHDR)MyWnds::ActInfoProc_lParam)->code)
	{
	case NM_CLICK:case NM_RETURN://����
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
			//�б������ʼ��
			MyWnds::x_Listview = -1;
			MyWnds::y_Listview = 0;
			//���ٿؼ�
			MyWnds::DestroyControl(MyWnds::ActInfoProc_hwnd, {actReturnSysLinkID,actInfoListID,actInfoSysLinkID});
			//�����ؼ�
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), WM_CREATE, NULL, NULL);
			//���ı��
			MyWnds::actInfoSysLinkFlag = 0;
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case browseActSysLinkID:
		{
			MyWnds::DestroyControl(MyWnds::ActInfoProc_hwnd, {editActNameSysLinkID,editPasswdSysLinkID,creditSysLinkID,logoutSysLinkID,browseActSysLinkID});
			//����
			CreateWindowEx(
					0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
					int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
					MyWnds::ActInfoProc_hwnd, HMENU(actReturnSysLinkID), MyWnds::hInstance, NULL
				);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, actReturnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�����û���Ϣ
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"���\">���</A>")\
				_T(" <A HREF=\"�޸�\">�޸�</A>")\
				_T(" <A HREF=\"ɾ��\">ɾ��</A>"),
				WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(actInfoSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�û���Ϣ�б�
			CreateWindowEx(
				0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL |LVS_REPORT | LVS_SHOWSELALWAYS,
				int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, (HMENU)actInfoListID, MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID),  LVS_EX_COLUMNSNAPPOINTS |LVS_EX_CHECKBOXES| LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
			//������
			LVCOLUMN temp = { 0 };
			temp.mask = LVCF_TEXT | LVCF_FMT| LVCF_WIDTH| LVCF_MINWIDTH | LVCF_SUBITEM;
			temp.fmt = LVCFMT_CENTER;
			temp.cx = int(0.07 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("���");
			temp.iSubItem = 0;
			temp.cxMin = int(0.07 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 0, &temp);

			temp.cx = int(0.16 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("�û��ǳ�");
			temp.iSubItem = 1;
			temp.cxMin = int(0.16 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 1, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("�û���");
			temp.iSubItem = 2;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 2, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("����");
			temp.iSubItem = 3;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 3, &temp);


			temp.cx = int(0.06 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("Ȩ��");
			temp.iSubItem = 4;
			temp.cxMin = int(0.06
				* MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 4, &temp);

			temp.cx = int(0.1 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("���");
			temp.iSubItem = 5;
			temp.cxMin = int(0.1 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 5, &temp);

			temp.cx = int(0.2 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("ע��ʱ��");
			temp.iSubItem = 6;
			temp.cxMin = int(0.2 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), 6, &temp);
			//������
			Account tempAct;//��Ž�Ҫ��ȡ���û�����
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ , NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true;++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
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
			CloseHandle(tempHANDLE);//�ر��ļ�

			MyWnds::actInfoSysLinkFlag = 4;
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case actInfoSysLinkID:
		{
			if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 0)//����
			{
				dialogFlag = dialogActAdd;
				MyWnds::Dialog();

			}
			else if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 1)//�޸�
			{
				TCHAR tempTCHAR[20] = {};
				ListView_GetItemText(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), MyWnds::y_Listview, 4, tempTCHAR, 8);
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID))) {
					MessageBox(MyWnds::ActInfoProc_hwnd, _T("��ѡ��Ҫ�޸ĵ��û�"), _T("��ʾ"), MB_ICONINFORMATION);
				}
				else if (currentAct.mPer.mAdmin <= _wtoi(tempTCHAR)) {
					MessageBox(MyWnds::ActInfoProc_hwnd, _T("����Ȩ�޲��㣬�޷��޸���ѡ�û���Ϣ"), _T("Ȩ�޲���"), MB_ICONERROR);
				}
				else {
					dialogFlag = dialogActModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 2)//ɾ��
			{
				TCHAR tempTCHAR[20] = {};
				if (MessageBox(MyWnds::ActInfoProc_hwnd, _T("ȷ��Ҫɾ����Щ�û���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y =  ListView_GetItemCount(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID)) - 1; y >=0 ; --y) {
						if (ListView_GetCheckState(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), y)) {
							ListView_GetItemText(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID), y , 2, tempTCHAR, actUserName * 2);
							if (!_tcscmp(MyWnds::currentAct.mID, tempTCHAR))continue;
							Data<Account>::DataDelete(_T("Account.dat"), tempTCHAR);
						}
					}
				}
			}
			//׼��ˢ���б�����
			//ɾ��������
			ListView_DeleteAllItems(GetDlgItem(MyWnds::ActInfoProc_hwnd, actInfoListID));
			//������
			Account tempAct;//��Ž�Ҫ��ȡ���û�����
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
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
			CloseHandle(tempHANDLE);//�ر��ļ�

			MyWnds::actInfoSysLinkFlag = 4;
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);

		}
		break;
		case saveSysLinkID: 
		{
			TCHAR tempTCHAR[(actName>actPasswd)?actName:actPasswd];
			Edit_GetText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID)));//��ȡ�û�������ǳ�
			if (*tempTCHAR) {
				if (MyWnds::actInfoSysLinkFlag == 1) {
					_stprintf_s(MyWnds::currentAct.mName, tempTCHAR);
				}
				else if (MyWnds::actInfoSysLinkFlag == 2) {
					_stprintf_s(MyWnds::currentAct.mPasswd, tempTCHAR);
				}
				//�޸��û�
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
				//�ػ���������
				InvalidateRect(MyWnds::MyWnds::ActInfoProc_hwnd, NULL, TRUE);
				SendMessage(MyWnds::MyWnds::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			}
			else {
				MessageBox(MyWnds::ActInfoProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
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
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(saveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�����
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mName , WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				int(0.2 * homePageWidth), int(0.14 * homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), _T("�������µ��û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
			Edit_LimitText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û��ǳƵĳ���
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			MyWnds::actInfoSysLinkFlag = 1;
			//�ػ���������
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
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.5 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(saveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, saveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�����
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
				int(0.15 * homePageWidth), int(0.44 * homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				MyWnds::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), _T("�������µ�����"));//���ñ༭�ؼ��е��ı���ʾ
			Edit_LimitText(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), actPasswd - 1); //���ƿ��ڱ༭�ؼ���������û��ǳƵĳ���
			SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			MyWnds::actInfoSysLinkFlag = 2;
		}
		break;
		case creditSysLinkID:
		{
			if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 0)//��ֵ
			{
				MessageBox(MyWnds::ActInfoProc_hwnd, _T("�¹��ܻ��ڿ�����(��������)��"), _T("ά��"), MB_OK | MB_ICONERROR);
				//ShellExecute(NULL, _T("open"), _T("https://github.com/ISQIShI/Amusement-Park-Management-System"), NULL, NULL, SW_SHOW);
			}
			else if (PNMLINK(MyWnds::ActInfoProc_lParam)->item.iLink == 1)//����
			{
				MessageBox(MyWnds::ActInfoProc_hwnd, _T("û������������Ϩr���s�ߨt���q\n���ں�����չ(������������Ļ�)"), _T("ά��"), MB_OK | MB_ICONERROR);
			}
		}
		break;
		case logoutSysLinkID:
		{
			if (MessageBox(MyWnds::ActInfoProc_hwnd, _T("��ȷ��ע���û���\n��ע��˲������ɳ��أ�����"), _T("����"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
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
	case NM_DBLCLK://˫��
	{
		switch (LPNMHDR(MyWnds::ActInfoProc_lParam)->idFrom) {
		case actInfoListID:
		{

		}
		break;
		}
	}
	break;
	case NM_RCLICK://�һ�
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
		if (actInfoSysLinkFlag == 1)_stprintf_s(tempTCHAR, _T("�û��ǳƣ�"));
		else _stprintf_s(tempTCHAR, _T("�û��ǳƣ�%s"), currentAct.mName);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.15 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û�����%s"), currentAct.mID);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.3 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("���룺"));
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.45 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û�Ȩ�ޣ�%d"), currentAct.mPer.mAdmin);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.6 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û���%d"), currentAct.mCredit);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.75 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û�ע��ʱ�䣺%s %s"), currentAct.mRegTime.mDate, currentAct.mRegTime.mMoment);
		TextOut(MyWnds::hDC, int(0.1 * homePageWidth), int(0.9 * homePageHeight), tempTCHAR, wcslen(tempTCHAR));
	}
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), &ps);
	MyWnds::hDC = NULL;
}

void MyWnds::ActInfoProc_WM_CREATE() {
	//�༭�û��ǳ�
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"�༭\">�༭</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(editActNameSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editActNameSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//��������
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"��������\">��������</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(editPasswdSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, editPasswdSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//��ֵ/����
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"��ֵ\">��ֵ</A>")\
		_T("|<A HREF=\"����\"> ���� </A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(creditSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, creditSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ע���û�
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"ע���û�\">ע���û�</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
		int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		MyWnds::ActInfoProc_hwnd, HMENU(logoutSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, logoutSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�鿴�����û�����ҪȨ�ޣ�
	if (currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"�鿴�����û�\">�鿴�����û�</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
			int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			MyWnds::ActInfoProc_hwnd, HMENU(browseActSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
}

void MyWnds::ActInfo() {
	//��������---�û���Ϣ
	HWND actInfoHwnd = CreateWindowEx(
		0, _T("actInfoClassName"), _T("�û���Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
	);
	if (!actInfoHwnd) {
		//ʵ�������������---�û���Ϣ
		WNDCLASSEX actInfoClass = { 0 };
		actInfoClass.cbSize = sizeof(WNDCLASSEX);
		actInfoClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		actInfoClass.lpfnWndProc = MyWnds::ActInfoProc;//���ڹ���
		actInfoClass.hInstance = MyWnds::hInstance;//����ʵ��
		actInfoClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		actInfoClass.lpszClassName = _T("actInfoClassName");//��������
		actInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---�û���Ϣ
		if (!RegisterClassEx(&actInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---�û���Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}

		//��������---�û���Ϣ
		actInfoHwnd = CreateWindowEx(
			0, _T("actInfoClassName"), _T("�û���Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
		);
		if (!actInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---�û���Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//�豸��Ϣ
LRESULT CALLBACK MyWnds::DevInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::DevInfoProc_hwnd = hwnd;
	MyWnds::DevInfoProc_uMsg = uMsg;
	MyWnds::DevInfoProc_wParam = wParam;
	MyWnds::DevInfoProc_lParam = lParam;
	switch (uMsg)
	{
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::DevInfo() {
	//��������---�豸��Ϣ
	HWND devInfoHwnd = CreateWindowEx(
		0, _T("devInfoClassName"), _T("�豸��Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
	);
	if (!devInfoHwnd) {
		//ʵ�������������---�豸��Ϣ
		WNDCLASSEX devInfoClass = { 0 };
		devInfoClass.cbSize = sizeof(WNDCLASSEX);
		devInfoClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		devInfoClass.lpfnWndProc = MyWnds::DevInfoProc;//���ڹ���
		devInfoClass.hInstance = MyWnds::hInstance;//����ʵ��
		devInfoClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		devInfoClass.lpszClassName = _T("devInfoClassName");//��������
		devInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---�豸��Ϣ
		if (!RegisterClassEx(&devInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---�豸��Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//��������---�豸��Ϣ
		devInfoHwnd = CreateWindowEx(
			0, _T("devInfoClassName"), _T("�豸��Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
		);
		if (!devInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---�豸��Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//���׼�¼
LRESULT CALLBACK MyWnds::TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::TradeInfoProc_hwnd = hwnd;
	MyWnds::TradeInfoProc_uMsg = uMsg;
	MyWnds::TradeInfoProc_wParam = wParam;
	MyWnds::TradeInfoProc_lParam = lParam;
	switch (uMsg)
	{
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::TradeInfo() {
	//��������---���׼�¼
	HWND tradeInfoHwnd = CreateWindowEx(
		0, _T("tradeInfoClassName"), _T("���׼�¼"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
	);
	if (!tradeInfoHwnd) {
		//ʵ�������������---���׼�¼
		WNDCLASSEX tradeInfoClass = { 0 };
		tradeInfoClass.cbSize = sizeof(WNDCLASSEX);
		tradeInfoClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		tradeInfoClass.lpfnWndProc = MyWnds::TradeInfoProc;//���ڹ���
		tradeInfoClass.hInstance = MyWnds::hInstance;//����ʵ��
		tradeInfoClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		tradeInfoClass.lpszClassName = _T("tradeInfoClassName");//��������
		tradeInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---���׼�¼
		if (!RegisterClassEx(&tradeInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---���׼�¼��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//��������---���׼�¼
		tradeInfoHwnd = CreateWindowEx(
			0, _T("tradeInfoClassName"), _T("���׼�¼"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
		);
		if (!tradeInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---���׼�¼��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}


//����ģ̬�Ի���
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
					Account tempAct = { 0 };//����û�����
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), tempAct.mName, actName);//��ȡ�û��ǳ�
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), tempAct.mID, actUserName);//��ȡ�û���
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), tempAct.mPasswd, actPasswd);//��ȡ����
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID)));//��ȡȨ��
					if ( !(*tempAct.mName)|| !(*tempAct.mID) || !(*tempAct.mPasswd) || !(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("����������Ч������������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					tempAct.mPer.mAdmin = _wtoi(tempTCHAR);
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID)));//��ȡ���
					if (!(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("����������Ч������������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					if (dialogFlag == dialogActAdd && Data<Account>::DataSearch(_T("Account.dat"), tempAct.mID)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("��������û����Ѵ��ڣ�����������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					if (MyWnds::currentAct.mPer.mAdmin <= tempAct.mPer.mAdmin) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("�趨��Ȩ��ӦС������Ȩ��"), _T("Ȩ�޲���"), MB_ICONERROR);
						return 0;
					}
					tempAct.mCredit = _wtoi(tempTCHAR);
					//��ȡϵͳʱ��&�趨ע��ʱ��
					SYSTEMTIME sysTime;
					GetLocalTime(&sysTime);
					_stprintf_s(tempAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
					_stprintf_s(tempAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
					if(dialogFlag == dialogActAdd) Data<Account>::DataAdd(_T("Account.dat"), tempAct);	//���ú��������û�
					else Data<Account>::DataModify(_T("Account.dat"), tempAct);//���ú����޸��û�
					//ʹ��������
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//���ٴ��ڲ�����WM_DESTROY��Ϣ
					DestroyWindow(hwnd);
				}
				break;
				}
			}
			break;
			case cancelButtonID: {
				if (MessageBox(MyWnds::DialogProc_hwnd, _T("�رնԻ���"), _T("����԰����ϵͳ"), MB_OKCANCEL) == IDOK)
				{
					//ʹ��������
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//���ٴ��ڲ�����WM_DESTROY��Ϣ
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
		if (MessageBox(MyWnds::DialogProc_hwnd, _T("�رնԻ���"), _T("����԰����ϵͳ"), MB_OKCANCEL) == IDOK)
		{
			//ʹ��������
			EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
			//���ٴ��ڲ�����WM_DESTROY��Ϣ
			DestroyWindow(hwnd);
		}
	}
	break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);//����WM_QUIT��Ϣ
	}
	break;
	case WM_CTLCOLORSTATIC:
	{
		MyWnds::hDC = (HDC)MyWnds::DialogProc_wParam;
		SetTextColor(MyWnds::hDC, RGB(0, 0, 0));//����ǰ��ɫ
		//SetBkColor(MyWnds::hDC, RGB(174, 214, 241));//���ֱ���ɫ
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
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;

}

void MyWnds::DialogActAdd() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	//�ǳ�
	CreateWindowEx(
		0, WC_STATIC, _T("�ǳ�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight),int(0.1 * DialogWidth),int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), _T("�������û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�û���
	CreateWindowEx(
		0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), _T("�������û���"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), actUserName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//����
	CreateWindowEx(
		0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), _T("����������"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), actPasswd - 1); //���ƿ��ڱ༭�ؼ������������ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//Ȩ��
	CreateWindowEx(
		0, WC_STATIC, _T("Ȩ��"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actPerStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actPerEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), _T("������Ȩ��"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), 3); //���ƿ��ڱ༭�ؼ��������Ȩ�޵ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//���
	CreateWindowEx(
		0, WC_STATIC, _T("���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.71 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("���������"));//���ñ༭�ؼ��е��ı���ʾ
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogActModify() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Account tempAct = { 0 };//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempTCHAR[20] = {};
	//��ȡ���λ�õ��û���Ϣ
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	//�ļ�ָ���ƶ������û�����֮ǰ
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = (long long)(sizeof(Account)) * MyWnds::y_Listview;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
	CloseHandle(tempHANDLE);//�ر��ļ�
	//�ǳ�
	CreateWindowEx(
		0, WC_STATIC, _T("�ǳ�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), _T("�������û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�û���
	CreateWindowEx(
		0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	//����
	CreateWindowEx(
		0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL ,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), _T("����������"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), actPasswd - 1); //���ƿ��ڱ༭�ؼ������������ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//Ȩ��
	CreateWindowEx(
		0, WC_STATIC, _T("Ȩ��"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), _T("������Ȩ��"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), 3); //���ƿ��ڱ༭�ؼ��������Ȩ�޵ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actPerEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//���
	CreateWindowEx(
		0, WC_STATIC, _T("���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("���������"));//���ñ༭�ؼ��е��ı���ʾ
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

}


WPARAM MyWnds::Dialog() {
	//�����Ի���
	HWND dialogHwnd = CreateWindowEx(
		0, _T("dialogClassName"), _T("�Ի���"), WS_TILEDWINDOW | WS_VISIBLE ,
		int(0.45 * MyWnds::defScreenWidth), int(0.2 * MyWnds::defScreenHeight), int(0.7 * MyWnds::defMainWndHeight), int(0.8 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, NULL, MyWnds::hInstance, NULL
	);
	if (!dialogHwnd) {
		//ʵ�������������---�Ի���
		WNDCLASSEX dialogClass = { 0 };
		dialogClass.cbSize = sizeof(WNDCLASSEX);
		dialogClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		dialogClass.lpfnWndProc = MyWnds::DialogProc;//���ڹ���
		dialogClass.hInstance = MyWnds::hInstance;//����ʵ��
		dialogClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		dialogClass.lpszClassName = _T("dialogClassName");//��������
		dialogClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---�Ի���
		if (!RegisterClassEx(&dialogClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---�Ի���ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//��������---�Ի���
		dialogHwnd = CreateWindowEx(
			0, _T("dialogClassName"), _T("�Ի���"), WS_TILEDWINDOW | WS_VISIBLE,
			int(0.45 * MyWnds::defScreenWidth), int(0.2 * MyWnds::defScreenHeight), int(0.7 * MyWnds::defMainWndHeight), int(0.8 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, NULL, MyWnds::hInstance, NULL
		);
		if (!dialogHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---�Ի���ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
	//����������
	EnableWindow(MyWnds::MainWndProc_hwnd, FALSE);
	//������Ϣѭ��
	MSG Msg = { 0 };
	BOOL bRet = 1;
	while (bRet = (GetMessage(&Msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
		{
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��Ϣ����ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		else
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	//ǿ����������ʾ��ǰ̨
	ShowWindowAsync(MyWnds::MainWndProc_hwnd, SW_HIDE);
	ShowWindowAsync(MyWnds::MainWndProc_hwnd, SW_SHOW);
	return Msg.wParam;
}


//������¼��ť
void MyWnds::createLoginButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�����˺ţ���˵�¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//������¼ȷ�ϰ�ť
void MyWnds::createLoginConfirmButton() {
	CreateWindowEx(
		0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//����ע�ᰴť
void MyWnds::createRegisterButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("û���˺ţ����ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//����ע��ȷ�ϰ�ť
void MyWnds::createRegisterConfirmButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//������ҳ��ť
void MyWnds::createHomePageButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("��ҳ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(homePageButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����û���Ϣ��ť
void MyWnds::createActInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�û���Ϣ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����豸��Ϣ��ť
void MyWnds::createDevInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�豸��Ϣ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(devInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�������׼�¼��ť
void MyWnds::createTradeInfoButton(){
	TCHAR tempTCHAR[5] = _T("���Ѽ�¼");//��ͨ�û���ʾ���Ѽ�¼
	if (MyWnds::currentAct.mPer.mAdmin) {
		_stprintf_s(tempTCHAR, _T("���׼�¼"));//�й���Ȩ�޵��û���ʾ���׼�¼
	}
	CreateWindowEx(
		0, WC_BUTTON, tempTCHAR , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����˳�ϵͳ��ť
void MyWnds::createExitButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�˳�ϵͳ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(exitButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

//�����û��������
void MyWnds::createUserNameEdit_Static(){
	CreateWindowEx(
		0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), _T("�������û���"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), actUserName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�������������
void MyWnds::createPasswdEdit_Static(){
	CreateWindowEx(
		0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD,
		int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), _T("����������"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), actPasswd - 1); //���ƿ��ڱ༭�ؼ������������ĳ���
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����û��ǳ������
void MyWnds::createActNameEdit_Static(){
	CreateWindowEx(
		0, WC_STATIC, _T("�ǳ�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.285 * MyWnds::defMainWndWidth), int(0.21 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), _T("�������û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

//�����������ٶ���ؼ�&�Ӵ���
void MyWnds::DestroyControl(HWND hWnd,const std::initializer_list<int>& controlID) {
	for (auto cID : controlID) {
		DestroyWindow(GetDlgItem(hWnd, cID));
	}
}
//��������������ؼ�������ͬ��Ϣ (Ĭ��Ϊ�趨�������Ϣ)
void MyWnds::SendMessageToControl(HWND hWnd, const std::initializer_list<int>& controlID, UINT Msg, WPARAM wParam, LPARAM lParam) {
	for (auto cID : controlID) {
		SendMessage(GetDlgItem(hWnd, cID), Msg, wParam, lParam);
	}
}