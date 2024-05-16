#include"Trade.h"
#include "MyWnds.h"

//初始化总个数为0
UINT Trade::mCount = 0;

HWND Trade::TradeInfoProc_hwnd;
UINT Trade::TradeInfoProc_uMsg;
WPARAM Trade::TradeInfoProc_wParam;
LPARAM Trade::TradeInfoProc_lParam;

//交易记录
LRESULT CALLBACK Trade::TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Trade::TradeInfoProc_hwnd = hwnd;
	Trade::TradeInfoProc_uMsg = uMsg;
	Trade::TradeInfoProc_wParam = wParam;
	Trade::TradeInfoProc_lParam = lParam;
	switch (uMsg)
	{
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void Trade::TradeInfo() {
	//创建窗口---交易记录
	HWND tradeInfoHwnd = CreateWindowEx(
		0, _T("tradeInfoClassName"), _T("交易记录"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
	);
	if (!tradeInfoHwnd) {
		//实例化窗口类对象---交易记录
		WNDCLASSEX tradeInfoClass = { 0 };
		tradeInfoClass.cbSize = sizeof(WNDCLASSEX);
		tradeInfoClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		tradeInfoClass.lpfnWndProc = Trade::TradeInfoProc;//窗口过程
		tradeInfoClass.hInstance = MyWnds::hInstance;//程序实例
		tradeInfoClass.hbrBackground = HBRUSH(6);//类背景画刷
		tradeInfoClass.lpszClassName = _T("tradeInfoClassName");//窗口类名
		tradeInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---交易记录
		if (!RegisterClassEx(&tradeInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---交易记录，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//创建窗口---交易记录
		tradeInfoHwnd = CreateWindowEx(
			0, _T("tradeInfoClassName"), _T("交易记录"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
		);
		if (!tradeInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---交易记录，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}
