#include<Windows.h>
#include<tchar.h>
#include<iostream>


//���ҵ�github��Ŀҳ��
void OpenMyGitHubProjectPage(){
	SHELLEXECUTEINFO apms = { 0 };
	apms.cbSize = sizeof(SHELLEXECUTEINFO);
	apms.lpVerb = _T("open");
	apms.lpFile = _T("https://github.com/ISQIShI/Amusement-Park-Management-System");
	apms.nShow = SW_SHOW;
	ShellExecuteEx(&apms);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPTSTR lpCmdLine, INT nShowCmd) 
{	
	
	MessageBox(NULL, _T("���"), _T("����"), MB_YESNO);
	return 0;
}