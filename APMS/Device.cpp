#include"Device.h"
#include "MyWnds.h"
#include <CommCtrl.h>
#include "Data.hpp"
#include <windowsx.h>

//��ʼ���ܸ���Ϊ0
UINT Device::mCount = 0;

HWND Device::DevInfoProc_hwnd;
UINT Device::DevInfoProc_uMsg;
WPARAM Device::DevInfoProc_wParam;
LPARAM Device::DevInfoProc_lParam;

BYTE Device::devInfoFlag;

Device Device::currentDev = { 0 };

//�豸��Ϣ
LRESULT CALLBACK Device::DevInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Device::DevInfoProc_hwnd = hwnd;
	Device::DevInfoProc_uMsg = uMsg;
	Device::DevInfoProc_wParam = wParam;
	Device::DevInfoProc_lParam = lParam;
	switch (uMsg)
	{
	case WM_NOTIFY:
		Device::DevInfoProc_WM_NOTIFY();
		break;
	case WM_PAINT:
		Device::DevInfoProc_WM_PAINT();
		break;
	case WM_CREATE:
		Device::DevInfoProc_WM_CREATE();
		break;
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void Device::DevInfoProc_WM_NOTIFY() {
	switch (((LPNMHDR)Device::DevInfoProc_lParam)->code) 
	{
	case NM_CLICK:case NM_RETURN://����
	{
		switch (LPNMHDR(Device::DevInfoProc_lParam)->idFrom) {
		case devSaveSysLinkID:
		{
			TCHAR tempTCHAR[devIntro];
			Edit_GetText(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), tempTCHAR, devIntro);//��ȡ����
			if (*tempTCHAR) {
				//�޸��豸����
				_stprintf_s(Device::currentDev.mIntro, tempTCHAR);
				Data<Device>::DataModify(_T("Device.dat"), Device::currentDev);
				//���ٿؼ�
				DestroyWindow(GetDlgItem(Device::DevInfoProc_hwnd, devSaveSysLinkID));
				Edit_SetReadOnly(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), TRUE);//����ֻ��״̬
				//��ʾ���༭���ؼ�
				SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), SW_SHOW);
				//�ػ���������
				InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
				SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);
			}
			else {
				MessageBox(Device::DevInfoProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
			}
			break;
		}
		case editDevIntroSysLinkID:
		{
			//���ء��༭���ؼ�
			ShowWindow(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), SW_HIDE);
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Device::DevInfoProc_hwnd, HMENU(devSaveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, devSaveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

			Edit_SetReadOnly(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), FALSE);//����ֻ��״̬

			//�ػ���������
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);

			break;
		}
		case returnSysLinkID:
		{
			//���ٿؼ�
			MyWnds::DestroyControl(Device::DevInfoProc_hwnd, { returnSysLinkID, devIntroEditID , editDevIntroSysLinkID ,devSaveSysLinkID});
			//�����ؼ�
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), WM_CREATE, NULL, NULL);
			//���±��
			Device::devInfoFlag = 0;
			//�ػ���������
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case dataInfoListID:
		{
			//���µ�����б�����
			MyWnds::x_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iItem;
			break;
		}
		case dataInfoSysLinkID:
		{
			if (PNMLINK(Device::DevInfoProc_lParam)->item.iLink == 0)//����
			{
				MyWnds::dialogFlag = dialogDevAdd;
				MyWnds::Dialog();

			}
			else if (PNMLINK(Device::DevInfoProc_lParam)->item.iLink == 1)//�޸�
			{
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID))) {
					MessageBox(Device::DevInfoProc_hwnd, _T("��ѡ��Ҫ�޸ĵ��豸"), _T("��ʾ"), MB_ICONINFORMATION);
				}
				else {
					MyWnds::dialogFlag = dialogDevModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(Device::DevInfoProc_lParam)->item.iLink == 2)//ɾ��
			{
				TCHAR tempTCHAR[21] = {};
				if (MessageBox(Device::DevInfoProc_hwnd, _T("ȷ��Ҫɾ����Щ�豸��"), _T("��ʾ"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y = ListView_GetItemCount(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID)) - 1; y >= 0; --y) {
						if (ListView_GetCheckState(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), y)) {
							ListView_GetItemText(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), y, 2, tempTCHAR, devID * 2);
							Data<Device>::DataDelete(_T("Device.dat"), tempTCHAR);
						}
					}
				}
			}
			//׼��ˢ���б�����
			//ɾ��������
			ListView_DeleteAllItems(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID));
			//������
			Device tempDev;//��Ž�Ҫ��ȡ���豸����
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x + 1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempDev.mName;
				ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempDev.mID;
				ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempDev.mPrice);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempDev.mCharge);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempDev.mAddTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempDev.mAddTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);
			}
			CloseHandle(tempHANDLE);//�ر��ļ�
			//�ػ���������
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}

		}
		break;
	}

	case NM_DBLCLK://˫��
	{
		switch (LPNMHDR(Device::DevInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{
			//���µ�ǰ�鿴���豸
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			//��ȡ���λ�õ��豸��Ϣ
			HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			//�ļ�ָ���ƶ������豸����֮ǰ
			LARGE_INTEGER tempL_I;
			tempL_I.QuadPart = (long long)(sizeof(Device)) * MyWnds::y_Listview;
			SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
			ReadFile(tempHANDLE, &Device::currentDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
			CloseHandle(tempHANDLE);//�ر��ļ�

			//���±��
			Device::devInfoFlag = 1;
			//���µ�����б�����
			MyWnds::x_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iItem;
			//���ٿؼ�
			MyWnds::DestroyControl(Device::DevInfoProc_hwnd, { dataInfoListID,dataInfoSysLinkID });
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Device::DevInfoProc_hwnd, HMENU(returnSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, returnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�༭��--����
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, Device::currentDev.mIntro, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN |ES_READONLY,
				int(0.1 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.65 * MyWnds::homePageWidth), int(0.5 * MyWnds::homePageHeight),
				Device::DevInfoProc_hwnd, HMENU(devIntroEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), _T("�������豸����"));//���ñ༭�ؼ��е��ı���ʾ
			Edit_LimitText(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), devIntro - 1); //���ƿ��ڱ༭�ؼ�������Ľ��ܵĳ���
			SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			if (MyWnds::currentAct.mPer.mAdmin) {
				//�༭��������
				CreateWindowEx(
					0, _T("SysLink"), _T("<A HREF=\"�༭\">�༭</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
					int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
					Device::DevInfoProc_hwnd, HMENU(editDevIntroSysLinkID), MyWnds::hInstance, NULL
				);
				SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			}
			//�ػ���������
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);

		}
		break;
		}
		break;
	}

	case NM_RCLICK://�һ�
	{
		switch (LPNMHDR(Device::DevInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{

		}
		break;
		}
		break;
	}



	}
}

