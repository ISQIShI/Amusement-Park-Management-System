#include"general.h"

HINSTANCE hInstance;
int defScreenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
int defScreenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
int defMainWndWidth = 0.7*defScreenWidth;
int defMainWndHeight = 0.7* defScreenHeight;


//���ҵ�github��Ŀҳ��
void OpenMyGitHubProjectPage() {
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