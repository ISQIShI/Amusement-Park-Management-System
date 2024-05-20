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
			Account::ActInfo();
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
			Device::DevInfo();
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
			Trade::TradeInfo();
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
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;//�趨��ʱָ����ո�����Ϣ
	MyWnds::defMainWndWidth = temp->cx;//��ȡ�����µĿ��
	MyWnds::defMainWndHeight = temp->cy;//��ȡ�����µĸ߶�
	MyWnds::homePageWidth = int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth);
	MyWnds::homePageHeight = int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight);
	MyWnds::lastfontFlag = MyWnds::fontFlag;
	//�������ؼ���С��ʹ���������ڴ�С����Ӧ
	if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; MyWnds::fontFlag = defSmallFont; }
	else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; MyWnds::fontFlag = defMidFont; }
	else { MyWnds::currentHFONT = MyWnds::defLargeHFont; MyWnds::fontFlag = defLargeFont; }
	EnumChildWindows(MyWnds::MainWndProc_hwnd, MyWnds::EnumChildProc_AdaptiveWnd, NULL);
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
	SetBkMode(MyWnds::hDC, TRANSPARENT);//����͸��
	MyWnds::hDC = NULL;
	return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
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
		WS_EX_CONTROLPARENT,_T("mainWndClassName"),_T("����԰����ϵͳ"),WS_TILEDWINDOW,
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
			if (!IsDialogMessage(mainHwnd, &Msg)) //�ú������������Ϣ(��TAB�л��ؼ�����)
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
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

