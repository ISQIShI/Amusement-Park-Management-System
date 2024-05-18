#pragma once
#include"Time.h"
#include <wtypes.h>

class Device {
public:
	//�豸����
	TCHAR mName[devName];
	//�豸ID
	TCHAR mID[devID];
	//�豸����
	TCHAR mIntro[devIntro];
	//�豸�۸�
	UINT mPrice;
	//�豸�շ�
	UINT mCharge;
	//¼���豸��ʱ��
	Time mAddTime;
public:
	//�豸���ܸ���
	static UINT mCount;

	//�豸��Ϣ�Ĳ���
	static HWND DevInfoProc_hwnd;
	static UINT DevInfoProc_uMsg;
	static WPARAM DevInfoProc_wParam;
	static LPARAM DevInfoProc_lParam;

	//��ǰ���ڲ鿴���豸
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
