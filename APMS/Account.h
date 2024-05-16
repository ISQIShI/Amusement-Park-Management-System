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
	void BuyTicket();
	//充值
	void Recharge();
	//提现
	void Withdraw();

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

