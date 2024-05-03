#include"MyWnds.h"


//构建窗口过程---主菜单
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg)
	{
	case WM_WINDOWPOSCHANGING:
	{
		WINDOWPOS * temp = (WINDOWPOS *) lParam;
		if (temp->cx < 960 ) {
			temp->cx = 960;
		}
		if (temp->cy < 540) {
			temp->cy = 540;
		}
	}
	break;
	case WM_WINDOWPOSCHANGED://更改窗口大小
	{
		WINDOWPOS* temp = (WINDOWPOS*)lParam;
		UINT newMainWndWidth = temp->cx;
		UINT newMainWndHeight = temp->cy;
		MoveWindow(GetDlgItem(hwnd, loginButtonID), int(0.27 * newMainWndWidth), int(0.55 * newMainWndHeight), int(0.15 * newMainWndWidth), int(0.15 * newMainWndHeight), true);
		MoveWindow(GetDlgItem(hwnd, registerButtonID), int(0.52 * newMainWndWidth), int(0.55 * newMainWndHeight), int(0.15 * newMainWndWidth), int(0.15 * newMainWndHeight), true);
		MoveWindow(GetDlgItem(hwnd, userNameStaticID), int(0.28 * newMainWndWidth), int(0.31 * newMainWndHeight), int(0.05 * newMainWndWidth), int(0.03 * newMainWndHeight), true);
		MoveWindow(GetDlgItem(hwnd, userNameEditID), int(0.33 * newMainWndWidth), int(0.3 * newMainWndHeight), int(0.31 * newMainWndWidth), int(0.05 * newMainWndHeight), true);
		MoveWindow(GetDlgItem(hwnd, passwdStaticID), int(0.285 * newMainWndWidth), int(0.41 * newMainWndHeight), int(0.05 * newMainWndWidth), int(0.03 * newMainWndHeight), true);
		MoveWindow(GetDlgItem(hwnd, passwdEditID), int(0.33 * newMainWndWidth), int(0.4 * newMainWndHeight), int(0.31 * newMainWndWidth), int(0.05 * newMainWndHeight), true);
	}
	break;
	case WM_CLOSE://关闭窗口
		if (MessageBox(hwnd, _T("是否确定退出系统？"), _T("游乐园管理系统"), MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY://销毁窗口
		PostQuitMessage(0);
		break;
	case WM_PAINT://重绘窗口
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CREATE://创建窗口
	{
		//创建登录按钮
		CreateWindowEx(
			0, WC_BUTTON, _T("登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15   * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(loginButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		//创建注册按钮
		CreateWindowEx(
			0, WC_BUTTON, _T("注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(registerButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		//创建用户名输入框
		CreateWindowEx(
			0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE| SS_SIMPLE,
			int(0.28 * defMainWndWidth), int(0.31 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(userNameStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""),  WS_CHILD  | WS_VISIBLE | ES_AUTOHSCROLL,
			int(0.33 * defMainWndWidth), int(0.3 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(userNameEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		//创建密码输入框
		CreateWindowEx(
			0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			int(0.285 * defMainWndWidth), int(0.41 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(passwdStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL|ES_PASSWORD,
			int(0.33 * defMainWndWidth), int(0.4 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(passwdEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
	}
	break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}


WPARAM MyWnds::MainWnd() {
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
		0,_T("mainWndClassName"),_T("游乐园管理系统"),WS_TILEDWINDOW,
		int(0.15*defScreenWidth),int( 0.15*defScreenHeight), defMainWndWidth, defMainWndHeight,
		NULL,NULL,hInstance,NULL
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
	return Msg.wParam;
}