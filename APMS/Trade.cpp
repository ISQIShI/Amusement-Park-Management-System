#include"Trade.h"
#include "MyWnds.h"
#include <CommCtrl.h>
#include "Data.hpp"

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
	case WM_NOTIFY:
		Trade::TradeInfoProc_WM_NOTIFY();
		break;
	case WM_PAINT:
		Trade::TradeInfoProc_WM_PAINT();
		break;
	case WM_CREATE:
		Trade::TradeInfoProc_WM_CREATE();
		break;
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void Trade::TradeInfoProc_WM_NOTIFY()
{
	switch (((LPNMHDR)Trade::TradeInfoProc_lParam)->code)
	{
	case NM_CLICK:case NM_RETURN://����
	{
		switch (LPNMHDR(Trade::TradeInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{
			//���µ�����б�����
			MyWnds::x_Listview = LPNMITEMACTIVATE(Trade::TradeInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Trade::TradeInfoProc_lParam)->iItem;
			break;
		}
		case dataInfoSysLinkID:
		{
			if (PNMLINK(Trade::TradeInfoProc_lParam)->item.iLink == 0)//����
			{
				MyWnds::dialogFlag = dialogTradeAdd;
				MyWnds::Dialog();
			}
			else if (PNMLINK(Trade::TradeInfoProc_lParam)->item.iLink == 1)//�޸�
			{
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID))) {
					MessageBox(Trade::TradeInfoProc_hwnd, _T("��ѡ��Ҫ�޸ĵĽ��׼�¼"), _T("��ʾ"), MB_ICONINFORMATION);
				}
				else {
					MyWnds::dialogFlag = dialogTradeModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(Trade::TradeInfoProc_lParam)->item.iLink == 2)//ɾ��
			{
				TCHAR tempTCHAR[21] = {};
				if (MessageBox(Trade::TradeInfoProc_hwnd, _T("ȷ��Ҫɾ����Щ���׼�¼��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y = ListView_GetItemCount(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID)) - 1; y >= 0; --y) {
						if (ListView_GetCheckState(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), y)) {
							//��ȡ����ID
							ListView_GetItemText(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), y, 1, tempTCHAR, tradeID );
							Data<Trade>::DataDelete(_T("Trade.dat"), tempTCHAR);
						}
					}
				}
			}
			//׼��ˢ���б�����
			//ɾ��������
			ListView_DeleteAllItems(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
			//������
			Trade tempTrade;//��Ž�Ҫ��ȡ���豸����
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Trade.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempTrade, sizeof(Trade), &tempDWORD, NULL);//��ȡ�ļ�
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x + 1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempTrade.mID;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempTrade.mMoney);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempTrade.mUserName;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempTrade.mDevID;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempTrade.mTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempTrade.mTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);
			}
			CloseHandle(tempHANDLE);//�ر��ļ�

			//�ػ���������
			InvalidateRect(Trade::TradeInfoProc_hwnd, NULL, TRUE);
			SendMessage(Trade::TradeInfoProc_hwnd, WM_PAINT, NULL, NULL);

			break;
		}
		case tradeSelectSysLinkID:
		{
			MyWnds::dialogFlag = dialogTradeSelect;
			MyWnds::Dialog();
			break;
		}
		case returnSysLinkID:
		{
			//���١����ء�
			DestroyWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, returnSysLinkID));
			ShowWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, tradeSelectSysLinkID), SW_SHOW);
			ShowWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoSysLinkID), SW_SHOW);
			//ɾ���б�
			DestroyWindow(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID));
			//�ؽ����׼�¼�б�
			CreateWindowEx(
				0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
				int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
				Trade::TradeInfoProc_hwnd, (HMENU)dataInfoListID, MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			ListView_SetExtendedListViewStyle(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			//������
			LVCOLUMN temp = { 0 };
			temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
			temp.fmt = LVCFMT_CENTER;
			temp.cx = int(0.07 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("���");
			temp.iSubItem = 0;
			temp.cxDefault = 1;
			temp.cxMin = int(0.07 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 0, &temp);

			temp.cx = int(0.17 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("����ID");
			temp.iSubItem = 1;
			temp.cxDefault = 0;
			temp.cxMin = int(0.17 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 1, &temp);

			temp.cx = int(0.12 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("���");
			temp.iSubItem = 2;
			temp.cxDefault = 1;
			temp.cxMin = int(0.12 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 2, &temp);

			temp.cx = int(0.17 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("�û���");
			temp.iSubItem = 3;
			temp.cxDefault = 0;
			temp.cxMin = int(0.17 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 3, &temp);

			temp.cx = int(0.17 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("�豸ID");
			temp.iSubItem = 4;
			temp.cxDefault = 0;
			temp.cxMin = int(0.17 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 4, &temp);

			temp.cx = int(0.2 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("����ʱ��");
			temp.iSubItem = 5;
			temp.cxDefault = 0;
			temp.cxMin = int(0.2 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 5, &temp);

			//������
			Trade tempTrade;//��Ž�Ҫ��ȡ�Ľ�������
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Trade.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempTrade, sizeof(Trade), &tempDWORD, NULL);//��ȡ�ļ�
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x + 1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempTrade.mID;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempTrade.mMoney);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempTrade.mUserName;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempTrade.mDevID;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempTrade.mTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempTrade.mTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);
			}
			CloseHandle(tempHANDLE);//�ر��ļ�

			//�ػ���������
			InvalidateRect(Trade::TradeInfoProc_hwnd, NULL, TRUE);
			SendMessage(Trade::TradeInfoProc_hwnd, WM_PAINT, NULL, NULL);


			break;
		}
		}


		break;
	}
	case NM_DBLCLK://˫��
	{
		switch (LPNMHDR(Trade::TradeInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{

			break;
		}

		}


		break;
	}
	case NM_RCLICK://�һ�
	{
		switch (LPNMHDR(Trade::TradeInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{

			break;
		}

		}

		break;
	}
	case LVN_COLUMNCLICK:
	{
		ListCompareHandle = Trade::TradeInfoProc_hwnd;
		ListView_SortItemsEx(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), ListCompareFunc, Trade::TradeInfoProc_lParam);
		if (ListCompareFlag)ListCompareFlag = 0;
		else ListCompareFlag = 1;
		break;
	}
	}
}


