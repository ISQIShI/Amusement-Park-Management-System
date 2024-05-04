#include"general.h"

HINSTANCE hInstance;
int defScreenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
int defScreenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
int defMainWndWidth = 0.7*defScreenWidth;
int defMainWndHeight = 0.7* defScreenHeight;


//打开我的github项目页面
void OpenMyGitHubProjectPage() {
	//创建相关结构体对象
	SHELLEXECUTEINFO apms = { 0 };
	apms.cbSize = sizeof(SHELLEXECUTEINFO);
	//执行的行为---打开
	apms.lpVerb = _T("open");
	//利用默认浏览器打开的网址
	apms.lpFile = _T("https://github.com/ISQIShI/Amusement-Park-Management-System");
	//打开后的显示方式
	apms.nShow = SW_SHOW;
	//调用函数打开网址
	ShellExecuteEx(&apms);
}