#pragma once
#include"Permission.h"
#include"Time.h"
#include <wtypes.h>

class Account {
public:
	//�û��ǳ�
	TCHAR mName[actName];
	//�û���
	TCHAR mID[actUserName];
	//�û�����
	TCHAR mPasswd[actPasswd];
	//�û�Ȩ��
	Permission mPer;
	//�û����
	UINT mCredit;
	//�û�ע��ʱ��
	Time mRegTime;
	//�û��ܸ���
	static UINT mCount;
public:
	//��Ʊ
	void BuyTicket();
	//��ֵ
	void Recharge();
	//����
	void Withdraw();

	//�û���Ϣ�Ĳ���
	static HWND ActInfoProc_hwnd;
	static UINT ActInfoProc_uMsg;
	static WPARAM ActInfoProc_wParam;
	static LPARAM ActInfoProc_lParam;

	static BYTE actInfoSysLinkFlag;
	static LRESULT CALLBACK ActInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void ActInfoProc_WM_NOTIFY();
	static void ActInfoProc_WM_PAINT();
	static void ActInfoProc_WM_CREATE();
	static void ActInfo();

};

