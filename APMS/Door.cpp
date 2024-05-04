#include"Door.h"
#include"Account.h"
#include"MyWnds.h"

void Door::Login() {
	//���ٿؼ�
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID));
	//������¼��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::defHFont, TRUE);
	//����ע�ᰴť
	CreateWindowEx(
		0, WC_BUTTON, _T("û���˺ţ����ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::defHFont, TRUE);
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = LoginUI;
	MyWnds::mainWndFlag = LoginUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::LoginConfirm() {
	bool tempFlag = 0;//�趨��ʱ���
	Account tempAct;//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempUserName[actUserName] = _T(""), tempPasswd[actPasswd] = _T("");//�����û�������û���������
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), tempUserName, actUserName);//��ȡ�û�������û���
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), tempPasswd, actPasswd);//��ȡ�û����������
	if (!*tempUserName || !*tempPasswd ) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	do{
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempAct.mUserName,tempUserName) && !_tcscmp(tempAct.mPasswd,tempPasswd)) {
			tempFlag = 1;//ƥ��ɹ�
			break;
		}
	} while (tempDWORD);
	CloseHandle(tempHANDLE);//�ر��ļ�
	if (!tempFlag) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("��������û����������������������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	//���ٿؼ�
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = HomeUI;
	MyWnds::mainWndFlag = HomeUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::Register() {
	//���ٿؼ�
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID));
	//������¼��ť
	CreateWindowEx(
		0, WC_BUTTON, _T("�����˺ţ���˵�¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(loginButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::defHFont, TRUE);
	//����ע�ᰴť
	CreateWindowEx(
		0, WC_BUTTON, _T("ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(registerConfirmButtonID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::defHFont, TRUE);
	//�����û��ǳ������
	CreateWindowEx(
		0, WC_STATIC, _T("�ǳ�"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
		int(0.285 * MyWnds::defMainWndWidth), int(0.21 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameStaticID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::defHFont, TRUE);
	CreateWindowEx(
		WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(actNameEditID), MyWnds::hInstance, NULL
	);
	Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), _T("�������û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
	Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
	SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::defHFont, TRUE);
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = RegisterUI;
	MyWnds::mainWndFlag = RegisterUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::RegisterConfirm() {
	bool tempFlag = 0;//�趨��ʱ���
	Account tempAct,writeAct;//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD;//���ʵ�ʶ�ȡ���ֽ���
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), writeAct.mName, actName);//��ȡ�û�������ǳ�
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), writeAct.mUserName, actUserName);//��ȡ�û�������û���
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), writeAct.mPasswd, actPasswd);//��ȡ�û����������
	if (!*writeAct.mUserName|| !*writeAct.mPasswd|| !*writeAct.mName) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempAct.mUserName, writeAct.mUserName)) {
			tempFlag = 1;//ƥ��ɹ�
			break;
		}
	} while (tempDWORD);
	CloseHandle(tempHANDLE);//�ر��ļ�
	if (tempFlag) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("��������û����Ѵ��ڣ�����������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(tempHANDLE, 0, NULL, FILE_END);
	writeAct.mPer.mAdmin = 0;
	writeAct.mCredit = 0;
	//��ȡϵͳʱ��
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	_stprintf_s(writeAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	_stprintf_s(writeAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	++Account::mCount;
	WriteFile(tempHANDLE,&writeAct ,sizeof(Account), NULL, NULL);
	CloseHandle(tempHANDLE);//�ر��ļ�
	//���ٿؼ�
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = HomeUI;
	MyWnds::mainWndFlag = HomeUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}