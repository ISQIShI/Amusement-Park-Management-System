#include"MyWnds.h"

int WINAPI _tWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPTSTR lpCmdLine, _In_ INT nShowCmd)
{
	//����Ӧ�ó���ĵ�ǰʵ���ľ��
	MyWnds::hInstance = _hInstance;
	//��û���û���Ϣ���Զ�����һ����������Ա
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANDLE != INVALID_HANDLE_VALUE) {
		Account writeAct;
		_stprintf_s(writeAct.mName , _T("��������Ա"));
		_stprintf_s(writeAct.mUserName, _T("SuperAdmin"));
		_stprintf_s(writeAct.mPasswd, _T("SuperAdmin"));
		writeAct.mPer.mAdmin = superPer;
		writeAct.mCredit = 0;
		//��ȡϵͳʱ��
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		_stprintf_s(writeAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		_stprintf_s(writeAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		++Account::mCount;
		DWORD written;
		WriteFile(tempHANDLE, &writeAct, sizeof(Account),&written, NULL);
		CloseHandle(tempHANDLE);//�ر��ļ�
	}
	return MyWnds::MainWnd();
}