#include"Trade.h"
#include "MyWnds.h"

//��ʼ���ܸ���Ϊ0
UINT Trade::mCount = 0;

HWND Trade::TradeInfoProc_hwnd;
UINT Trade::TradeInfoProc_uMsg;
WPARAM Trade::TradeInfoProc_wParam;
LPARAM Trade::TradeInfoProc_lParam;

//���׼�¼
LRESULT CALLBACK Trade::TradeInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Trade::TradeInfoProc_hwnd = hwnd;
	Trade::TradeInfoProc_uMsg = uMsg;
	Trade::TradeInfoProc_wParam = wParam;
	Trade::TradeInfoProc_lParam = lParam;
	switch (uMsg)
	{
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void Trade::TradeInfo() {
	//��������---���׼�¼
	HWND tradeInfoHwnd = CreateWindowEx(
		0, _T("tradeInfoClassName"), _T("���׼�¼"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
	);
	if (!tradeInfoHwnd) {
		//ʵ�������������---���׼�¼
		WNDCLASSEX tradeInfoClass = { 0 };
		tradeInfoClass.cbSize = sizeof(WNDCLASSEX);
		tradeInfoClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		tradeInfoClass.lpfnWndProc = Trade::TradeInfoProc;//���ڹ���
		tradeInfoClass.hInstance = MyWnds::hInstance;//����ʵ��
		tradeInfoClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		tradeInfoClass.lpszClassName = _T("tradeInfoClassName");//��������
		tradeInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---���׼�¼
		if (!RegisterClassEx(&tradeInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---���׼�¼��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//��������---���׼�¼
		tradeInfoHwnd = CreateWindowEx(
			0, _T("tradeInfoClassName"), _T("���׼�¼"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
		);
		if (!tradeInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---���׼�¼��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}
