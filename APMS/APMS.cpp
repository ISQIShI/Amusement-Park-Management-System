#include"general.h"
#include"MyWnds.h"
#include"Account.h"
#include"Permission.h"
#include"Time.h"
#include"Door.h"
int WINAPI _tWinMain(_In_ HINSTANCE _hInstance, _In_opt_ HINSTANCE hPreInstance, _In_ LPTSTR lpCmdLine, _In_ INT nShowCmd)
{
	//����Ӧ�ó���ĵ�ǰʵ���ľ��
	MyWnds::hInstance = _hInstance;
	MyWnds::MainWnd();

	return 0;
}