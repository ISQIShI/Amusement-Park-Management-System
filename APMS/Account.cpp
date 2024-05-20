#include"Account.h"
#include"MyWnds.h"
#include "Door.h"
#include"Data.hpp"
#include <CommCtrl.h>
#include <windowsx.h>


//��ʼ���ܸ���Ϊ0
UINT Account::mCount = 0;

HWND Account::ActInfoProc_hwnd;
UINT Account::ActInfoProc_uMsg;
WPARAM Account::ActInfoProc_wParam;
LPARAM Account::ActInfoProc_lParam;

BYTE Account::actInfoSysLinkFlag;

//�û���Ϣ
LRESULT CALLBACK Account::ActInfoProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Account::ActInfoProc_hwnd = hwnd;
	Account::ActInfoProc_uMsg = uMsg;
	Account::ActInfoProc_wParam = wParam;
	Account::ActInfoProc_lParam = lParam;
	switch (uMsg)
	{
	case WM_NOTIFY:
		Account::ActInfoProc_WM_NOTIFY();
		break;
	case WM_PAINT:
		Account::ActInfoProc_WM_PAINT();
		break;
	case WM_CREATE:
		Account::ActInfoProc_WM_CREATE();
		break;
	default://δ�Զ����������Ϣ
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//Ĭ�ϴ��ڹ���
	}
	return 0;
}

