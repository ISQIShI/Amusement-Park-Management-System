#include"MyWnds.h"

int WINAPI _tWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPTSTR lpCmdLine, _In_ INT nShowCmd)
{
	//接收应用程序的当前实例的句柄
	MyWnds::hInstance = _hInstance;
	//若没有用户信息，自动创建一个超级管理员
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (tempHANDLE != INVALID_HANDLE_VALUE) {
		Account writeAct;
		_stprintf_s(writeAct.mName , _T("超级管理员"));
		_stprintf_s(writeAct.mUserName, _T("SuperAdmin"));
		_stprintf_s(writeAct.mPasswd, _T("SuperAdmin"));
		writeAct.mPer.mAdmin = superPer;
		writeAct.mCredit = 0;
		//获取系统时间
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		_stprintf_s(writeAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
		_stprintf_s(writeAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
		++Account::mCount;
		DWORD written;
		WriteFile(tempHANDLE, &writeAct, sizeof(Account),&written, NULL);
		CloseHandle(tempHANDLE);//关闭文件
	}
	return MyWnds::MainWnd();
}