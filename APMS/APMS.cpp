#include"general.h"
#include"MyWnds.h"

int WINAPI _tWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPTSTR lpCmdLine, _In_ INT nShowCmd)
{
	//接收应用程序的当前实例的句柄
	hInstance = _hInstance;


	MyWnds::MainWnd();
	return 0;
}