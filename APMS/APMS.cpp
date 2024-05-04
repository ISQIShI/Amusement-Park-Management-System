#include"general.h"
#include"MyWnds.h"
#include"Account.h"
#include"Permission.h"
#include"Time.h"
#include"Door.h"
int WINAPI _tWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPTSTR lpCmdLine, _In_ INT nShowCmd)
{
	//接收应用程序的当前实例的句柄
	MyWnds::hInstance = _hInstance;
	MyWnds::MainWnd();

	return 0;
}