//��ҳ
LRESULT CALLBACK MyWnds::HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	MyWnds::HomePageProc_hwnd = hwnd;
	MyWnds::HomePageProc_uMsg = uMsg;
	MyWnds::HomePageProc_wParam = wParam;
	MyWnds::HomePageProc_lParam = lParam;
	switch (uMsg)
	{
	case WM_CREATE:
	{
		//GitHubҳ��
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"GitHub����\">https://github.com/ISQIShI/Amusement-Park-Management-System</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
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
		case NM_CLICK:case NM_RETURN://����
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
		SetTextColor(MyWnds::hDC, RGB(46, 134, 193));//����ǰ��ɫ
		//SetBkColor(MyWnds::hDC, RGB(93, 173, 226));//���ֱ���ɫ
		//SetBkMode(MyWnds::hDC, TRANSPARENT);//����͸��
		TextOut(MyWnds::hDC, int(0.4  * MyWnds::homePageWidth), int(0.1  * MyWnds::homePageHeight), _T("��ӭʹ������԰����ϵͳ"), wcslen(_T("��ӭʹ������԰����ϵͳ")));
		TextOut(MyWnds::hDC, int(0.28 * MyWnds::homePageWidth), int(0.13 * MyWnds::homePageHeight), _T("Welcome to the Amusement Park Management System"), wcslen(_T("Welcome to the Amusement Park Management System")));
		SetTextColor(MyWnds::hDC, RGB(52, 152, 219));//����ǰ��ɫ

		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.25 * MyWnds::homePageHeight), _T("��ϵͳ����Ҫ���ܣ�"), wcslen(_T("��ϵͳ����Ҫ���ܣ�")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.28 * MyWnds::homePageHeight), _T("��ͨ�˻���"), wcslen(_T("��ͨ�˻���")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.31 * MyWnds::homePageHeight), _T("��ѯ/�޸ĸ�����Ϣ"), wcslen(_T("��ѯ/�޸ĸ�����Ϣ")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.34 * MyWnds::homePageHeight), _T("��ѯ����԰�豸��Ϣ"), wcslen(_T("��ѯ����԰�豸��Ϣ��")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.37 * MyWnds::homePageHeight), _T("��ѯ�������Ѽ�¼"), wcslen(_T("��ѯ�������Ѽ�¼")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), _T("����Ա�˻���"), wcslen(_T("����Ա�˻���")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.43 * MyWnds::homePageHeight), _T("��ѯ/�޸ĸ�����Ϣ"), wcslen(_T("��ѯ/�޸ĸ�����Ϣ")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.46 * MyWnds::homePageHeight), _T("����/�޸�/ɾ�������û���Ϣ(��ҪȨ�޸��ڶԷ��˻�)"), wcslen(_T("����/�޸�/ɾ�������û���Ϣ(��ҪȨ�޸��ڶԷ��˻�)")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.49 * MyWnds::homePageHeight), _T("����/�޸�/ɾ�������豸��Ϣ"), wcslen(_T("����/�޸�/ɾ�������豸��Ϣ")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.52 * MyWnds::homePageHeight), _T("����/�޸�/ɾ�����н��׼�¼"), wcslen(_T("����/�޸�/ɾ�����н��׼�¼")));

		SetTextColor(MyWnds::hDC, RGB(46, 134, 193));//����ǰ��ɫ
		TextOut(MyWnds::hDC, int(0.39 * MyWnds::homePageWidth), int(0.8  * MyWnds::homePageHeight), _T("����ĿΪ��һ���ڿ�����Ŀ"), wcslen(_T("����ĿΪ��һ���ڿ�����Ŀ")));
		TextOut(MyWnds::hDC, int(0.41 * MyWnds::homePageWidth), int(0.83 * MyWnds::homePageHeight), _T("Created By ISQIShI"), wcslen(_T("Created By ISQIShI")));
		TextOut(MyWnds::hDC, int(0.3 * MyWnds::homePageWidth), int(0.86 * MyWnds::homePageHeight), _T("��Ŀ���������·����ӣ������ҵ�GitHubҳ��鿴"), wcslen(_T("��Ŀ���������·����ӣ������ҵ�GitHubҳ��鿴")));

		EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID), &ps);
		MyWnds::hDC = NULL;
		break;
	}
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::HomePage(){
	//��������---��ҳ
	HWND homePageHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("homePageClassName"), _T("��ҳ"), WS_TILED | WS_CHILD | WS_VISIBLE,
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
			WS_EX_CONTROLPARENT, _T("homePageClassName"), _T("��ҳ"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(homePageWndID), MyWnds::hInstance, NULL
		);
		if (!homePageHwnd) {
			MessageBox(NULL, _T("��������---��ҳ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
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
					//��ȡϵͳʱ��&�趨¼��ʱ��
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
					break;
				}
				
				case dialogDevAdd: case dialogDevModify:
				{
					TCHAR tempTCHAR[21];
					Device tempDev = { 0 };//����豸����
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), tempDev.mName, devName);//��ȡ�豸����
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), tempDev.mID, devID);//��ȡ�豸ID
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID)));//��ȡ�۸�
					if (!(*tempDev.mName) || !(*tempDev.mID) || !(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("����������Ч������������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					tempDev.mPrice = _wtoi(tempTCHAR);
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID)));//��ȡ�շ�
					if (!(*tempTCHAR)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("����������Ч������������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					if (dialogFlag == dialogDevAdd && Data<Device>::DataSearch(_T("Device.dat"), tempDev.mID)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("��������豸ID�Ѵ��ڣ�����������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					tempDev.mCharge = _wtoi(tempTCHAR);
					//��ȡϵͳʱ��&�趨¼��ʱ��
					SYSTEMTIME sysTime;
					GetLocalTime(&sysTime);
					_stprintf_s(tempDev.mAddTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
					_stprintf_s(tempDev.mAddTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
					if (dialogFlag == dialogDevAdd) Data<Device>::DataAdd(_T("Device.dat"), tempDev);	//���ú��������豸
					else Data<Device>::DataModify(_T("Device.dat"), tempDev);//���ú����޸��豸
					//ʹ��������
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//���ٴ��ڲ�����WM_DESTROY��Ϣ
					DestroyWindow(hwnd);
					break;
				}
				case dialogTradeAdd: case dialogTradeModify:
				{
					TCHAR tempTCHAR[21];
					Trade tempTrade = { 0 };//��Ž�������
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), tempTrade.mID, tradeID);//��ȡ�豸ID
					Edit_GetText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID)));//��ȡ���׽��
					if (!(*tempTrade.mID) || !(*tempTCHAR)|| ComboBox_GetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID)) == -1 || ComboBox_GetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID)) == -1) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("����������Ч������������"), _T("����"), MB_ICONERROR);
						return 0;
					}
					
					if (dialogFlag == dialogTradeAdd && Data<Trade>::DataSearch(_T("Trade.dat"), tempTrade.mID)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("������Ľ���ID�Ѵ��ڣ�����������"), _T("����"), MB_ICONERROR);
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
					if (dialogFlag == dialogTradeAdd) Data<Trade>::DataAdd(_T("Trade.dat"), tempTrade);	//���ú����������׼�¼
					else Data<Trade>::DataModify(_T("Trade.dat"), tempTrade);//���ú����޸Ľ��׼�¼
					//ʹ��������
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//���ٴ��ڲ�����WM_DESTROY��Ϣ
					DestroyWindow(hwnd);
					break;
				}
				case dialogTradeSelect:
				{
					int y;
					bool flag = 0;
					TCHAR tempTCHAR[31] = {}, _tempTCHAR[31] = {};
					if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 3) && ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 4)) {
						MessageBox(MyWnds::DialogProc_hwnd, _T("������ͬʱ���û������Ѻ��豸������ɸѡ"), _T("����"), MB_ICONERROR);
						return 0;
					}
					//��ǰ�����ȡɸѡ�б��ѡ��ѡ��״̬�������������˳�򣬺����ɸѡ����ǰ���ɸѡ��
					for ( y = 0; y < ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID)); ++y) {
						if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), y)) {
							//��ȡɸѡѡ��
							ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), y, 0, tempTCHAR, 21 );
							if (!_tcscmp(tempTCHAR, _T("���û�"))) {
								//�Խ��׼�¼�б�Ӻ���ǰ���û�ɾ��(����ɾ������ļ�¼ǰ��ļ�¼����������)
								for (int yy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; yy >= 0; --yy) {
									//��ȡ��ǰ��¼���û���
									ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy, 3, tempTCHAR, actUserName );
									for (int yyy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID)) - 1; yyy >= 0; --yyy) {
										if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yyy)) {
											//��ȡɸѡ�б���ѡ�����û���
											ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yyy, 0, _tempTCHAR, actUserName );
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) { flag = 1; break; }
										}
									}
									//�������ɸѡ�����������ü�¼
									if (flag) { flag = 0; continue; }
									//�����ϣ�ɾ����¼
									ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy);
								}
							}
							else if (!_tcscmp(tempTCHAR, _T("���豸"))) {
								//�Խ��׼�¼�б�Ӻ���ǰ���豸ɾ��(����ɾ������ļ�¼ǰ��ļ�¼����������)
								for (int yy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; yy >= 0; --yy) {
									//��ȡ��ǰ��¼���豸ID
									ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy, 4, tempTCHAR, devID );
									for (int yyy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID)) - 1; yyy >= 0; --yyy) {
										if (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yyy)) {
											//��ȡɸѡ�б���ѡ�����豸ID
											ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yyy, 0, _tempTCHAR, devID );
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) { flag = 1; break; }
										}
									}
									//�������ɸѡ�����������ü�¼
									if (flag) { flag = 0; continue; }
									//�����ϣ�ɾ����¼
									ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy);
								}
							}
							else if (!_tcscmp(tempTCHAR, _T("��ʱ��"))) {
								//�Խ��׼�¼�б�Ӻ���ǰ��ʱ��ɾ��(����ɾ������ļ�¼ǰ��ļ�¼����������)
								for (int yy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; yy >= 0; --yy) {
									//��ȡ��ǰ��¼��ʱ��
									ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy, 5, tempTCHAR, timeDate + timeMoment);
									TCHAR tempTimeA[timeDate + timeMoment] = {}, tempTimeB[timeDate + timeMoment] = {};
									//��ʼʱ��
									SYSTEMTIME tempTime;
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), &tempTime);
									_stprintf_s(tempTimeA, _T("%04d-%02d-%02d"), tempTime.wYear, tempTime.wMonth, tempTime.wDay);
									wcscat_s(tempTimeA, _T(" "));
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), &tempTime);
									_stprintf_s(_tempTCHAR, _T("%02d:%02d:%02d"), tempTime.wHour, tempTime.wMinute, tempTime.wSecond);
									wcscat_s(tempTimeA, _tempTCHAR);
									//��ֹʱ��
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateBTimeID), &tempTime);
									_stprintf_s(tempTimeB, _T("%04d-%02d-%02d"), tempTime.wYear, tempTime.wMonth, tempTime.wDay);
									wcscat_s(tempTimeB, _T(" "));
									DateTime_GetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentBTimeID), &tempTime);
									_stprintf_s(_tempTCHAR, _T("%02d:%02d:%02d"), tempTime.wHour, tempTime.wMinute, tempTime.wSecond);
									wcscat_s(tempTimeB, _tempTCHAR);

									//�������ɸѡ�����������ü�¼
									if (_tcscmp(tempTCHAR,tempTimeA)>=0 && _tcscmp(tempTCHAR,tempTimeB)<=0) continue;
									//�����ϣ�ɾ����¼
									ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yy);
								}
							}
							else if (!_tcscmp(tempTCHAR, _T("���û�������"))) {
								int consume = 0;//���ֳ�������
								int itemCount = 0;
								//�����µ�һ��--�û�������
								LVCOLUMN temp = { 0 };
								temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
								temp.fmt = LVCFMT_CENTER;
								temp.cx = int(0.2 * MyWnds::homePageWidth);
								temp.pszText = (LPTSTR)_T("�û�������");
								temp.iSubItem = 6;
								temp.cxDefault = 1;
								temp.cxMin = int(0.2 * MyWnds::homePageWidth);
								ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 6, &temp);
								LVITEM tempINSERT = { 0 };
								tempINSERT.mask = LVIF_TEXT;
								//��ȡ�û�ѡ���б��ÿһ���û�
								for (int yy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID)) - 1; yy >= 0; --yy) {
									//���ûѡ���û������㲢��ʾÿ���û��������ܶ���ѡ�˰��û���ֻ��ʾѡ����û��������ܶ
									if (!ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 0) || (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 0) && ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yy))) {
										//��ȡɸѡ�б���ѡ�����û���
										UINT totalConsume = 0;
										ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), yy, 0, tempTCHAR, actUserName);
										for (int yyy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1 - itemCount; yyy >= 0; --yyy) {
											//��ȡ��ǰ��¼���û���
											ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 3, _tempTCHAR, actUserName);
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) {
												//��ȡ���׽��
												ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 2, _tempTCHAR, 11);
												totalConsume += _wtoi(_tempTCHAR);
												//��¼��ý������ݱ�ɾ��������¼
												ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy);
											}
										}
										consume += totalConsume;
										//���б�ĩβ�����µ�����
										tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
										tempINSERT.iSubItem = 0;
										_stprintf_s(_tempTCHAR, _T("%d"), 0);
										tempINSERT.pszText = _tempTCHAR;
										ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//�û���
										tempINSERT.iSubItem = 3;
										tempINSERT.pszText = tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//������
										tempINSERT.iSubItem = 6;
										_stprintf_s(_tempTCHAR, _T("%d"), totalConsume);
										tempINSERT.pszText = _tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);										
										++itemCount;
									}
								}
								//���б�ĩβ�������ֳ�������
								tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
								tempINSERT.iSubItem = 0;
								_stprintf_s(_tempTCHAR, _T("%d"), 0);
								tempINSERT.pszText = _tempTCHAR;
								ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//�û���
								tempINSERT.iSubItem = 3;
								tempINSERT.pszText = (LPTSTR)_T("������");
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//������
								tempINSERT.iSubItem = 6;
								_stprintf_s(_tempTCHAR, _T("%d"), consume);
								tempINSERT.pszText = _tempTCHAR;
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//ɾ������Ҫ����
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 5);//����ʱ��
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 4);//�豸ID
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 2);//���
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 1);//����ID
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 0);//���
							}
							else if (!_tcscmp(tempTCHAR, _T("���豸������"))) {
								int income = 0;//���ֳ�������
								int itemCount = 0;
								//�����µ�һ��--�豸������
								LVCOLUMN temp = { 0 };
								temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
								temp.fmt = LVCFMT_CENTER;
								temp.cx = int(0.2 * MyWnds::homePageWidth);
								temp.pszText = (LPTSTR)_T("�豸������");
								temp.iSubItem = 6;
								temp.cxDefault = 1;
								temp.cxMin = int(0.2 * MyWnds::homePageWidth);
								ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 6, &temp);
								LVITEM tempINSERT = { 0 };
								tempINSERT.mask = LVIF_TEXT;
								//��ȡ�豸ѡ���б��ÿһ���豸
								for (int yy = ListView_GetItemCount(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID)) - 1; yy >= 0; --yy) {
									//���ûѡ���豸�����㲢��ʾÿ���豸�������ܶ���ѡ�˰��豸��ֻ��ʾѡ����豸�������ܶ
									if (!ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 1) || (ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 1) && ListView_GetCheckState(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yy))) {
										//��ȡɸѡ�б���ѡ�����豸ID
										UINT totalIncome = 0;
										ListView_GetItemText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), yy, 0, tempTCHAR, devID);
										for (int yyy = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1 - itemCount; yyy >= 0; --yyy) {
											//��ȡ��ǰ��¼���豸ID
											ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 4, _tempTCHAR, devID);
											if (!_tcscmp(tempTCHAR, _tempTCHAR)) {
												//��ȡ���׽��
												ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy, 2, _tempTCHAR, 11);
												totalIncome += _wtoi(_tempTCHAR);
												//��¼��ý������ݱ�ɾ��������¼
												ListView_DeleteItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), yyy);
											}
										}
										income += totalIncome;
										//���б�ĩβ�����µ�����
										tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
										tempINSERT.iSubItem = 0;
										_stprintf_s(_tempTCHAR, _T("%d"), 0);
										tempINSERT.pszText = _tempTCHAR;
										ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//�豸ID
										tempINSERT.iSubItem = 4;
										tempINSERT.pszText = tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										//������
										tempINSERT.iSubItem = 6;
										_stprintf_s(_tempTCHAR, _T("%d"), totalIncome);
										tempINSERT.pszText = _tempTCHAR;
										ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

										++itemCount;
									}
								}
								//���б�ĩβ����������
								tempINSERT.iItem = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
								tempINSERT.iSubItem = 0;
								_stprintf_s(_tempTCHAR, _T("%d"), 0);
								tempINSERT.pszText = _tempTCHAR;
								ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//�豸ID
								tempINSERT.iSubItem = 4;
								tempINSERT.pszText = (LPTSTR)_T("������");
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//������
								tempINSERT.iSubItem = 6;
								_stprintf_s(_tempTCHAR, _T("%d"), income);
								tempINSERT.pszText = _tempTCHAR;
								ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

								//ɾ������Ҫ����
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 5);//����ʱ��
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 3);//�û���
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 2);//���
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 1);//����ID
								ListView_DeleteColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 0);//���
							}
						}
					}
					ShowWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, tradeSelectSysLinkID), SW_HIDE);
					ShowWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoSysLinkID), SW_HIDE);
					//����
					CreateWindowEx(
						0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
						int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
						Trade::TradeInfoProc_hwnd, HMENU(returnSysLinkID), MyWnds::hInstance, NULL
					);
					SendMessage(GetDlgItem(Trade::TradeInfoProc_hwnd, returnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

					//ʹ��������
					EnableWindow(MyWnds::MainWndProc_hwnd, TRUE);
					//���ٴ��ڲ�����WM_DESTROY��Ϣ
					DestroyWindow(hwnd);
					break;
				}
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), _T("�������û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û��ǳƵĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�û���
	CreateWindowEx(
		0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("���������"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), 10); //���ƿ��ڱ༭�ؼ�����������ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogActModify() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Account tempAct = { 0 };//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempTCHAR[21] = {};
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mID, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetReadOnly(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), TRUE);//����ֻ��״̬
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//����
	CreateWindowEx(
		0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, tempTCHAR, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.7 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(actCreditEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), _T("���������"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), 10); //���ƿ��ڱ༭�ؼ�����������ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, actCreditEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

}

