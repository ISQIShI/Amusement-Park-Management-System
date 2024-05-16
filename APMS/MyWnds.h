#pragma once
#include"general.h"
#include"Account.h"
#include<Windows.h>
#include<initializer_list>

//������ʹ��Win XP����ʽ�ؼ����
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

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

	static int homePageWidth;
	static int homePageHeight;

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
	static BYTE lastfontFlag;

	//��Ϊ���ڷ��ı��
	static BYTE mainWndStyle;
	//��Ϊ���ڽ���ı��
	static BYTE mainWndFlag;
	//��ǰ�û�
	static Account currentAct;

	//�Ի���ı��
	static BYTE dialogFlag;

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

	//�Ի���Ĳ���
	static HWND DialogProc_hwnd;
	static UINT DialogProc_uMsg;
	static WPARAM DialogProc_wParam;
	static LPARAM DialogProc_lParam;

	//Listview �������
	static SHORT x_Listview;//�б�
	static UINT y_Listview;//�б�

	//��ȡ�����ݵĸ���
	static void GetDataCount();
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

	//������һ�� mainWndFlag ���ٶ�Ӧ�Ӵ���
	static void DestroyChildWnd();

	//��ҳ
	static LRESULT CALLBACK HomePageProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//static void HomePageProc_WM_COMMAND();
	//static void HomePageProc_WM_WINDOWPOSCHANGING();
	//static void HomePageProc_WM_WINDOWPOSCHANGED();
	//static void HomePageProc_WM_CLOSE();
	//static void HomePageProc_WM_DESTROY();
	//static LRESULT HomePageProc_WM_CTLCOLORSTATIC();
	//static void HomePageProc_WM_PAINT();
	static void HomePage();

	//����ģ̬�Ի���
	static LRESULT CALLBACK DialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static WPARAM Dialog();
	static void DialogActAdd();
	static void DialogActModify();
	static void DialogDevAdd();
	static void DialogDevModify();

	//�����ӿؼ�
	static void createLoginButton();
	static void createLoginConfirmButton();
	static void createRegisterButton();
	static void createRegisterConfirmButton();
	static void createHomePageButton();
	static void createActInfoButton();
	static void createDevInfoButton();
	static void createTradeInfoButton();
	static void createExitButton();

	static void createUserNameEdit_Static();
	static void createPasswdEdit_Static();
	static void createActNameEdit_Static();

	//ö�������Ӵ��ڣ�����Ӧ��С�����壩
	static BOOL CALLBACK EnumChildProc_AdaptiveWnd(HWND hwndChild, LPARAM lParam);
	//�����������ٶ���ؼ�&�Ӵ���
	static void DestroyControl(HWND hWnd,const std::initializer_list<int>& controlID);
	//��������������ؼ�������ͬ��Ϣ (Ĭ��Ϊ�趨�������Ϣ)
	static void SendMessageToControl(HWND hWnd, const std::initializer_list<int>& controlID, UINT Msg = WM_SETFONT, WPARAM wParam = (WPARAM)MyWnds::currentHFONT, LPARAM lParam = TRUE);

};
