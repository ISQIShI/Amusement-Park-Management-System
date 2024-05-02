#include<Windows.h>
#include<tchar.h>
#include<iostream>


//打开我的github项目页面
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
	
	MessageBox(NULL, _T("你好"), _T("世界"), MB_YESNO);
	return 0;
}