void MyWnds::DialogDevAdd() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	//�豸����
	CreateWindowEx(
		0, WC_STATIC, _T("�豸����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), _T("�������豸����"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), devName - 1); //���ƿ��ڱ༭�ؼ���������豸���Ƶĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�豸ID
	CreateWindowEx(
		0, WC_STATIC, _T("�豸ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), _T("�������豸ID"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), devID - 1); //���ƿ��ڱ༭�ؼ���������豸ID�ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�۸�
	CreateWindowEx(
		0, WC_STATIC, _T("�۸�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.41 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devPriceStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.4 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devPriceEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), _T("������۸�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), 10); //���ƿ��ڱ༭�ؼ�������ļ۸�ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�շ�
	CreateWindowEx(
		0, WC_STATIC, _T("�շ�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.56 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devChargeStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.55 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devChargeEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), _T("�������շ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), 10); //���ƿ��ڱ༭�ؼ���������շѵĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogDevModify() {
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Device tempDev = { 0 };//��Ž�Ҫ��ȡ���豸����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempTCHAR[21] = {};
	//��ȡ���λ�õ��豸��Ϣ
	HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	//�ļ�ָ���ƶ������豸����֮ǰ
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = (long long)(sizeof(Device)) * MyWnds::y_Listview;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
	CloseHandle(tempHANDLE);//�ر��ļ�
	//�豸����
	CreateWindowEx(
		0, WC_STATIC, _T("�豸����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempDev.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), _T("�������豸����"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), devName - 1); //���ƿ��ڱ༭�ؼ���������豸���Ƶĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�豸ID
	CreateWindowEx(
		0, WC_STATIC, _T("�豸ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, tempDev.mID, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(devIDEditID), MyWnds::hInstance, NULL
	);
	Edit_SetReadOnly(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), TRUE);//����ֻ��״̬
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�۸�
	CreateWindowEx(
		0, WC_STATIC, _T("�۸�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), _T("������۸�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), 10); //���ƿ��ڱ༭�ؼ�������ļ۸�ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devPriceEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�շ�
	CreateWindowEx(
		0, WC_STATIC, _T("�շ�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), _T("�������շ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), 10); //���ƿ��ڱ༭�ؼ���������շѵĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devChargeEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogTradeAdd(){
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	//����ID
	CreateWindowEx(
		0, WC_STATIC, _T("����ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.04 * DialogWidth), int(0.11 * DialogHeight), int(0.1 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeIDStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.1 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeIDEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), _T("�����뽻��ID"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), tradeID - 1); //���ƿ��ڱ༭�ؼ�������Ľ���ID�ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeIDEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//���׽��
	CreateWindowEx(
		0, WC_STATIC, _T("���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.05 * DialogWidth), int(0.26 * DialogHeight), int(0.12 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMoneyStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_NUMBER | WS_TABSTOP,
		int(0.15 * DialogWidth), int(0.25 * DialogHeight), int(0.8 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMoneyEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), _T("�����뽻�׽��"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), 10); //���ƿ��ڱ༭�ؼ�������Ľ��׽��ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�û���
	CreateWindowEx(
		0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	//����Ͽ�����������û���Ϣ
	Account tempAct;//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), tempAct.mID);
	}
	CloseHandle(tempHANDLE);//�ر��ļ�
	//�豸ID
	CreateWindowEx(
		0, WC_STATIC, _T("�豸ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Device tempDev;//��Ž�Ҫ��ȡ���豸����
	tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), tempDev.mID);
	}
	CloseHandle(tempHANDLE);//�ر��ļ�
	//����ʱ��
	CreateWindowEx(
		0, WC_STATIC, _T("����ʱ��"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.71 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeAStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeAStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//����
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE ,
		int(0.2 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ʱ��
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.52 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogTradeModify(){
	int DialogWidth = int(0.7 * MyWnds::defMainWndHeight), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	Trade tempTrade = { 0 };//��Ž�Ҫ��ȡ�Ľ�������
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempTCHAR[21] = {};
	//��ȡ���λ�õĽ��׼�¼
	HANDLE tempHANDLE = CreateFile(_T("Trade.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	//�ļ�ָ���ƶ����ý�������֮ǰ
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = (long long)(sizeof(Trade)) * MyWnds::y_Listview;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	ReadFile(tempHANDLE, &tempTrade, sizeof(Trade), &tempDWORD, NULL);//��ȡ�ļ�
	CloseHandle(tempHANDLE);//�ر��ļ�
	//����ID
	CreateWindowEx(
		0, WC_STATIC, _T("����ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	//���׽��
	CreateWindowEx(
		0, WC_STATIC, _T("���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Edit_SetCueBannerText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), _T("�����뽻�׽��"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), 10); //���ƿ��ڱ༭�ؼ�������Ľ��׽��ĳ���
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMoneyEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�û���
	CreateWindowEx(
		0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	//����Ͽ�����������û���Ϣ
	Account tempAct;//��Ž�Ҫ��ȡ���û�����
	tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	int index = 0;//��¼��ѡ���ݵ�����
	tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), tempAct.mID);
		if (!_tcscmp(tempAct.mID, tempTrade.mUserName)) index = x;
	}
	CloseHandle(tempHANDLE);//�ر��ļ�
	ComboBox_SetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, userNameComboBoxID), index);
	//�豸ID
	CreateWindowEx(
		0, WC_STATIC, _T("�豸ID"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	Device tempDev;//��Ž�Ҫ��ȡ���豸����
	tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		ComboBox_AddString(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), tempDev.mID);
		if (!_tcscmp(tempDev.mID, tempTrade.mDevID)) index = x;
	}
	CloseHandle(tempHANDLE);//�ر��ļ�
	ComboBox_SetCurSel(GetDlgItem(MyWnds::DialogProc_hwnd, devIDComboBoxID), index);
	//����ʱ��
	CreateWindowEx(
		0, WC_STATIC, _T("����ʱ��"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.02 * DialogWidth), int(0.71 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeAStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeAStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//����
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
	//ʱ��
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.52 * DialogWidth), int(0.7 * DialogHeight), int(0.27 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	DateTime_SetSystemtime(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), GDT_VALID, &tempTime);
	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.2 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.6 * DialogWidth), int(0.8 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(cancelButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, cancelButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::DialogTradeSelect(){
	int DialogWidth = int(0.7 * MyWnds::defMainWndWidth), DialogHeight = int(0.8 * MyWnds::defMainWndHeight);
	
	//ɸѡѡ��
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.1 * DialogWidth), int(0.05 * DialogHeight), int(0.2 * DialogWidth), int(0.25 * DialogHeight),
		MyWnds::DialogProc_hwnd, (HMENU)selectListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//������
	LVCOLUMN temp = { 0 };
	temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
	temp.fmt = LVCFMT_CENTER;
	temp.cx = int(0.2 * DialogWidth);
	temp.pszText = (LPTSTR)_T("ɸѡѡ��");
	temp.iSubItem = 0;
	temp.cxDefault = 0;
	temp.cxMin = int(0.2 * DialogWidth);
	ListView_InsertColumn(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), 0, &temp);
	//������
	LVITEM tempINSERT = { 0 };
	tempINSERT.mask = LVIF_TEXT;
	tempINSERT.iItem = 0;
	tempINSERT.iSubItem = 0;
	tempINSERT.pszText = (LPTSTR)_T("���û�");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("���豸");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("��ʱ��");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("���û�������");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	++tempINSERT.iItem;
	tempINSERT.pszText = (LPTSTR)_T("���豸������");
	ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, selectListID), &tempINSERT);

	//��ʼʱ��
	CreateWindowEx(
		0, WC_STATIC, _T("��ʼʱ��"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.1 * DialogWidth), int(0.33 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeAStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeAStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//����
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE,
		int(0.1 * DialogWidth), int(0.37 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ʱ��
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.1 * DialogWidth), int(0.42 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentATimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentATimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//��ֹʱ��
	CreateWindowEx(
		0, WC_STATIC, _T("��ֹʱ��"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.1 * DialogWidth), int(0.48 * DialogHeight), int(0.17 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeTimeBStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeTimeBStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//����
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE,
		int(0.1 * DialogWidth), int(0.52 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeDateBTimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeDateBTimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ʱ��
	CreateWindowEx(
		0, DATETIMEPICK_CLASS, _T(""), WS_CHILD | WS_VISIBLE | DTS_TIMEFORMAT,
		int(0.1 * DialogWidth), int(0.57 * DialogHeight), int(0.2 * DialogWidth), int(0.05 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(tradeMomentBTimeID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, tradeMomentBTimeID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);


	//�û���
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.4 * DialogWidth), int(0.05 * DialogHeight), int(0.2 * DialogWidth), int(0.8 * DialogHeight),
		MyWnds::DialogProc_hwnd, (HMENU)userNameSelectListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//������
	temp.pszText = (LPTSTR)_T("�û���");
	temp.cxDefault = 0;
	ListView_InsertColumn(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), 0, &temp);
	Account tempAct;//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	int index = 0;//��¼��ѡ���ݵ�����
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		tempINSERT.iItem = x;
		tempINSERT.iSubItem = 0;
		tempINSERT.pszText = tempAct.mID;
		ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, userNameSelectListID), &tempINSERT);
	}
	CloseHandle(tempHANDLE);//�ر��ļ�


	//�豸ID
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.7 * DialogWidth), int(0.05 * DialogHeight), int(0.2 * DialogWidth), int(0.8 * DialogHeight),
		MyWnds::DialogProc_hwnd, (HMENU)devIDSelectListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//������
	temp.pszText = (LPTSTR)_T("�豸ID");
	temp.cxDefault = 0;
	ListView_InsertColumn(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), 0, &temp);
	Device tempDev;//��Ž�Ҫ��ȡ���豸����
	tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		tempINSERT.iItem = x;
		tempINSERT.iSubItem = 0;
		tempINSERT.pszText = tempDev.mID;
		ListView_InsertItem(GetDlgItem(MyWnds::DialogProc_hwnd, devIDSelectListID), &tempINSERT);
	}
	CloseHandle(tempHANDLE);//�ر��ļ�

	//ȷ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȷ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.1 * DialogWidth), int(0.67 * DialogHeight), int(0.2 * DialogWidth), int(0.1 * DialogHeight),
		MyWnds::DialogProc_hwnd, HMENU(confirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::DialogProc_hwnd, confirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ȡ��
	CreateWindowEx(
		0, WC_BUTTON, _T("ȡ��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
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
	//�����Ի���
	HWND dialogHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("dialogClassName"), _T("�Ի���"), WS_TILEDWINDOW | WS_VISIBLE ,
		x, y, cx, cy,
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
			WS_EX_CONTROLPARENT, _T("dialogClassName"), _T("�Ի���"), WS_TILEDWINDOW | WS_VISIBLE,
			x, y, cx, cy,
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
			if (!IsDialogMessage(dialogHwnd, &Msg)) //�ú������������Ϣ
			{
				TranslateMessage(&Msg);
				DispatchMessage(&Msg);
			}
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
		0, WC_BUTTON, _T("�����˺ţ���˵�¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//������¼ȷ�ϰ�ť
void MyWnds::createLoginConfirmButton() {
	CreateWindowEx(
		0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.27 * MyWnds::MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//����ע�ᰴť
void MyWnds::createRegisterButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("û���˺ţ����ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//����ע��ȷ�ϰ�ť
void MyWnds::createRegisterConfirmButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//������ҳ��ť
void MyWnds::createHomePageButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("��ҳ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(homePageButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����û���Ϣ��ť
void MyWnds::createActInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�û���Ϣ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����豸��Ϣ��ť
void MyWnds::createDevInfoButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�豸��Ϣ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
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
		0, WC_BUTTON, tempTCHAR , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
//�����˳�ϵͳ��ť
void MyWnds::createExitButton(){
	CreateWindowEx(
		0, WC_BUTTON, _T("�˳�ϵͳ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL| WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD| WS_TABSTOP,
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
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
		int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), _T("�������û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

//ö�������Ӵ��ڣ�����Ӧ��С�����壩
BOOL CALLBACK MyWnds::EnumChildProc_AdaptiveWnd(HWND hwndChild, LPARAM lParam) {
	
	if (MyWnds::lastfontFlag != MyWnds::fontFlag) {
		//��������
		SendMessage(hwndChild, WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		//�ػ���������
		InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
		SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
	}
	//���´�С
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

	case homePageWndID://��ҳ
		MoveWindow(hwndChild, int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight, TRUE);
		break;
	case gitHubSysLinkID:
		MoveWindow(hwndChild, int(0.23 * MyWnds::homePageWidth), int(0.89 * MyWnds::homePageHeight), int(0.7 * MyWnds::homePageWidth), int(0.03 * MyWnds::homePageHeight), TRUE);
		break;

	case actInfoWndID://�û���Ϣ
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
		
	case devInfoWndID://�豸��Ϣ
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

	case tradeInfoWndID://���׼�¼
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


HWND ListCompareHandle = NULL;
bool ListCompareFlag = 1;
//�����б�����ıȽ�
int CALLBACK ListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort) {
	TCHAR tempTCHAR[51], _tempTCHAR[51];
	ListView_GetItemText(GetDlgItem(ListCompareHandle, dataInfoListID), lParam1, LPNMLISTVIEW(lParamSort)->iSubItem, tempTCHAR, 51);
	ListView_GetItemText(GetDlgItem(ListCompareHandle, dataInfoListID), lParam2, LPNMLISTVIEW(lParamSort)->iSubItem, _tempTCHAR, 51);
	LVCOLUMN temp;
	ListView_GetColumn(GetDlgItem(ListCompareHandle, dataInfoListID), LPNMLISTVIEW(lParamSort)->iSubItem, &temp);
	if (temp.cxDefault) {
		//�ж��������ַ��ͻ�����ֵ��
		if (ListCompareFlag)
		{
			return _wtoi(tempTCHAR) - _wtoi(_tempTCHAR);//����
		}
		else {
			return _wtoi(_tempTCHAR) - _wtoi(tempTCHAR);//����
		}
	}
	if (ListCompareFlag) {
		return _tcscmp(tempTCHAR, _tempTCHAR);//����
	}
	else {
		return _tcscmp(_tempTCHAR, tempTCHAR);//����
	}
}