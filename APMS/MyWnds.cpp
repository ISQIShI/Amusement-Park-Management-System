#include"MyWnds.h"

HINSTANCE MyWnds::hInstance;
int MyWnds::defScreenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
int MyWnds::defScreenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
int MyWnds::defMainWndWidth = int(0.7 * defScreenWidth);
int MyWnds::defMainWndHeight = int(0.7 * defScreenHeight);
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
BYTE MyWnds::currentPer = 0;

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

HWND MyWnds::DevInfoProc_hwnd;
UINT MyWnds::DevInfoProc_uMsg;
WPARAM MyWnds::DevInfoProc_wParam;
LPARAM MyWnds::DevInfoProc_lParam;

HWND MyWnds::TradeInfoProc_hwnd;
UINT MyWnds::TradeInfoProc_uMsg;
WPARAM MyWnds::TradeInfoProc_wParam;
LPARAM MyWnds::TradeInfoProc_lParam;

void MyWnds::GetInfoCount() {
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
		MyWnds::GetInfoCount();
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
	WORD tempHIWORD = HIWORD(MyWnds::MainWndProc_wParam);
	//��������ť����Ϣ
	if (tempHIWORD == BN_CLICKED) {
		switch (LOWORD(MyWnds::MainWndProc_wParam)) {
		case loginButtonID: {
			//���ٿؼ�
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
			Door::Login();
		}
		break;
		case loginConfirmButtonID: {
			Door::LoginConfirm();
		}
		break;
		case registerButtonID: {
			//���ٿؼ�
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
			DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
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
				DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID));
				DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID));
				DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID));
				DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID));
				DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID));
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
	//�������ؼ���С��ʹ���������ڴ�С����Ӧ
	if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; tempFontFlag = defSmallFont; }
	else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; tempFontFlag = defMidFont; }
	else { MyWnds::currentHFONT = MyWnds::defLargeHFont; tempFontFlag = defLargeFont; }
	switch (MyWnds::mainWndFlag)
	{
	case LoginUI: 
	{
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
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
	break;
	case RegisterUI:
	{	
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
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
	break;
	case HomeUI:
	{
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X *3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight), true);
	}
	break;
	case ActInfoUI:{
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight), true);
	}
	break;
	case DevInfoUI: {
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight), true);

	}
	break;
	case TradeInfoUI: {
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�ػ���������
			InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), int(homePageButtonCoord_X * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoWndID), int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight), true);

	}
	break;
	}
	
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

void MyWnds::DestroyChildWnd() {
	switch (MyWnds::mainWndFlag) {
	case HomeUI: {
		DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageWndID));
	}
	break;
	case ActInfoUI: {
		DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID));
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
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::ActInfo() {
	//��������---�û���Ϣ
	HWND actInfoHwnd = CreateWindowEx(
		0, _T("actInfoClassName"), _T("�û���Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
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
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), int((1 - homePageButtonCoord_X * 3 - homePageButtonWidth) * MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6 + homePageButtonHeight) * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
		);
		if (!tradeInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---���׼�¼��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}






void MyWnds::createLoginButton(){
	//������¼��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("�����˺ţ���˵�¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createLoginConfirmButton() {
	//������¼ȷ�ϰ�ť
	CreateWindowEx(
		0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createRegisterButton(){
	//����ע�ᰴť
	CreateWindowEx(
		0, WC_BUTTON, _T("û���˺ţ����ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createRegisterConfirmButton(){
	//����ע��ȷ�ϰ�ť
	CreateWindowEx(
		0, WC_BUTTON, _T("ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createHomePageButton(){
	//������ҳ��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("��ҳ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int(homePageButtonCoord_Y * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(homePageButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, homePageButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createActInfoButton(){
	//�����û���Ϣ��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("�û���Ϣ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.15) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createDevInfoButton(){
	//�����豸��Ϣ��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("�豸��Ϣ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.3) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(devInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createTradeInfoButton(){
	TCHAR tempTCHAR[5] = _T("���Ѽ�¼");//��ͨ�û���ʾ���Ѽ�¼
	if (currentPer) {
		_stprintf_s(tempTCHAR, _T("���׼�¼"));//�й���Ȩ�޵��û���ʾ���׼�¼
	}
	//�������׼�¼��ť
	CreateWindowEx(
		0, WC_BUTTON, tempTCHAR , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.45) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}
void MyWnds::createExitButton(){
	//�����˳�ϵͳ��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("�˳�ϵͳ"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(homePageButtonCoord_X * MyWnds::MyWnds::defMainWndWidth), int((homePageButtonCoord_Y + 0.6) * MyWnds::defMainWndHeight), int(homePageButtonWidth * MyWnds::defMainWndWidth), int(homePageButtonHeight * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(exitButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, exitButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
}

void MyWnds::createUserNameEdit_Static(){
	//�����û��������
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
void MyWnds::createPasswdEdit_Static(){
	//�������������
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
void MyWnds::createActNameEdit_Static(){
	//�����û��ǳ������
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