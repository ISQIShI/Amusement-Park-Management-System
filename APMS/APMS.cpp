#include"general.h"

//���ҵ�github��Ŀҳ��
void OpenMyGitHubProjectPage(){
	//������ؽṹ�����
	SHELLEXECUTEINFO apms = { 0 };
	apms.cbSize = sizeof(SHELLEXECUTEINFO);
	//ִ�е���Ϊ---��
	apms.lpVerb = _T("open");
	//����Ĭ��������򿪵���ַ
	apms.lpFile = _T("https://github.com/ISQIShI/Amusement-Park-Management-System");
	//�򿪺����ʾ��ʽ
	apms.nShow = SW_SHOW;
	//���ú�������ַ
	ShellExecuteEx(&apms);
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPTSTR lpCmdLine, INT nShowCmd) 
{	
	thread(MyWnds::MainWnd,hInstance).join();
	system("pause");
	return 0;
}