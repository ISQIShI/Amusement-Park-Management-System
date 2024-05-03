#include"general.h"



int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPTSTR lpCmdLine, INT nShowCmd) 
{
	
	thread(MyWnds::MainWnd,hInstance).join();
	system("pause");
	return 0;
}