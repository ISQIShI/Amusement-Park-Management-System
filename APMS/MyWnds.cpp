#include"MyWnds.h"

HINSTANCE MyWnds::hInstance;
int MyWnds::defScreenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
int MyWnds::defScreenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
int MyWnds::defMainWndWidth = int(0.7 * defScreenWidth);
int MyWnds::defMainWndHeight = int(0.7 * defScreenHeight);
HDC MyWnds::hDC;
HBRUSH MyWnds::defHBrush = CreateSolidBrush(RGB(133, 193, 233));//创建默认画刷

LOGFONT MyWnds::defLogFont;
HFONT MyWnds::defSmallHFont;
HFONT MyWnds::defMidHFont;
HFONT MyWnds::defLargeHFont;
HFONT MyWnds::currentHFONT;
BYTE MyWnds::fontFlag;

BYTE MyWnds::mainWndStyle = LoginUI;
BYTE MyWnds::mainWndFlag = LoginUI;

HWND MyWnds::MainWndProc_hwnd;
UINT MyWnds::MainWndProc_uMsg;
WPARAM MyWnds::MainWndProc_wParam;
LPARAM MyWnds::MainWndProc_lParam;

HWND MyWnds::HomePageProc_hwnd;
UINT MyWnds::HomePageProc_uMsg;
WPARAM MyWnds::HomePageProc_wParam;
LPARAM MyWnds::HomePageProc_lParam;