void Account::ActInfoProc_WM_NOTIFY() {
	switch (((LPNMHDR)Account::ActInfoProc_lParam)->code)
	{
	case NM_CLICK:case NM_RETURN://����
	{
		switch (LPNMHDR(Account::ActInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{
			//���µ�����б�����
			MyWnds::x_Listview = LPNMITEMACTIVATE(Account::ActInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Account::ActInfoProc_lParam)->iItem;
			break;
		}
		case returnSysLinkID:
		{
			//���ٿؼ�
			MyWnds::DestroyControl(Account::ActInfoProc_hwnd, { returnSysLinkID,dataInfoListID,dataInfoSysLinkID });
			//�����ؼ�
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), WM_CREATE, NULL, NULL);
			//���ı��
			Account::actInfoSysLinkFlag = 0;
			//�ػ���������
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case browseActSysLinkID:
		{
			//�б������ʼ��
			MyWnds::x_Listview = -1;
			MyWnds::y_Listview = 0;
			MyWnds::DestroyControl(Account::ActInfoProc_hwnd, { editActNameSysLinkID,editPasswdSysLinkID,creditSysLinkID,logoutSysLinkID,browseActSysLinkID });
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(returnSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, returnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�����û���Ϣ
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"���\">���</A>")\
				_T(" <A HREF=\"�޸�\">�޸�</A>")\
				_T(" <A HREF=\"ɾ��\">ɾ��</A>"),
				WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(dataInfoSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�û���Ϣ�б�
			CreateWindowEx(
				0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
				int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, (HMENU)dataInfoListID, MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			ListView_SetExtendedListViewStyle(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			//������
			LVCOLUMN temp = { 0 };
			temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
			temp.fmt = LVCFMT_CENTER;
			temp.cx = int(0.07 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("���");
			temp.iSubItem = 0;
			temp.cxDefault = 1;
			temp.cxMin = int(0.07 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 0, &temp);

			temp.cx = int(0.16 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("�û��ǳ�");
			temp.iSubItem = 1;
			temp.cxDefault = 0;
			temp.cxMin = int(0.16 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 1, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("�û���");
			temp.iSubItem = 2;
			temp.cxDefault = 0;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 2, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("����");
			temp.iSubItem = 3;
			temp.cxDefault = 0;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 3, &temp);


			temp.cx = int(0.06 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("Ȩ��");
			temp.iSubItem = 4;
			temp.cxDefault = 1;
			temp.cxMin = int(0.06 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 4, &temp);

			temp.cx = int(0.1 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("���");
			temp.iSubItem = 5;
			temp.cxDefault = 1;
			temp.cxMin = int(0.1 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 5, &temp);

			temp.cx = int(0.2 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("ע��ʱ��");
			temp.iSubItem = 6;
			temp.cxDefault = 0;
			temp.cxMin = int(0.2 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 6, &temp);
			//������
			Account tempAct;//��Ž�Ҫ��ȡ���û�����
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x + 1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mName;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mID;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mPasswd;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mPer.mAdmin);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mCredit);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempAct.mRegTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempAct.mRegTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

			}
			CloseHandle(tempHANDLE);//�ر��ļ�

			Account::actInfoSysLinkFlag = 4;
			//�ػ���������
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case dataInfoSysLinkID:
		{
			if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 0)//����
			{
				MyWnds::dialogFlag = dialogActAdd;
				MyWnds::Dialog();

			}
			else if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 1)//�޸�
			{
				TCHAR tempTCHAR[21] = {};//�洢Ҫ�޸ĵ��û���Ȩ����Ϣ
				ListView_GetItemText(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), MyWnds::y_Listview, 4, tempTCHAR, 4);
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID))) {
					MessageBox(Account::ActInfoProc_hwnd, _T("��ѡ��Ҫ�޸ĵ��û�"), _T("��ʾ"), MB_ICONINFORMATION);
				}
				else if (MyWnds::currentAct.mPer.mAdmin <= _wtoi(tempTCHAR)) {
					MessageBox(Account::ActInfoProc_hwnd, _T("����Ȩ�޲��㣬�޷��޸���ѡ�û���Ϣ"), _T("Ȩ�޲���"), MB_ICONERROR);
				}
				else {
					MyWnds::dialogFlag = dialogActModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 2)//ɾ��
			{
				TCHAR tempTCHAR[21] = {};
				if (MessageBox(Account::ActInfoProc_hwnd, _T("ȷ��Ҫɾ����Щ�û���"), _T("��ʾ"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y = ListView_GetItemCount(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID)) - 1; y >= 0; --y) {
						if (ListView_GetCheckState(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), y)) {
							//��ȡȨ��
							ListView_GetItemText(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), y , 4, tempTCHAR, 4);
							//����Ȩ���ж�
							if (MyWnds::currentAct.mPer.mAdmin <= _wtoi(tempTCHAR))continue;
							//��ȡ�û���
							ListView_GetItemText(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), y, 2, tempTCHAR, actUserName);
							Data<Account>::DataDelete(_T("Account.dat"), tempTCHAR);
						}
					}
				}
			}
			//׼��ˢ���б�����
			//ɾ��������
			ListView_DeleteAllItems(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID));
			//������
			Account tempAct;//��Ž�Ҫ��ȡ���û�����
			DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//���ļ�
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
				if (!tempDWORD)break;
				tempINSERT.mask = LVIF_TEXT;
				tempINSERT.iItem = x;
				tempINSERT.iSubItem = 0;
				_stprintf_s(tempTCHAR, _T("%d"), x + 1);
				tempINSERT.pszText = tempTCHAR;
				ListView_InsertItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mName;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mID;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				tempINSERT.pszText = tempAct.mPasswd;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mPer.mAdmin);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, _T("%d"), tempAct.mCredit);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

				++tempINSERT.iSubItem;
				_stprintf_s(tempTCHAR, tempAct.mRegTime.mDate);
				wcscat_s(tempTCHAR, _T(" "));
				wcscat_s(tempTCHAR, tempAct.mRegTime.mMoment);
				tempINSERT.pszText = tempTCHAR;
				ListView_SetItem(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), &tempINSERT);

			}
			CloseHandle(tempHANDLE);//�ر��ļ�

			Account::actInfoSysLinkFlag = 4;
			//�ػ���������
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case actSaveSysLinkID:
		{
			TCHAR tempTCHAR[(actName > actPasswd) ? actName : actPasswd];
			Edit_GetText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID)));//��ȡ�û�������ǳ�
			if (*tempTCHAR) {
				if (Account::actInfoSysLinkFlag == 1) {
					_stprintf_s(MyWnds::currentAct.mName, tempTCHAR);
				}
				else if (Account::actInfoSysLinkFlag == 2) {
					_stprintf_s(MyWnds::currentAct.mPasswd, tempTCHAR);
				}
				//�޸��û�
				Data<Account>::DataModify(_T("Account.dat"), MyWnds::currentAct);
				Account::actInfoSysLinkFlag = 0;
				DestroyWindow(GetDlgItem(Account::ActInfoProc_hwnd, actSaveSysLinkID));
				DestroyWindow(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID));
				SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), SW_SHOW);
				SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), SW_SHOW);
				SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), SW_SHOW);
				SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), SW_SHOW);
				if (MyWnds::currentAct.mPer.mAdmin) {
					SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
					MoveWindow(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
					ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), SW_SHOW);
				}
				//�ػ���������
				InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
				SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			}
			else {
				MessageBox(Account::ActInfoProc_hwnd, _T("����������Ч������������"), _T("����"), MB_OK | MB_ICONERROR);
			}
		}
		break;
		case editActNameSysLinkID:
		{
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), SW_HIDE);
			if (MyWnds::currentAct.mPer.mAdmin)ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), SW_HIDE);
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(actSaveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, actSaveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�����
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
				int(0.2 * MyWnds::homePageWidth), int(0.14 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), _T("�������µ��û��ǳ�"));//���ñ༭�ؼ��е��ı���ʾ
			Edit_LimitText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), actName - 1); //���ƿ��ڱ༭�ؼ���������û��ǳƵĳ���
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			Account::actInfoSysLinkFlag = 1;
			//�ػ���������
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
		}
		break;
		case editPasswdSysLinkID:
		{
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), SW_HIDE);
			ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), SW_HIDE);
			if (MyWnds::currentAct.mPer.mAdmin)ShowWindow(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), SW_HIDE);
			//����
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"����\">����</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.5 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(actSaveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, actSaveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//�����
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
				int(0.15 * MyWnds::homePageWidth), int(0.44 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), _T("�������µ�����"));//���ñ༭�ؼ��е��ı���ʾ
			Edit_LimitText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), actPasswd - 1); //���ƿ��ڱ༭�ؼ���������û��ǳƵĳ���
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			Account::actInfoSysLinkFlag = 2;
		}
		break;
		case creditSysLinkID:
		{
			if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 0)//��ֵ
			{
				MessageBox(Account::ActInfoProc_hwnd, _T("û������������Ϩr���s�ߨt���q\n���ں�����չ(������������Ļ�)"), _T("ά��"), MB_OK | MB_ICONERROR);
			}
			else if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 1)//����
			{
				MessageBox(Account::ActInfoProc_hwnd, _T("û������������Ϩr���s�ߨt���q\n���ں�����չ(������������Ļ�)"), _T("ά��"), MB_OK | MB_ICONERROR);
			}
		}
		break;
		case logoutSysLinkID:
		{
			if (MessageBox(Account::ActInfoProc_hwnd, _T("��ȷ��ע���û���\n��ע��˲������ɳ��أ�����"), _T("����"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
			{
				Data<Account>::DataDelete(_T("Account.dat"), MyWnds::currentAct.mID);
				MyWnds::DestroyChildWnd();
				MyWnds::DestroyControl(MyWnds::MainWndProc_hwnd, { homePageButtonID,actInfoButtonID,devInfoButtonID,tradeInfoButtonID,exitButtonID });
				Door::Login();
			}
		}
		break;
		}
	}
	break;
	case NM_DBLCLK://˫��
	{
		switch (LPNMHDR(Account::ActInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{

		}
		break;
		}
	}
	break;
	case NM_RCLICK://�һ�
	{
		switch (LPNMHDR(Account::ActInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{

		}
		break;
		}
	}
	break;

	case LVN_COLUMNCLICK:
	{
		ListCompareHandle = Account::ActInfoProc_hwnd;
		ListView_SortItemsEx(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), ListCompareFunc, Account::ActInfoProc_lParam);
		if (ListCompareFlag)ListCompareFlag = 0;
		else ListCompareFlag = 1;
		break;
	}

	}
}

