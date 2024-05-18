#pragma once
#include"Time.h"
#include <wtypes.h>

class Trade {
public:
	//交易ID
	TCHAR mID[tradeID];
	//交易金额
	UINT mMoney;
	//进行交易的用户名
	TCHAR mUserName[actUserName];
	//获取收入的设备ID
	TCHAR mDevID[devID];
	//交易时间
	Time mTime;

	//交易记录总个数
	static UINT mCount;
	
	//交易记录的参数
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
