#include<Windows.h>
#include<tchar.h>
#include<iostream>

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPTSTR lpCmdLine, int nShowCmd) 
{
	
	MessageBox(NULL, _T("���"), _T("����"), MB_YESNO);
	system("pause");
	return 0;
}