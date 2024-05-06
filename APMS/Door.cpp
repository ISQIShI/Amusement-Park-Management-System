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
			MyWnds::currentPer = tempAct.mPer.mAdmin;
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
	writeAct.mPer.mAdmin = normalPer;
	MyWnds::currentPer = writeAct.mPer.mAdmin;
	writeAct.mCredit = 0;
	//��ȡϵͳʱ��
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	_stprintf_s(writeAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	_stprintf_s(writeAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	++Account::mCount;
	DWORD written;
	WriteFile(tempHANDLE,&writeAct ,sizeof(Account), &written, NULL);
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