void MyWnds::CreateFont() {
	//创建默认字体
	MyWnds::defLogFont.lfEscapement = 0;//转义向量与设备的 x 轴之间的角度（以十分之一度为单位）
	MyWnds::defLogFont.lfOrientation = 0;//每个字符的基线和设备 x 轴之间的角度（以十分之一度为单位）
	MyWnds::defLogFont.lfWeight = 550;//字体的粗细
	MyWnds::defLogFont.lfItalic = FALSE;//斜体
	MyWnds::defLogFont.lfUnderline = FALSE;//下划线
	MyWnds::defLogFont.lfStrikeOut = FALSE;//删除线
	MyWnds::defLogFont.lfCharSet = GB2312_CHARSET;//字符集
	MyWnds::defLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;//输出精度
	MyWnds::defLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;//剪裁精度
	MyWnds::defLogFont.lfQuality = ANTIALIASED_QUALITY;//输出质量
	MyWnds::defLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;//字体的间距和系列
	_stprintf_s(MyWnds::defLogFont.lfFaceName, _T("宋体"));//字体名称
	//小字体
	MyWnds::hDC = GetDC(MyWnds::MainWndProc_hwnd);//获取设备环境句柄
	MyWnds::defLogFont.lfHeight = MulDiv(11, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//10是字号大小
	MyWnds::defLogFont.lfWidth = 0;//字体中字符的平均宽度（以逻辑单位为单位）
	MyWnds::defSmallHFont = CreateFontIndirect(&MyWnds::defLogFont);
	//中字体
	MyWnds::defLogFont.lfHeight = MulDiv(13, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//13是字号大小
	MyWnds::defLogFont.lfWidth = 0;
	MyWnds::defMidHFont = CreateFontIndirect(&MyWnds::defLogFont);
	//大字体
	MyWnds::defLogFont.lfHeight = MulDiv(17, GetDeviceCaps(MyWnds::hDC, LOGPIXELSY), 72);//17是字号大小
	MyWnds::defLogFont.lfWidth = 0;
	MyWnds::defLargeHFont = CreateFontIndirect(&MyWnds::defLogFont);
	ReleaseDC(MyWnds::MainWndProc_hwnd, MyWnds::hDC);//释放设备环境句柄
	MyWnds::hDC = NULL;//hDC置空
}

//构建窗口过程---主窗口
LRESULT CALLBACK MyWnds::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MyWnds::MainWndProc_hwnd = hwnd;
	MyWnds::MainWndProc_uMsg = uMsg;
	MyWnds::MainWndProc_wParam = wParam;
	MyWnds::MainWndProc_lParam = lParam;
	switch (uMsg){
	case WM_COMMAND:
		MyWnds::MainWndProc_WM_COMMAND();
		break;
	case WM_WINDOWPOSCHANGING://准备更改窗口大小
		MyWnds::MainWndProc_WM_WINDOWPOSCHANGING();
		break;
	case WM_WINDOWPOSCHANGED://窗口大小完成更改
		MyWnds::MainWndProc_WM_WINDOWPOSCHANGED();
		break;
	case WM_CLOSE://关闭窗口
		MyWnds::MainWndProc_WM_CLOSE();
		break;
	case WM_DESTROY://销毁窗口
		MyWnds::MainWndProc_WM_DESTROY();
		break;
	case WM_CTLCOLORSTATIC://绘制static和edit(ES_READONLY)控件
		return MyWnds::MainWndProc_WM_CTLCOLORSTATIC();
	case WM_PAINT://绘制窗口更新区域
		MyWnds::MainWndProc_WM_PAINT();
		break;
	case WM_CREATE://创建窗口
		{
		MyWnds::CreateFont();
		if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; MyWnds::fontFlag = defSmallFont; }
		else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; MyWnds::fontFlag = defMidFont; }
		else { MyWnds::currentHFONT = MyWnds::defLargeHFont; MyWnds::fontFlag = defLargeFont; }

		//创建登录按钮
		CreateWindowEx(
			0, WC_BUTTON, _T("登录"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(loginConfirmButtonID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		//创建注册按钮
		CreateWindowEx(
			0, WC_BUTTON, _T("没有账号？点此注册"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(registerButtonID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		//创建用户名输入框
		CreateWindowEx(
			0, WC_STATIC, _T("用户名"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(userNameStaticID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)currentHFONT, TRUE);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(userNameEditID), MyWnds::hInstance, NULL
		);
		Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), _T("请输入用户名"));//设置编辑控件中的文本提示
		Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), actUserName - 1); //限制可在编辑控件中输入的用户名的长度
		SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		//创建密码输入框
		CreateWindowEx(
			0, WC_STATIC, _T("密码"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(passwdStaticID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD,
			int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight),
			MyWnds::MainWndProc_hwnd, HMENU(passwdEditID), MyWnds::hInstance, NULL
		);
		Edit_SetCueBannerText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), _T("请输入密码"));//设置编辑控件中的文本提示
		Edit_LimitText(GetDlgItem(MyWnds::MainWndProc_hwnd,passwdEditID),actPasswd-1); //限制可在编辑控件中输入的密码的长度
		SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
	break;
	default://未自定义的其他消息
		return DefWindowProc(MyWnds::MainWndProc_hwnd, uMsg, wParam, MyWnds::MainWndProc_lParam);//默认窗口过程
	}
	return 0;
}

void MyWnds::MainWndProc_WM_COMMAND() {
	WORD tempHIWORD = HIWORD(MyWnds::MainWndProc_wParam);
	//处理点击按钮的消息
	if (tempHIWORD == BN_CLICKED) {
		switch (LOWORD(MyWnds::MainWndProc_wParam)) {
		case loginButtonID: {
			Door::Login();
		}
		break;
		case loginConfirmButtonID: {
			Door::LoginConfirm();
		}
		break;
		case registerButtonID: {
			Door::Register();
		}
		break;
		case registerConfirmButtonID: {
			Door::RegisterConfirm();
		}
		break;
		}
	}
}

void MyWnds::MainWndProc_WM_WINDOWPOSCHANGING(){
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;
	if (temp->cx < 960) {
		temp->cx = 960;
	}//如果新的窗口宽度小于960（像素），设定为960
	if (temp->cy < 540) {
		temp->cy = 540;
	}//如果新的窗口高度小于540（像素），设定为540
}

void MyWnds::MainWndProc_WM_WINDOWPOSCHANGED(){
	BYTE tempFontFlag;
	WINDOWPOS* temp = (WINDOWPOS*)MyWnds::MainWndProc_lParam;//设定临时指针接收附加信息
	MyWnds::defMainWndWidth = temp->cx;//获取窗口新的宽度
	MyWnds::defMainWndHeight = temp->cy;//获取窗口新的高度
	//调整各控件大小，使其与主窗口大小自适应
	if (MyWnds::defMainWndWidth < 1080 || MyWnds::defMainWndHeight < 608) { MyWnds::currentHFONT = MyWnds::defSmallHFont; tempFontFlag = defSmallFont; }
	else if (MyWnds::defMainWndWidth < 1320 || MyWnds::defMainWndHeight < 743) { MyWnds::currentHFONT = MyWnds::defMidHFont; tempFontFlag = defMidFont; }
	else { MyWnds::currentHFONT = MyWnds::defLargeHFont; tempFontFlag = defLargeFont; }
	switch (MyWnds::mainWndFlag)
	{
	case LoginUI: 
	{
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//重绘整个窗口
			InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID), int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID), int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
	}
	break;
	case RegisterUI:
	{	
		if (tempFontFlag != MyWnds::fontFlag) {
			MyWnds::fontFlag = tempFontFlag;
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//重绘整个窗口
			InvalidateRect(MyWnds::MyWnds::MainWndProc_hwnd, NULL, TRUE);
			SendMessage(MyWnds::MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
		}
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID), int(0.27 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID), int(0.52 * MyWnds::defMainWndWidth), int(0.55 * MyWnds::defMainWndHeight), int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID), int(0.285 * MyWnds::defMainWndWidth), int(0.21 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.2 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID), int(0.28 * MyWnds::defMainWndWidth), int(0.31 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.3 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID), int(0.285 * MyWnds::defMainWndWidth), int(0.41 * MyWnds::defMainWndHeight), int(0.05 * MyWnds::defMainWndWidth), int(0.03 * MyWnds::defMainWndHeight), true);
		MoveWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), int(0.33 * MyWnds::defMainWndWidth), int(0.4 * MyWnds::defMainWndHeight), int(0.31 * MyWnds::defMainWndWidth), int(0.05 * MyWnds::defMainWndHeight), true);
	}
	break;
	}
	
}
void MyWnds::MainWndProc_WM_CLOSE(){
	if (MessageBox(MyWnds::MainWndProc_hwnd, _T("是否确定退出系统？"), _T("游乐园管理系统"), MB_OKCANCEL) == IDOK)
	{
		DeleteObject(MyWnds::defHBrush);//删除默认画刷
		DeleteObject(MyWnds::defSmallHFont);//删除小字体
		DeleteObject(MyWnds::defMidHFont);//删除中字体
		DeleteObject(MyWnds::defLargeHFont);//删除大字体
		DestroyWindow(MyWnds::MainWndProc_hwnd);//销毁窗口并发送WM_DESTROY消息
	}
}
void MyWnds::MainWndProc_WM_DESTROY(){
	PostQuitMessage(0);//发布WM_QUIT消息
}
LRESULT MyWnds::MainWndProc_WM_CTLCOLORSTATIC(){
	MyWnds::hDC = (HDC)MyWnds::MainWndProc_wParam;
	SetTextColor(MyWnds::hDC, RGB(0, 0, 0));//文字前景色
	//SetBkColor(MyWnds::hDC, RGB(174, 214, 241));//文字背景色
	SetBkMode(MyWnds::hDC, TRANSPARENT);
	MyWnds::hDC = NULL;
	return (INT_PTR)MyWnds::defHBrush;
}
void MyWnds::MainWndProc_WM_PAINT(){
	switch (MyWnds::mainWndStyle) {
	case LoginUI: case RegisterUI:
	{
		//创建临时画刷
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//实例化绘图信息结构体对象
		PAINTSTRUCT ps;
		//获取主窗口的显示设备的环境句柄
		MyWnds::hDC = BeginPaint(MyWnds::MainWndProc_hwnd, &ps);
		//绘制更新区域
		//FillRect(MyWnds::hDC, &ps.rcPaint, defHBrush);
		//绘制中央区域
		RECT center = { int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), int(0.85 * MyWnds::defMainWndWidth), int(0.8 * MyWnds::defMainWndHeight) };
		FillRect(MyWnds::hDC, &center, tempBrush);
		//删除临时画刷
		DeleteObject(tempBrush);
		//释放主窗口的显示设备的环境句柄
		EndPaint(MyWnds::MainWndProc_hwnd, &ps);
		MyWnds::hDC = NULL;
	}
	 break;
	case HomeUI:
	{
		//创建临时画刷
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//实例化绘图信息结构体对象
		PAINTSTRUCT ps;
		//获取主窗口的显示设备的环境句柄
		MyWnds::hDC = BeginPaint(MyWnds::MainWndProc_hwnd, &ps);
		//绘制更新区域
		//FillRect(MyWnds::hDC, &ps.rcPaint, MyWnds::defHBrush);
		//绘制中央区域
		//RECT center = { int(0.15 * MyWnds::defMainWndWidth), int(0.15 * MyWnds::defMainWndHeight), int(0.85 * MyWnds::defMainWndWidth), int(0.8 * MyWnds::defMainWndHeight) };
		//FillRect(MyWnds::hDC, &center, tempBrush);
		//删除临时画刷
		DeleteObject(tempBrush);
		//释放主窗口的显示设备的环境句柄
		EndPaint(MyWnds::MainWndProc_hwnd, &ps);
		MyWnds::hDC = NULL;
	}
	break;
	}
}


