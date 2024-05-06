#pragma once
#include"general.h"
#include"Door.h"
#include"Account.h"
#include"Device.h"
#include"Trade.h"
#include"Recharge.h"
#include"Notification.h"
//������ʹ��Win XP����ʽ�ؼ����
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//�Ӵ��ڱ�ʶ��
#define homePageWndID 1//��ҳ
#define actInfoWndID 2//�û���Ϣ
#define devInfoWndID 3//�豸��Ϣ
#define tradeInfoWndID 4//���׼�¼����ҪȨ�ޣ�

//��ť
#define loginButtonID 101//��¼
#define loginConfirmButtonID 102//ȷ�ϵ�¼
#define registerButtonID 103//ע��
#define registerConfirmButtonID 104//ȷ��ע��
#define homePageButtonID 105//��ҳ��ť
#define actInfoButtonID 106//�û���Ϣ��ť
#define devInfoButtonID 107//�豸��Ϣ��ť
#define tradeInfoButtonID 108//���׼�¼��ť����ҪȨ�ޣ�
#define exitButtonID 109//�˳�ϵͳ
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
#define ActInfoUI 4
#define DevInfoUI 5
#define TradeInfoUI 6

//����
#define defSmallFont 1
#define defMidFont 2
#define defLargeFont 3

//���ؼ�����
#define homePageButtonCoord_X 0.05
#define homePageButtonCoord_Y 0.125
#define homePageButtonWidth 0.1
#define homePageButtonHeight 0.1

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
	//��ǰ�û�����Ȩ��
	static BYTE currentPer;

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

	//�û���Ϣ�Ĳ���
	static HWND ActInfoProc_hwnd;
	static UINT ActInfoProc_uMsg;
	static WPARAM ActInfoProc_wParam;
	static LPARAM ActInfoProc_lParam;

	//�豸��Ϣ�Ĳ���
	static HWND DevInfoProc_hwnd;
	static UINT DevInfoProc_uMsg;
	static WPARAM DevInfoProc_wParam;
	static LPARAM DevInfoProc_lParam;

	//���׼�¼�Ĳ���
	static HWND TradeInfoProc_hwnd;
	static UINT TradeInfoProc_uMsg;
	static WPARAM TradeInfoProc_wParam;
	static LPARAM TradeInfoProc_lParam;

	//��ȡ�����ݵĸ���
	static void GetInfoCount();
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

	//�û���Ϣ
	static LRESULT CALLBACK ActInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void ActInfo();

	//�豸��Ϣ
	static LRESULT CALLBACK DevInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void DevInfo();

	//���׼�¼
	static LRESULT CALLBACK TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void TradeInfo();

	//�ؼ�
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
};
