#include"MyWnds.h"

HDC hDC;
LOGFONT defLogFont;
HFONT defHFont;
HBRUSH defHBrush = CreateSolidBrush(RGB(133, 193, 233));//����Ĭ�ϻ�ˢ
UINT newMainWndWidth = defMainWndWidth, newMainWndHeight = defMainWndHeight;

//�������ڹ���---������
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg){
	case WM_WINDOWPOSCHANGING://׼�����Ĵ��ڴ�С
	{
		WINDOWPOS * temp = (WINDOWPOS *) lParam;
		if (temp->cx < 960 ) {
			temp->cx = 960;
		}//����µĴ��ڿ��С��960�����أ����趨Ϊ960
		if (temp->cy < 540) {
			temp->cy = 540;
		}//����µĴ��ڸ߶�С��540�����أ����趨Ϊ540
	}
	break;
	case WM_WINDOWPOSCHANGED://���ڴ�С��ɸ���
	{
		WINDOWPOS* temp = (WINDOWPOS*)lParam;//�趨��ʱָ����ո�����Ϣ
		newMainWndWidth = temp->cx;//��ȡ�����µĿ��
		newMainWndHeight = temp->cy;//��ȡ�����µĸ߶�
		//�������ؼ���С��ʹ���������ڴ�С����Ӧ
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
			DeleteObject(defHBrush);//ɾ��Ĭ�ϻ�ˢ
			DeleteObject(defHFont);//ɾ��Ĭ������
			DestroyWindow(hwnd);//���ٴ��ڲ�����WM_DESTROY��Ϣ
		}
		break;
	case WM_DESTROY://���ٴ���
		PostQuitMessage(0);//����WM_QUIT��Ϣ
		break;
	case WM_CTLCOLORSTATIC://����static��edit(ES_READONLY)�ؼ�
	{
		hDC = (HDC)wParam;
		SetTextColor(hDC, RGB(0, 0, 0));//����ǰ��ɫ
		//SetBkColor(hDC, RGB(174, 214, 241));//���ֱ���ɫ
		SetBkMode(hDC, TRANSPARENT);
		hDC = NULL;
		return (INT_PTR)defHBrush;
	}
	case WM_PAINT://���ƴ��ڸ�������
	{
		//������ʱ��ˢ
		HBRUSH tempBrush = CreateSolidBrush(RGB(174, 214, 241));
		//ʵ������ͼ��Ϣ�ṹ�����
		PAINTSTRUCT ps;
		//��ȡ�����ڵ���ʾ�豸�Ļ������
		hDC = BeginPaint(hwnd, &ps);
		//���Ƹ�������
		//FillRect(hDC, &ps.rcPaint, defHBrush);
		//������������
		RECT center = { int(0.15 * newMainWndWidth), int(0.15 * newMainWndHeight), int(0.85 * newMainWndWidth), int(0.8 * newMainWndHeight)};
		FillRect(hDC, &center, tempBrush);
		//ɾ����ʱ��ˢ
		DeleteObject(tempBrush);
		//�ͷ������ڵ���ʾ�豸�Ļ������
		EndPaint(hwnd, &ps);
		hDC = NULL;
	}
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
		_stprintf_s(defLogFont.lfFaceName,_T("����"));//��������
		defHFont = CreateFontIndirect(&defLogFont);
		//������¼��ť
		CreateWindowEx(
			0, WC_BUTTON, _T("��¼"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.27 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15   * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(loginButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, loginButtonID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//����ע�ᰴť
		CreateWindowEx(
			0, WC_BUTTON, _T("ע��"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			int(0.52 * defMainWndWidth), int(0.55 * defMainWndHeight), int(0.15 * defMainWndWidth), int(0.15 * defMainWndHeight),
			hwnd, HMENU(registerButtonID), ((LPCREATESTRUCT)lParam)->hInstance, NULL
		);
		SendMessage(GetDlgItem(hwnd, registerButtonID), WM_SETFONT, (WPARAM)defHFont, TRUE);
		//�����û��������
		CreateWindowEx(
			0, WC_STATIC, _T("�û���"), WS_CHILD | WS_VISIBLE| SS_SIMPLE,
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
		//�������������
		CreateWindowEx(
			0, WC_STATIC, _T("����"), WS_CHILD | WS_VISIBLE | SS_SIMPLE,
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
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
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