void Device::DevInfoProc_WM_PAINT() {
	TCHAR tempTCHAR[211];
	PAINTSTRUCT ps;
	MyWnds::hDC = BeginPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), &ps);
	//�趨����
	SelectObject(MyWnds::hDC, MyWnds::currentHFONT);
	if (devInfoFlag == 1) {
		_stprintf_s(tempTCHAR, _T("�豸���ƣ�%s"), Device::currentDev.mName);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�豸ID��%s"), Device::currentDev.mID);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.2 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�۸�%d"), Device::currentDev.mPrice);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.25 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�շѣ�%d"), Device::currentDev.mCharge);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.3 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�豸¼��ʱ�䣺%s %s"), Device::currentDev.mAddTime.mDate, Device::currentDev.mAddTime.mMoment);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.35 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("���ܣ�"));
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
	}
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), &ps);
	MyWnds::hDC = NULL;
}

void Device::DevInfoProc_WM_CREATE() {
	//��ǳ�ʼ��
	Device::devInfoFlag = 0;
	//�б������ʼ��
	MyWnds::x_Listview = -1;
	MyWnds::y_Listview = 0;
	//�����豸��Ϣ
	if (MyWnds::currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"���\">���</A>")\
			_T(" <A HREF=\"�޸�\">�޸�</A>")\
			_T(" <A HREF=\"ɾ��\">ɾ��</A>"),
			WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
			int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			Device::DevInfoProc_hwnd, HMENU(dataInfoSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
	//�豸��Ϣ�б�
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
		Device::DevInfoProc_hwnd, (HMENU)dataInfoListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//������
	LVCOLUMN temp = { 0 };
	temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM;
	temp.fmt = LVCFMT_CENTER;
	temp.cx = int(0.07 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("���");
	temp.iSubItem = 0;
	temp.cxMin = int(0.07 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 0, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("�豸����");
	temp.iSubItem = 1;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 1, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("�豸ID");
	temp.iSubItem = 2;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 2, &temp);

	temp.cx = int(0.12 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("�۸�");
	temp.iSubItem = 3;
	temp.cxMin = int(0.12 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 3, &temp);

	temp.cx = int(0.11 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("�շ�");
	temp.iSubItem = 4;
	temp.cxMin = int(0.11 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 4, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("¼��ʱ��");
	temp.iSubItem = 5;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 5, &temp);
	//������
	Device tempDev;//��Ž�Ҫ��ȡ���豸����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	TCHAR tempTCHAR[30];
	LVITEM tempINSERT = { 0 };
	HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//��ȡ�ļ�
		if (!tempDWORD)break;
		tempINSERT.mask = LVIF_TEXT;
		tempINSERT.iItem = x;
		tempINSERT.iSubItem = 0;
		_stprintf_s(tempTCHAR, _T("%d"), x + 1);
		tempINSERT.pszText = tempTCHAR;
		ListView_InsertItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		tempINSERT.pszText = tempDev.mName;
		ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		tempINSERT.pszText = tempDev.mID;
		ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		_stprintf_s(tempTCHAR, _T("%d"), tempDev.mPrice);
		tempINSERT.pszText = tempTCHAR;
		ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		_stprintf_s(tempTCHAR, _T("%d"), tempDev.mCharge);
		tempINSERT.pszText = tempTCHAR;
		ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);

		++tempINSERT.iSubItem;
		_stprintf_s(tempTCHAR, tempDev.mAddTime.mDate);
		wcscat_s(tempTCHAR, _T(" "));
		wcscat_s(tempTCHAR, tempDev.mAddTime.mMoment);
		tempINSERT.pszText = tempTCHAR;
		ListView_SetItem(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), &tempINSERT);
	}
	CloseHandle(tempHANDLE);//�ر��ļ�

	//�ػ���������
	InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
	SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);

}



void Device::DevInfo() {
	//��������---�豸��Ϣ
	HWND devInfoHwnd = CreateWindowEx(
		0, _T("devInfoClassName"), _T("�豸��Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
	);
	if (!devInfoHwnd) {
		//ʵ�������������---�豸��Ϣ
		WNDCLASSEX devInfoClass = { 0 };
		devInfoClass.cbSize = sizeof(WNDCLASSEX);
		devInfoClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		devInfoClass.lpfnWndProc = Device::DevInfoProc;//���ڹ���
		devInfoClass.hInstance = MyWnds::hInstance;//����ʵ��
		devInfoClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		devInfoClass.lpszClassName = _T("devInfoClassName");//��������
		devInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---�豸��Ϣ
		if (!RegisterClassEx(&devInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---�豸��Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//��������---�豸��Ϣ
		devInfoHwnd = CreateWindowEx(
			0, _T("devInfoClassName"), _T("�豸��Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
		);
		if (!devInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---�豸��Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}
