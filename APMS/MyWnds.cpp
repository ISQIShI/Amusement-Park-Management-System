#include"MyWnds.h"

HINSTANCE MyWnds::hInstance;
int MyWnds::defScreenWidth = GetSystemMetrics(SM_CXMAXIMIZED);
int MyWnds::defScreenHeight = GetSystemMetrics(SM_CYMAXIMIZED);
int MyWnds::defMainWndWidth = int(0.7 * defScreenWidth);
int MyWnds::defMainWndHeight = int(0.7 * defScreenHeight);
HDC MyWnds::hDC;
LOGFONT MyWnds::defLogFont;
HFONT MyWnds::defHFont;
HBRUSH MyWnds::defHBrush = CreateSolidBrush(RGB(133, 193, 233));//����Ĭ�ϻ�ˢ
BYTE MyWnds::mainWndStyle = LoginUI;
BYTE MyWnds::mainWndFlag = LoginUI;

HWND MyWnds::MainWndProc_hwnd;
UINT MyWnds::MainWndProc_uMsg;
WPARAM MyWnds::MainWndProc_wParam;
LPARAM MyWnds::MainWndProc_lParam;

//�������ڹ���---������
LRESULT CALLBACK MyWnds::MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	MainWndProc_hwnd = hwnd;
	MainWndProc_uMsg = uMsg;
	MainWndProc_wParam = wParam;
	MainWndProc_lParam = lParam;
	switch (uMsg){
	case WM_COMMAND:
		MainWndProc_WM_COMMAND();
		break;
	case WM_WINDOWPOSCHANGING://׼�����Ĵ��ڴ�С
		MainWndProc_WM_WINDOWPOSCHANGING();
		break;
	case WM_WINDOWPOSCHANGED://���ڴ�С��ɸ���
		MainWndProc_WM_WINDOWPOSCHANGED();
		break;
	case WM_CLOSE://�رմ���
		MainWndProc_WM_CLOSE();
		break;
	case WM_DESTROY://���ٴ���
		MainWndProc_WM_DESTROY();
		break;
	case WM_CTLCOLORSTATIC://����static��edit(ES_READONLY)�ؼ�
		return MainWndProc_WM_CTLCOLORSTATIC();
	case WM_PAINT://���ƴ��ڸ�������
		MainWndProc_WM_PAINT();
		break;
	case WM_CREATE://��������
		{
		//����Ĭ������
		hDC = GetDC(hwnd);
		defLogFont.lfHeight = MulDiv(13, GetDeviceCaps(hDC, LOGPIXELSY), 72);//13���ֺŴ�С
		ReleaseDC(hwnd, hDC);
		hDC = NULL;
		//defLogFont.lfHeight = -20;
		defLogFont.lfWidth = 0;//�������ַ���ƽ����ȣ����߼���λΪ��λ��
		defLogFont.lfEscapement = 0;//ת���������豸�� x ��֮��ĽǶȣ���ʮ��֮һ��Ϊ��λ��
		defLogFont.lfOrientation = 0;//ÿ���ַ��Ļ��ߺ��豸 x ��֮��ĽǶȣ���ʮ��֮һ��Ϊ��λ��
		defLogFont.lfWeight = 550;//����Ĵ�ϸ
		defLogFont.lfItalic = FALSE;//б��
		defLogFont.lfUnderline = FALSE;//�»���
		defLogFont.lfStrikeOut = FALSE;//ɾ����
		defLogFont.lfCharSet = GB2312_CHARSET;//�ַ���
		defLogFont.lfOutPrecision = OUT_DEFAULT_PRECIS;//�������
		defLogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;//���þ���
		defLogFont.lfQuality = ANTIALIASED_QUALITY;//�������
		defLogFont.lfPitchAndFamily = VARIABLE_PITCH | FF_DONTCARE;//����ļ���ϵ��
		_stprintf_s(defLogFont.lfFaceName, _T("����"));//��������
		defHFont = CreateFontIndirect(&defLogFont);
		//������¼��ť
		CreateWindowEx(
			0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(loginConfirmButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, loginConfirmButtonID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//����ע�ᰴť
		CreateWindowEx(
			0, WC_BUTTON, _T("û���˺ţ����ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(registerButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, registerButtonID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//�����û��������
		CreateWindowEx(
			0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			int(0.28 * defMainWndWidth), int(0.31 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(userNameStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, userNameStaticID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			int(0.33 * defMainWndWidth), int(0.3 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(userNameEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		Edit_SetCueBannerText(GetDlgItem(MainWndProc_hwnd, userNameEditID), _T("�������û���"));//���ñ༭�ؼ��е��ı���ʾ
		Edit_LimitText(GetDlgItem(MainWndProc_hwnd, userNameEditID), actUserName - 1); //���ƿ��ڱ༭�ؼ���������û����ĳ���
		SendMessage(GetDlgItem(hwnd, userNameEditID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//�������������
		CreateWindowEx(
			0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
			int(0.285 * defMainWndWidth), int(0.41 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(passwdStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, passwdStaticID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""), WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_PASSWORD,
			int(0.33 * defMainWndWidth), int(0.4 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(passwdEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		Edit_SetCueBannerText(GetDlgItem(MainWndProc_hwnd, passwdEditID), _T("����������"));//���ñ༭�ؼ��е��ı���ʾ
		Edit_LimitText(GetDlgItem(MainWndProc_hwnd,passwdEditID),actPasswd-1); //���ƿ��ڱ༭�ؼ������������ĳ���
		SendMessage(GetDlgItem(hwnd, passwdEditID), WM_SETFONT, (WPARAM)defHFont, TRUE);
	}
	break;
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void MyWnds::MainWndProc_WM_COMMAND() {
	WORD tempHIWORD = HIWORD(MainWndProc_wParam);
	if (tempHIWORD == BN_CLICKED) {
		switch (LOWORD(MainWndProc_wParam)) {
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
	WINDOWPOS* temp = (WINDOWPOS*)MainWndProc_lParam;
	if (temp->cx < 960) {
		temp->cx = 960;
	}//����µĴ��ڿ��С��960�����أ����趨Ϊ960
	if (temp->cy < 540) {
		temp->cy = 540;
	}//����µĴ��ڸ߶�С��540�����أ����趨Ϊ540
}

void MyWnds::MainWndProc_WM_WINDOWPOSCHANGED(){
	WINDOWPOS* temp = (WINDOWPOS*)MainWndProc_lParam;//�趨��ʱָ����ո�����Ϣ
	defMainWndWidth = temp->cx;//��ȡ�����µĿ��
	defMainWndHeight = temp->cy;//��ȡ�����µĸ߶�
	//�������ؼ���С��ʹ���������ڴ�С����Ӧ
	switch (mainWndFlag)
	{
	case LoginUI: 
	{
		MoveWindow(GetDlgItem(MainWndProc_hwnd, loginConfirmButtonID), int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, registerButtonID), int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, userNameStaticID), int(0.28 * defMainWndWidth), int(0.31 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, userNameEditID), int(0.33 * defMainWndWidth), int(0.3 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, passwdStaticID), int(0.285 * defMainWndWidth), int(0.41 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, passwdEditID), int(0.33 * defMainWndWidth), int(0.4 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight), true);
	}
	break;
	case RegisterUI:
	{
		MoveWindow(GetDlgItem(MainWndProc_hwnd, loginButtonID), int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, registerConfirmButtonID), int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, actNameStaticID), int(0.285 * defMainWndWidth), int(0.21 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, actNameEditID), int(0.33 * defMainWndWidth), int(0.2 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, userNameStaticID), int(0.28 * defMainWndWidth), int(0.31 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, userNameEditID), int(0.33 * defMainWndWidth), int(0.3 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, passwdStaticID), int(0.285 * defMainWndWidth), int(0.41 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight), true);
		MoveWindow(GetDlgItem(MainWndProc_hwnd, passwdEditID), int(0.33 * defMainWndWidth), int(0.4 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight), true);
	}
	break;
	}
	
}
void MyWnds::MainWndProc_WM_CLOSE(){
	if (MessageBox(MainWndProc_hwnd, _T("�Ƿ�ȷ���˳�ϵͳ��"), _T("����԰����ϵͳ"), MB_OKCANCEL) == IDOK)
	{
		DeleteObject(defHBrush);//ɾ��Ĭ�ϻ�ˢ
		DeleteObject(defHFont);//ɾ��Ĭ������
		DestroyWindow(MainWndProc_hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ
	}
}
void MyWnds::MainWndProc_WM_DESTROY(){
	PostQuitMessage(0);//����WM_QUIT��Ϣ
}
LRESULT MyWnds::MainWndProc_WM_CTLCOLORSTATIC(){
	hDC = (HDC)MainWndProc_wParam;
	SetTextColor(hDC, RGB(0, 0, 0));//����ǰ��ɫ
	//SetBkColor(hDC, RGB(174, 214, 241));//���ֱ���ɫ
	SetBkMode(hDC, TRANSPARENT);
	hDC = NULL;
	return (INT_PTR)defHBrush;
}
void MyWnds::MainWndProc_WM_PAINT(){
	switch (mainWndStyle) {
	case LoginUI: case RegisterUI:
	{
		//������ʱ��ˢ
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//ʵ������ͼ��Ϣ�ṹ�����
		PAINTSTRUCT ps;
		//��ȡ�����ڵ���ʾ�豸�Ļ������
		hDC = BeginPaint(MainWndProc_hwnd, &ps);
		//���Ƹ�������
		//FillRect(hDC, &ps.rcPaint, defHBrush);
		//������������
		RECT center = { int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight), int(0.85 * defMainWndWidth), int(0.8 * defMainWndHeight) };
		FillRect(hDC, &center, tempBrush);
		//ɾ����ʱ��ˢ
		DeleteObject(tempBrush);
		//�ͷ������ڵ���ʾ�豸�Ļ������
		EndPaint(MainWndProc_hwnd, &ps);
		hDC = NULL;
	}
	 break;
	case HomeUI:
	{
		//������ʱ��ˢ
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//ʵ������ͼ��Ϣ�ṹ�����
		PAINTSTRUCT ps;
		//��ȡ�����ڵ���ʾ�豸�Ļ������
		hDC = BeginPaint(MainWndProc_hwnd, &ps);
		//���Ƹ�������
		//FillRect(hDC, &ps.rcPaint, defHBrush);
		//������������
		//RECT center = { int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight), int(0.85 * defMainWndWidth), int(0.8 * defMainWndHeight) };
		//FillRect(hDC, &center, tempBrush);
		//ɾ����ʱ��ˢ
		DeleteObject(tempBrush);
		//�ͷ������ڵ���ʾ�豸�Ļ������
		EndPaint(MainWndProc_hwnd, &ps);
		hDC = NULL;
	}
	break;
	}
}


WPARAM MyWnds::MainWnd() {
	//ʵ�������������---������
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
	mainWndClass.lpfnWndProc = MainWndProc;//���ڹ���
	mainWndClass.hInstance = hInstance;//����ʵ��
	mainWndClass.hbrBackground = defHBrush;//�౳����ˢ
	mainWndClass.lpszClassName = _T("mainWndClassName");//��������
	mainWndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
	//ע�ᴰ����---������
	if (!RegisterClassEx(&mainWndClass)) {
		MessageBox(NULL, _T("ע�ᴰ����---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//��������---������
	HWND mainHwnd = CreateWindowEx(
		0,_T("mainWndClassName"),_T("����԰����ϵͳ"),WS_TILEDWINDOW,
		int(0.15*defScreenWidth),int( 0.15*defScreenHeight), defMainWndWidth, defMainWndHeight,
		NULL,NULL,hInstance,NULL
	);
	if (!mainHwnd) {
		MessageBox(NULL, _T("��������---�����ڣ�ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
		exit(-1);
	}
	//��ʾ����---������
	ShowWindow(mainHwnd, SW_SHOW);
	//������Ϣѭ��
	MSG Msg = { 0 };
	BOOL bRet = 1;
	while (bRet = (GetMessage(&Msg, NULL, 0, 0)) != 0) {
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
	return Msg.wParam;
}