void Trade::TradeInfoProc_WM_PAINT()
{
	PAINTSTRUCT ps;
	MyWnds::hDC = BeginPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoWndID), &ps);
	//�趨����
	SelectObject(MyWnds::hDC, MyWnds::currentHFONT);
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, tradeInfoWndID), &ps);
	MyWnds::hDC = NULL;

}

void Trade::TradeInfoProc_WM_CREATE()
{
	//�б������ʼ��
	MyWnds::x_Listview = -1;
	MyWnds::y_Listview = 0;
	//���Ľ��׼�¼&���׼�¼ɸѡ(��ҪȨ��)
	if (MyWnds::currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"���\">���</A>")\
			_T(" <A HREF=\"�޸�\">�޸�</A>")\
			_T(" <A HREF=\"ɾ��\">ɾ��</A>"),
			WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
			int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			Trade::TradeInfoProc_hwnd, HMENU(dataInfoSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"ɸѡ\">ɸѡ</A>"),
			WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
			int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			Trade::TradeInfoProc_hwnd, HMENU(tradeSelectSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(Trade::TradeInfoProc_hwnd, tradeSelectSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
	//���׼�¼�б�
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
		Trade::TradeInfoProc_hwnd, (HMENU)dataInfoListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//������
	LVCOLUMN temp = { 0 };
	temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
	temp.fmt = LVCFMT_CENTER;
	temp.cx = int(0.07 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("���");
	temp.iSubItem = 0;
	temp.cxDefault = 1;
	temp.cxMin = int(0.07 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 0, &temp);

	temp.cx = int(0.17 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("����ID");
	temp.iSubItem = 1;
	temp.cxDefault = 0;
	temp.cxMin = int(0.17 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 1, &temp);

	temp.cx = int(0.12 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("���");
	temp.iSubItem = 2;
	temp.cxDefault = 1;
	temp.cxMin = int(0.12 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 2, &temp);

	temp.cx = int(0.17 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("�û���");
	temp.iSubItem = 3;
	temp.cxDefault = 0;
	temp.cxMin = int(0.17 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 3, &temp);

	temp.cx = int(0.17 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("�豸ID");
	temp.iSubItem = 4;
	temp.cxDefault = 0;
	temp.cxMin = int(0.17 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 4, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("����ʱ��");
	temp.iSubItem = 5;
	temp.cxDefault = 0;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), 5, &temp);

	//������
	Trade tempTrade;//��Ž�Ҫ��ȡ�Ľ�������
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempTCHAR[30];
	LVITEM tempINSERT = { 0 };
	HANDLE tempHANDLE = CreateFile(_T("Trade.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ) {
		ReadFile(tempHANDLE, &tempTrade, sizeof(Trade), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		//��ͨ�û�ֻ��ʾ�Լ������Ѽ�¼
		if (MyWnds::currentAct.mPer.mAdmin == 0 && _tcscmp(tempTrade.mUserName, MyWnds::currentAct.mID)) continue;
		tempINSERT.mask = LVIF_TEXT;
		tempINSERT.iItem = x;
		tempINSERT.iSubItem = 0;
		_stprintf_s(tempTCHAR, _T("%d"), x + 1);
		tempINSERT.pszText = tempTCHAR;
		ListView_InsertItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		tempINSERT.pszText = tempTrade.mID;
		ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		_stprintf_s(tempTCHAR, _T("%d"), tempTrade.mMoney);
		tempINSERT.pszText = tempTCHAR;
		ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		tempINSERT.pszText = tempTrade.mUserName;
		ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		tempINSERT.pszText = tempTrade.mDevID;
		ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		_stprintf_s(tempTCHAR, tempTrade.mTime.mDate);
		wcscat_s(tempTCHAR, _T(" "));
		wcscat_s(tempTCHAR, tempTrade.mTime.mMoment);
		tempINSERT.pszText = tempTCHAR;
		ListView_SetItem(GetDlgItem(Trade::TradeInfoProc_hwnd, dataInfoListID), &tempINSERT);
		++x;
	}
	CloseHandle(tempHANDLE);//�ر��ļ�

	//�ػ���������
	InvalidateRect(Trade::TradeInfoProc_hwnd, NULL, TRUE);
	SendMessage(Trade::TradeInfoProc_hwnd, WM_PAINT, NULL, NULL);

}


void Trade::TradeInfo() {
	//��������---���׼�¼
	HWND tradeInfoHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("tradeInfoClassName"), _T("���׼�¼"), WS_TILED | WS_CHILD | WS_VISIBLE,
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
			WS_EX_CONTROLPARENT, _T("tradeInfoClassName"), _T("���׼�¼"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(tradeInfoWndID), MyWnds::hInstance, NULL
		);
		if (!tradeInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---���׼�¼��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}
