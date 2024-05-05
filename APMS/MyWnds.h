#pragma once
#include"general.h"
#include"Door.h"

//������ʹ��Win XP����ʽ�ؼ����
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//�Ӵ��ڱ�ʶ��
#define homePageWnd 1//��ҳ
#define actInfoWnd 2//�û���Ϣ
#define devInfoWnd 3//�豸��Ϣ
#define tradeInfoWnd 4//���׼�¼����ҪȨ�ޣ�
//��ť
#define loginButtonID 101//��¼
#define loginConfirmButtonID 102//ȷ�ϵ�¼
#define registerButtonID 103//ע��
#define registerConfirmButtonID 104//ȷ��ע��
#define logoutButtonID 105//�ǳ�
//�༭��
#define userNameEditID 201//�û���
#define passwdEditID 202//����
#define actNameEditID 203//�û��ǳ�
//��̬�ı�
#define userNameStaticID 301//�û���
#define passwdStaticID 302//����
#define actNameStaticID 303//�ǳ�

//UI����
#define LoginUI 1
#define RegisterUI 2
#define HomeUI 3

//����
#define defSmallFont 1
#define defMidFont 2
#define defLargeFont 3

class MyWnds {
public:
	//����Ӧ�ó���ĵ�ǰʵ���ľ��
	static _In_ HINSTANCE hInstance;
	//��Ļ�����
	static int defScreenWidth;
	//��Ļ���߶�
	static int defScreenHeight;
	//������Ĭ�Ͽ��
	static int defMainWndWidth;
	//������Ĭ�ϸ߶�
	static int defMainWndHeight;
	//����豸�������
	static HDC hDC;
	//Ĭ�ϻ�ˢ
	static HBRUSH defHBrush;

	//����
	static LOGFONT defLogFont;
	static HFONT defSmallHFont;
	static HFONT defMidHFont;
	static HFONT defLargeHFont;
	static HFONT currentHFONT;
	static BYTE fontFlag;

	//��Ϊ���ڷ��ı��
	static BYTE mainWndStyle;
	//��Ϊ���ڽ���ı��
	static BYTE mainWndFlag;

	//�����ڹ��̵Ĳ���
	static HWND MainWndProc_hwnd;
	static UINT MainWndProc_uMsg;
	static WPARAM MainWndProc_wParam;
	static LPARAM MainWndProc_lParam;

	//��ҳ���̵Ĳ���
	static HWND HomePageProc_hwnd;
	static UINT HomePageProc_uMsg;
	static WPARAM HomePageProc_wParam;
	static LPARAM HomePageProc_lParam;

	//��������
	static void CreateFont();

	//������
	static LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void MainWndProc_WM_COMMAND();
	static void MainWndProc_WM_WINDOWPOSCHANGING();
	static void MainWndProc_WM_WINDOWPOSCHANGED();
	static void MainWndProc_WM_CLOSE();
	static void MainWndProc_WM_DESTROY();
	static LRESULT MainWndProc_WM_CTLCOLORSTATIC();
	static void MainWndProc_WM_PAINT();
	static WPARAM MainWnd();

	//��ҳ
	static LRESULT CALLBACK HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void HomePageProc_WM_COMMAND();
	static void HomePageProc_WM_WINDOWPOSCHANGING();
	static void HomePageProc_WM_WINDOWPOSCHANGED();
	static void HomePageProc_WM_CLOSE();
	static void HomePageProc_WM_DESTROY();
	static LRESULT HomePageProc_WM_CTLCOLORSTATIC();
	static void HomePageProc_WM_PAINT();
	static void HomePage();
};