WPARAM MyWnds::MainWnd() {
	//实例化窗口类对象---主窗口
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
	mainWndClass.lpfnWndProc = MyWnds::MainWndProc;//窗口过程
	mainWndClass.hInstance = MyWnds::hInstance;//程序实例
	mainWndClass.hbrBackground = MyWnds::defHBrush;//类背景画刷
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
		int(0.15 * MyWnds::defScreenWidth),int( 0.15 * MyWnds::defScreenHeight), MyWnds::defMainWndWidth, MyWnds::defMainWndHeight,
		NULL,NULL, MyWnds::hInstance,NULL
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
			MessageBox(NULL, _T("消息检索失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
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



LRESULT CALLBACK MyWnds::HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	MyWnds::HomePageProc_hwnd = hwnd;
	MyWnds::HomePageProc_uMsg = uMsg;
	MyWnds::HomePageProc_wParam = wParam;
	MyWnds::HomePageProc_lParam = lParam;
	switch (uMsg)
	{
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}
void MyWnds::HomePageProc_WM_COMMAND(){

}
void MyWnds::HomePageProc_WM_WINDOWPOSCHANGING(){

}
void MyWnds::HomePageProc_WM_WINDOWPOSCHANGED(){

}
void MyWnds::HomePageProc_WM_CLOSE(){

}
void MyWnds::HomePageProc_WM_DESTROY(){

}
LRESULT MyWnds::HomePageProc_WM_CTLCOLORSTATIC(){	
	return (INT_PTR)MyWnds::defHBrush;
}
void MyWnds::HomePageProc_WM_PAINT(){

}

void MyWnds::HomePage(){
	//实例化窗口类对象---主页
	WNDCLASSEX homePageClass = { 0 };
	homePageClass.cbSize = sizeof(WNDCLASSEX);
	homePageClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
	homePageClass.lpfnWndProc = MyWnds::HomePageProc;//窗口过程
	homePageClass.hInstance = MyWnds::hInstance;//程序实例
	homePageClass.hbrBackground = HBRUSH(6);//类背景画刷
	homePageClass.lpszClassName = _T("homePageClassName");//窗口类名
	homePageClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
	//注册窗口类---主页
	if (!RegisterClassEx(&homePageClass)) {
		MessageBox(NULL, _T("注册窗口类---主窗口，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//创建窗口---主页
	HWND homePageHwnd = CreateWindowEx(
		0, _T("homePageClassName"), _T("主页"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int(0.45 * MyWnds::defMainWndWidth), int(0.25 * MyWnds::defMainWndHeight), int(0.5*MyWnds::defMainWndWidth), int(0.5*MyWnds::defMainWndHeight),
		MyWnds::MainWndProc_hwnd, HMENU(homePageWnd), MyWnds::hInstance, NULL
	);
	if (!homePageHwnd) {
		MessageBox(NULL, _T("创建窗口---主页，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}	
}