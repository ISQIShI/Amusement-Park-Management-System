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

//�������ڹ���---���˵�
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE:
		if (MessageBox(hwnd, _T("�Ƿ�ȷ���˳�ϵͳ��"), _T("����԰����ϵͳ"), MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam); 
		break;
	}
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPreInstance,LPTSTR lpCmdLine, INT nShowCmd) 
{	
	//ʵ�������������---������
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.lpfnWndProc = MainWindowProc;
	mainWndClass.hInstance = hInstance;
	mainWndClass.lpszClassName = _T("mainWndClassName");
	//ע�ᴰ����---������
	if (!RegisterClassEx(&mainWndClass)) {
		MessageBox(NULL, _T("ע�ᴰ����---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//��������---������
	HWND mainHwnd = CreateWindowEx(
		0,
		_T("mainWndClassName"),
		_T("����԰����ϵͳ"),
		WS_TILEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!mainHwnd) {
		MessageBox(NULL, _T("��������---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//��ʾ����---������
	ShowWindow(mainHwnd, SW_SHOW);
	//������Ϣѭ��
	MSG Msg = {0};
	BOOL bRet = 1;
	while (bRet=(GetMessage(&Msg, NULL, 0, 0))!=0) {
		if (bRet == -1)
		{
			MessageBox(NULL, _T("��Ϣ����---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		else
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
	return 0;
}