#pragma once
#include"Permission.h"
#include"Time.h"
#include <wtypes.h>

class Account {
public:
	//用户昵称
	TCHAR mName[actName];
	//用户名
	TCHAR mID[actUserName];
	//用户密码
	TCHAR mPasswd[actPasswd];
	//用户权限
	Permission mPer;
	//用户余额
	UINT mCredit;
	//用户注册时间
	Time mRegTime;
	//用户总个数
	static UINT mCount;
public:
	//购票
	void BuyTicket();//仅留下接口，实际作为软件的话在通过机器刷卡时应调用此函数
	//充值
	void Recharge();//为实际使用留下接口
	//提现
	void Withdraw();//为实际使用留下接口

	//用户信息的参数
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

extern bool ListCompareFlag;
extern HWND ListCompareHandle;
extern int CALLBACK ListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

