#pragma once
#include"Time.h"
#include <wtypes.h>

class Device {
public:
	//设备名称
	TCHAR mName[devName];
	//设备ID
	TCHAR mID[devID];
	//设备介绍
	TCHAR mIntro[devIntro];
	//设备价格
	UINT mPrice;
	//设备收费
	UINT mCharge;
	//录入设备的时间
	Time mAddTime;
public:
	//设备的总个数
	static UINT mCount;

	//设备信息的参数
	static HWND DevInfoProc_hwnd;
	static UINT DevInfoProc_uMsg;
	static WPARAM DevInfoProc_wParam;
	static LPARAM DevInfoProc_lParam;

	//当前正在查看的设备
	static Device currentDev;

	static BYTE devInfoFlag;
	static LRESULT CALLBACK DevInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void DevInfoProc_WM_NOTIFY();
	static void DevInfoProc_WM_PAINT();
	static void DevInfoProc_WM_CREATE();

	static void DevInfo();

};

extern bool ListCompareFlag;
extern HWND ListCompareHandle;
extern int CALLBACK ListCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
