#include"MyWnds.h"


//�������ڹ���---���˵�
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
	case WM_WINDOWPOSCHANGED://���Ĵ��ڴ�С
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
	case WM_CLOSE://�رմ���
		if (MessageBox(hwnd, _T("�Ƿ�ȷ���˳�ϵͳ��"), _T("����԰����ϵͳ"), MB_OKCANCEL) == IDOK)
		{
			DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY://���ٴ���
		PostQuitMessage(0);
		break;
	case WM_PAINT://�ػ洰��
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CREATE://��������
	{
		//������¼��ť
		CreateWindowEx(
			0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15   * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(loginButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		//����ע�ᰴť
		CreateWindowEx(
			0, WC_BUTTON, _T("ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(registerButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		//�����û��������
		CreateWindowEx(
			0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE| SS_SIMPLE,
			int(0.28 * defMainWndWidth), int(0.31 * defMainWndHeight), int(0.05 * defMainWndWidth), int(0.03 * defMainWndHeight),
			hwnd, HMENU(userNameStaticID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		CreateWindowEx(
			WS_EX_CLIENTEDGE, WC_EDIT, _T(""),  WS_CHILD  | WS_VISIBLE | ES_AUTOHSCROLL,
			int(0.33 * defMainWndWidth), int(0.3 * defMainWndHeight), int(0.31 * defMainWndWidth), int(0.05 * defMainWndHeight),
			hwnd, HMENU(userNameEditID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		//�������������
		CreateWindowEx(
			0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	//ʵ�������������---������
	WNDCLASSEX mainWndClass = { 0 };
	mainWndClass.cbSize = sizeof(WNDCLASSEX);
	mainWndClass.lpfnWndProc = MainWndProc;
	mainWndClass.hInstance = hInstance;
	mainWndClass.lpszClassName = _T("mainWndClassName");
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