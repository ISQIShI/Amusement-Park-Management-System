#include"Door.h"
#include"Account.h"
#include"MyWnds.h"


void Door::Login() {
	MyWnds::createLoginConfirmButton();
	MyWnds::createRegisterButton();
	MyWnds::createUserNameEdit_Static();
	MyWnds::createPasswdEdit_Static();
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = LoginUI;
	MyWnds::mainWndFlag = LoginUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::LoginConfirm() {
	bool tempFlag = 0;//�趨��ʱ���
	Account tempAct = {0};//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempUserName[actUserName] = _T(""), tempPasswd[actPasswd] = _T("");//�����û�������û���������
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), tempUserName, actUserName);//��ȡ�û�������û���
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), tempPasswd, actPasswd);//��ȡ�û����������
	if (!*tempUserName || !*tempPasswd ) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	//����û���������
	if (Account::ActSearch(tempUserName, &tempAct)) {
		if (!_tcscmp(tempAct.mPasswd, tempPasswd)) {
			tempFlag = 1;//ƥ��ɹ�
			MyWnds::currentAct = tempAct;
		}
	}
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
	//������ҳ
	MyWnds::HomePage();
	MyWnds::createHomePageButton();
	MyWnds::createActInfoButton();
	MyWnds::createDevInfoButton();
	MyWnds::createTradeInfoButton();
	MyWnds::createExitButton();
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = HomeUI;
	MyWnds::mainWndFlag = HomeUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::Register() {
	MyWnds::createLoginButton();
	MyWnds::createRegisterConfirmButton();
	MyWnds::createActNameEdit_Static();
	MyWnds::createUserNameEdit_Static();
	MyWnds::createPasswdEdit_Static();
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = RegisterUI;
	MyWnds::mainWndFlag = RegisterUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::RegisterConfirm() {
	Account tempAct;//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), MyWnds::currentAct.mName, actName);//��ȡ�û�������ǳ�
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), MyWnds::currentAct.mUserName, actUserName);//��ȡ�û�������û���
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), MyWnds::currentAct.mPasswd, actPasswd);//��ȡ�û����������
	if (!*MyWnds::currentAct.mUserName|| !*MyWnds::currentAct.mPasswd|| !*MyWnds::currentAct.mName) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	//���������û����Ƿ��Ѵ���
	if (Account::ActSearch(MyWnds::currentAct.mUserName)) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("��������û����Ѵ��ڣ�����������"), _T("����"), MB_OK | MB_ICONERROR);
		return;
	}
	//�趨��ͨȨ��
	MyWnds::currentAct.mPer.mAdmin = normalPer;
	//�趨��ʼ���Ϊ0
	MyWnds::currentAct.mCredit = 0;
	//��ȡϵͳʱ��&�趨ע��ʱ��
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	_stprintf_s(MyWnds::currentAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	_stprintf_s(MyWnds::currentAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	//���ú��������û�
	Account::ActAdd(MyWnds::currentAct);
	//���ٿؼ�
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
	//������ҳ
	MyWnds::HomePage();
	MyWnds::createHomePageButton();
	MyWnds::createActInfoButton();
	MyWnds::createDevInfoButton();
	MyWnds::createTradeInfoButton();
	MyWnds::createExitButton();
	//���Ĵ��ڷ������
	MyWnds::mainWndStyle = HomeUI;
	MyWnds::mainWndFlag = HomeUI;
	//�ػ���������
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}