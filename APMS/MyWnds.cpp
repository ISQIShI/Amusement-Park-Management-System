#include"MyWnds.h"

HDC hDC;
LOGFONT defLogFont;
HFONT defHFont;
HBRUSH defHBrush = CreateSolidBrush(RGB(133, 193, 233));//创建默认画刷
UINT newMainWndWidth = defMainWndWidth, newMainWndHeight = defMainWndHeight;

//构建窗口过程---主窗口
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg){
	case WM_WINDOWPOSCHANGING://准备更改窗口大小
	{
		WINDOWPOS * temp = (WINDOWPOS *) lParam;
		if (temp->cx < 960 ) {
			temp->cx = 960;
		}//如果新的窗口宽度小于960（像素），设定为960
		if (temp->cy < 540) {
			temp->cy = 540;
		}//如果新的窗口高度小于540（像素），设定为540
	}
	break;
	case WM_WINDOWPOSCHANGED://窗口大小完成更改
	{
		WINDOWPOS* temp = (WINDOWPOS*)lParam;//设定临时指针接收附加信息
		newMainWndWidth = temp->cx;//获取窗口新的宽度
		newMainWndHeight = temp->cy;//获取窗口新的高度
		//调整各控件大小，使其与主窗口大小自适应
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
			DeleteObject(defHBrush);//删除默认画刷
			DeleteObject(defHFont);//删除默认字体
			DestroyWindow(hwnd);//销毁窗口并发送WM_DESTROY消息
		}
		break;
	case WM_DESTROY://销毁窗口
		PostQuitMessage(0);//发布WM_QUIT消息
		break;
	case WM_CTLCOLORSTATIC://绘制static和edit(ES_READONLY)控件
	{
		hDC = (HDC)wParam;
		SetTextColor(hDC, RGB(0, 0, 0));//文字前景色
		//SetBkColor(hDC, RGB(174, 214, 241));//文字背景色
		SetBkMode(hDC, TRANSPARENT);
		hDC = NULL;
		return (INT_PTR)defHBrush;
	}
	case WM_PAINT://绘制窗口更新区域
	{
		//创建临时画刷
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//实例化绘图信息结构体对象
		PAINTSTRUCT ps;
		//获取主窗口的显示设备的环境句柄
		hDC = BeginPaint(hwnd, &ps);
		//绘制更新区域
		//FillRect(hDC, &ps.rcPaint, defHBrush);
		//绘制中央区域
		RECT center = { int(0.15 * newMainWndWidth), int(0.15 * newMainWndHeight), int(0.85 * newMainWndWidth), int(0.8 * newMainWndHeight)};
		FillRect(hDC, &center, tempBrush);
		//删除临时画刷
		DeleteObject(tempBrush);
		//释放主窗口的显示设备的环境句柄
		EndPaint(hwnd, &ps);
		hDC = NULL;
	}
	break;
	case WM_CREATE://创建窗口
	{
		
		//创建默认字体
		hDC = GetDC(hwnd);
		defLogFont.lfHeight = MulDiv(13, GetDeviceCaps(hDC, LOGPIXELSY), 72);//13是字号大小
		ReleaseDC(hwnd, hDC);
		hDC = NULL;
		//defLogFont.lfHeight = -20;
		defLogFont.lfWidth = 0;//字体中字符的平均宽度（以逻辑单位为单位）
		defLogFont.lfEscapement = 0;//转义向量与设备的 x 轴之间的角度（以十分之一度为单位）
		defLogFont.lfOrientation = 0;//每个字符的基线和设备 x 轴之间的角度（以十分之一度为单位）
		defLogFont.lfWeight = 550;//字体的粗细
		defLogFont.lfItalic = FALSE;//斜体
		defLogFont.lfUnderline = FALSE;//下划线
		defLogFont.lfStrikeOut = FALSE;//删除线
		defLogFont.lfCharSet = GB2312_CHARSET;//字符集
		defLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;//输出精度
		defLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;//剪裁精度
		defLogFont.lfQuality = ANTIALIASED_QUALITY;//输出质量
		defLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;//字体的间距和系列
		_stprintf_s(defLogFont.lfFaceName,_T("宋体"));//字体名称
		defHFont = CreateFontIndirect(&defLogFont);
		//创建登录按钮
		CreateWindowEx(
			0, WC_BUTTON, _T("登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15   * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(loginButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, loginButtonID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//创建注册按钮
		CreateWindowEx(
			0, WC_BUTTON, _T("注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(registerButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, registerButtonID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//创建用户名输入框
		CreateWindowEx(
			0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE| SS_SIMPLE,
			int(0.28 * defMainWndWidth), int(0.31 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(userNameStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, userNameStaticID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""),  WS_CHILD  | WS_VISIBLE | ES_AUTOHSCROLL,
			int(0.33 * defMainWndWidth), int(0.3 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(userNameEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, userNameEditID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//创建密码输入框
		CreateWindowEx(
			0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			int(0.285 * defMainWndWidth), int(0.41 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(passwdStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, passwdStaticID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL|ES_PASSWORD,
			int(0.33 * defMainWndWidth), int(0.4 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(passwdEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, passwdEditID), WM_SETFONT, (WPARAM)defHFont, TRUE);
	}
	break;
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}


WPARAM MyWnds::MainWnd() {
	//实例化窗口类对象---主窗口
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
	mainWndClass.lpfnWndProc = MainWndProc;//窗口过程
	mainWndClass.hInstance = hInstance;//程序实例
	mainWndClass.hbrBackground = defHBrush;//类背景画刷
	mainWndClass.lpszClassName = _T("mainWndClassName");//窗口类名
	mainWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
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