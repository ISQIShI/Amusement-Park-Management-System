#pragma once
#include"Time.h"
#include <wtypes.h>

class Trade {
public:
	//����ID
	TCHAR mID[tradeID];
	//���׽��
	UINT mMoney;
	//���н��׵��û���
	TCHAR mUserName[actUserName];
	//��ȡ������豸ID
	TCHAR mDevID[devID];
	//����ʱ��
	Time mTime;

	//���׼�¼�ܸ���
	static UINT mCount;
	
	//���׼�¼�Ĳ���
	static HWND TradeInfoProc_hwnd;
	static UINT TradeInfoProc_uMsg;
	static WPARAM TradeInfoProc_wParam;
	static LPARAM TradeInfoProc_lParam;

	static LRESULT CALLBACK TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void TradeInfoProc_WM_CREATE();
	static void TradeInfoProc_WM_PAINT();
	static void TradeInfoProc_WM_NOTIFY();
	static void TradeInfo();

};

extern bool ListCompareFlag;
extern HWND ListCompareHandle;
extern int CALLBACK ListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
