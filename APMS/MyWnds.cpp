#include"MyWnds.h"

//构建窗口过程---主菜单
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CLOSE:
		if (MessageBox(hwnd, _T("是否确定退出系统？"), _T("游乐园管理系统"), MB_OKCANCEL) == IDOK)
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


void MyWnds::MainWnd(HINSTANCE hInstance) {
	//实例化窗口类对象---主窗口
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.lpfnWndProc = MainWndProc;
	mainWndClass.hInstance = hInstance;
	mainWndClass.lpszClassName = _T("mainWndClassName");
	//注册窗口类---主窗口
	if (!RegisterClassEx(&mainWndClass)) {
		MessageBox(NULL, _T("注册窗口类---主窗口，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//创建窗口---主窗口
	HWND mainHwnd = CreateWindowEx(
		0,
		_T("mainWndClassName"),
		_T("游乐园管理系统"),
		WS_TILEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	if (!mainHwnd) {
		MessageBox(NULL, _T("创建窗口---主窗口，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//显示窗口---主窗口
	ShowWindow(mainHwnd, SW_SHOW);
	//构建消息循环
	MSG Msg = { 0 };
	BOOL bRet = 1;
	while (bRet = (GetMessage(&Msg, NULL, 0, 0)) != 0) {
		if (bRet == -1)
		{
			MessageBox(NULL, _T("消息检索---主窗口，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		else
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
}