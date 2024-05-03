#include"general.h"
#include"MyWnds.h"


int WINAPI _tWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPTSTR lpCmdLine, _In_ INT nShowCmd)
{
	
	thread(MyWnds::MainWnd,hInstance).join();
	return 0;
}