void Account::ActInfoProc_WM_PAINT() {
	TCHAR tempTCHAR[50];
	PAINTSTRUCT ps;
	MyWnds::hDC = BeginPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), &ps);
	SelectObject(MyWnds::hDC, MyWnds::currentHFONT);
	if (actInfoSysLinkFlag == 4) {

	}
	else {
		if (actInfoSysLinkFlag == 1)_stprintf_s(tempTCHAR, _T("�û��ǳƣ�"));
		else _stprintf_s(tempTCHAR, _T("�û��ǳƣ�%s"), MyWnds::currentAct.mName);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û�����%s"), MyWnds::currentAct.mID);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.3 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("���룺"));
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û�Ȩ�ޣ�%d"), MyWnds::currentAct.mPer.mAdmin);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.6 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û���%d"), MyWnds::currentAct.mCredit);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("�û�ע��ʱ�䣺%s %s"), MyWnds::currentAct.mRegTime.mDate, MyWnds::currentAct.mRegTime.mMoment);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
	}
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), &ps);
	MyWnds::hDC = NULL;
}

void Account::ActInfoProc_WM_CREATE() {
	//��ʼ�����
	Account::actInfoSysLinkFlag = 0;
	//�༭�û��ǳ�
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"�༭\">�༭</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(editActNameSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//��������
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"��������\">��������</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(editPasswdSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//��ֵ/����
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"��ֵ\">��ֵ</A>")\
		_T("|<A HREF=\"����\"> ���� </A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(creditSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//ע���û�
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"ע���û�\">ע���û�</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(logoutSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//�鿴�����û�����ҪȨ�ޣ�
	if (MyWnds::currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"�鿴�����û�\">�鿴�����û�</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
			int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			Account::ActInfoProc_hwnd, HMENU(browseActSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
}

void Account::ActInfo() {
	//��������---�û���Ϣ
	HWND actInfoHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("actInfoClassName"), _T("�û���Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
	);
	if (!actInfoHwnd) {
		//ʵ�������������---�û���Ϣ
		WNDCLASSEX actInfoClass = { 0 };
		actInfoClass.cbSize = sizeof(WNDCLASSEX);
		actInfoClass.style = CS_HREDRAW | CS_VREDRAW;//����ʽ
		actInfoClass.lpfnWndProc = Account::ActInfoProc;//���ڹ���
		actInfoClass.hInstance = MyWnds::hInstance;//����ʵ��
		actInfoClass.hbrBackground = HBRUSH(6);//�౳����ˢ
		actInfoClass.lpszClassName = _T("actInfoClassName");//��������
		actInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//����ͼ��
		//ע�ᴰ����---�û���Ϣ
		if (!RegisterClassEx(&actInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("ע�ᴰ����---�û���Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}

		//��������---�û���Ϣ
		actInfoHwnd = CreateWindowEx(
			WS_EX_CONTROLPARENT, _T("actInfoClassName"), _T("�û���Ϣ"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
		);
		if (!actInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("��������---�û���Ϣ��ʧ��"), _T("������Ϣ"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//��Ʊ
void Account::BuyTicket(){}//�����½ӿڣ�ʵ����Ϊ����Ļ���ͨ������ˢ��ʱӦ���ô˺���
//��ֵ
void Account::Recharge(){}//Ϊʵ��ʹ�����½ӿ�
//����
void Account::Withdraw(){} //Ϊʵ��ʹ�����½ӿ�
