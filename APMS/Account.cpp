#include"Account.h"
#include"MyWnds.h"
#include "Door.h"
#include"Data.hpp"
#include <CommCtrl.h>
#include <windowsx.h>


//初始化总个数为0
UINT Account::mCount = 0;

HWND Account::ActInfoProc_hwnd;
UINT Account::ActInfoProc_uMsg;
WPARAM Account::ActInfoProc_wParam;
LPARAM Account::ActInfoProc_lParam;

BYTE Account::actInfoSysLinkFlag;

//用户信息
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
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void Account::ActInfoProc_WM_NOTIFY() {
	switch (((LPNMHDR)Account::ActInfoProc_lParam)->code)
	{
	case NM_CLICK:case NM_RETURN://单击
	{
		switch (LPNMHDR(Account::ActInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{
			//更新点击的列表坐标
			MyWnds::x_Listview = LPNMITEMACTIVATE(Account::ActInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Account::ActInfoProc_lParam)->iItem;
			break;
		}
		case returnSysLinkID:
		{
			//销毁控件
			MyWnds::DestroyControl(Account::ActInfoProc_hwnd, { returnSysLinkID,dataInfoListID,dataInfoSysLinkID });
			//创建控件
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), WM_CREATE, NULL, NULL);
			//更改标记
			Account::actInfoSysLinkFlag = 0;
			//重绘整个窗口
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case browseActSysLinkID:
		{
			//列表坐标初始化
			MyWnds::x_Listview = -1;
			MyWnds::y_Listview = 0;
			MyWnds::DestroyControl(Account::ActInfoProc_hwnd, { editActNameSysLinkID,editPasswdSysLinkID,creditSysLinkID,logoutSysLinkID,browseActSysLinkID });
			//返回
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"返回\">返回</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(returnSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, returnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//更改用户信息
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"添加\">添加</A>")\
				_T(" <A HREF=\"修改\">修改</A>")\
				_T(" <A HREF=\"删除\">删除</A>"),
				WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(dataInfoSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//用户信息列表
			CreateWindowEx(
				0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
				int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, (HMENU)dataInfoListID, MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			ListView_SetExtendedListViewStyle(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
			//插入列
			LVCOLUMN temp = { 0 };
			temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM | LVCF_DEFAULTWIDTH;
			temp.fmt = LVCFMT_CENTER;
			temp.cx = int(0.07 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("序号");
			temp.iSubItem = 0;
			temp.cxDefault = 1;
			temp.cxMin = int(0.07 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 0, &temp);

			temp.cx = int(0.16 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("用户昵称");
			temp.iSubItem = 1;
			temp.cxDefault = 0;
			temp.cxMin = int(0.16 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 1, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("用户名");
			temp.iSubItem = 2;
			temp.cxDefault = 0;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 2, &temp);

			temp.cx = int(0.15 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("密码");
			temp.iSubItem = 3;
			temp.cxDefault = 0;
			temp.cxMin = int(0.15 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 3, &temp);


			temp.cx = int(0.06 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("权限");
			temp.iSubItem = 4;
			temp.cxDefault = 1;
			temp.cxMin = int(0.06 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 4, &temp);

			temp.cx = int(0.1 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("余额");
			temp.iSubItem = 5;
			temp.cxDefault = 1;
			temp.cxMin = int(0.1 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 5, &temp);

			temp.cx = int(0.2 * MyWnds::homePageWidth);
			temp.pszText = (LPTSTR)_T("注册时间");
			temp.iSubItem = 6;
			temp.cxDefault = 0;
			temp.cxMin = int(0.2 * MyWnds::homePageWidth);
			ListView_InsertColumn(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), 6, &temp);
			//插入行
			Account tempAct;//存放将要读取的用户数据
			DWORD tempDWORD = 0;//存放实际读取的字节数
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
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
			CloseHandle(tempHANDLE);//关闭文件

			Account::actInfoSysLinkFlag = 4;
			//重绘整个窗口
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case dataInfoSysLinkID:
		{
			if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 0)//增加
			{
				MyWnds::dialogFlag = dialogActAdd;
				MyWnds::Dialog();

			}
			else if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 1)//修改
			{
				TCHAR tempTCHAR[21] = {};//存储要修改的用户的权限信息
				ListView_GetItemText(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), MyWnds::y_Listview, 4, tempTCHAR, 4);
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID))) {
					MessageBox(Account::ActInfoProc_hwnd, _T("请选择要修改的用户"), _T("提示"), MB_ICONINFORMATION);
				}
				else if (MyWnds::currentAct.mPer.mAdmin <= _wtoi(tempTCHAR)) {
					MessageBox(Account::ActInfoProc_hwnd, _T("您的权限不足，无法修改所选用户信息"), _T("权限不足"), MB_ICONERROR);
				}
				else {
					MyWnds::dialogFlag = dialogActModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 2)//删除
			{
				TCHAR tempTCHAR[21] = {};
				if (MessageBox(Account::ActInfoProc_hwnd, _T("确定要删除这些用户吗？"), _T("提示"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y = ListView_GetItemCount(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID)) - 1; y >= 0; --y) {
						if (ListView_GetCheckState(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), y)) {
							//获取权限
							ListView_GetItemText(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), y , 4, tempTCHAR, 4);
							//进行权限判定
							if (MyWnds::currentAct.mPer.mAdmin <= _wtoi(tempTCHAR))continue;
							//获取用户名
							ListView_GetItemText(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID), y, 2, tempTCHAR, actUserName);
							Data<Account>::DataDelete(_T("Account.dat"), tempTCHAR);
						}
					}
				}
			}
			//准备刷新列表数据
			//删除所有行
			ListView_DeleteAllItems(GetDlgItem(Account::ActInfoProc_hwnd, dataInfoListID));
			//插入行
			Account tempAct;//存放将要读取的用户数据
			DWORD tempDWORD = 0;//存放实际读取的字节数
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
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
			CloseHandle(tempHANDLE);//关闭文件

			Account::actInfoSysLinkFlag = 4;
			//重绘整个窗口
			InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
			SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case actSaveSysLinkID:
		{
			TCHAR tempTCHAR[(actName > actPasswd) ? actName : actPasswd];
			Edit_GetText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), tempTCHAR, 1 + GetWindowTextLength(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID)));//获取用户输入的昵称
			if (*tempTCHAR) {
				if (Account::actInfoSysLinkFlag == 1) {
					_stprintf_s(MyWnds::currentAct.mName, tempTCHAR);
				}
				else if (Account::actInfoSysLinkFlag == 2) {
					_stprintf_s(MyWnds::currentAct.mPasswd, tempTCHAR);
				}
				//修改用户
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
				//重绘整个窗口
				InvalidateRect(Account::ActInfoProc_hwnd, NULL, TRUE);
				SendMessage(Account::ActInfoProc_hwnd, WM_PAINT, NULL, NULL);
			}
			else {
				MessageBox(Account::ActInfoProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
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
			//保存
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"保存\">保存</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(actSaveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, actSaveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//输入框
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mName, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
				int(0.2 * MyWnds::homePageWidth), int(0.14 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), _T("请输入新的用户昵称"));//设置编辑控件中的文本提示
			Edit_LimitText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), actName - 1); //限制可在编辑控件中输入的用户昵称的长度
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			Account::actInfoSysLinkFlag = 1;
			//重绘整个窗口
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
			//保存
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"保存\">保存</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
				int(0.5 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(actSaveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, actSaveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//输入框
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, MyWnds::currentAct.mPasswd, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_TABSTOP,
				int(0.15 * MyWnds::homePageWidth), int(0.44 * MyWnds::homePageHeight), int(0.25 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Account::ActInfoProc_hwnd, HMENU(editActInfoEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), _T("请输入新的密码"));//设置编辑控件中的文本提示
			Edit_LimitText(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), actPasswd - 1); //限制可在编辑控件中输入的用户昵称的长度
			SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActInfoEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			Account::actInfoSysLinkFlag = 2;
		}
		break;
		case creditSysLinkID:
		{
			if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 0)//充值
			{
				MessageBox(Account::ActInfoProc_hwnd, _T("没有做这个功能嘞╮（╯＿╰）╭\n便于后续扩展(如果是真的软件的话)"), _T("维护"), MB_OK | MB_ICONERROR);
			}
			else if (PNMLINK(Account::ActInfoProc_lParam)->item.iLink == 1)//提现
			{
				MessageBox(Account::ActInfoProc_hwnd, _T("没有做这个功能嘞╮（╯＿╰）╭\n便于后续扩展(如果是真的软件的话)"), _T("维护"), MB_OK | MB_ICONERROR);
			}
		}
		break;
		case logoutSysLinkID:
		{
			if (MessageBox(Account::ActInfoProc_hwnd, _T("您确定注销用户吗？\n请注意此操作不可撤回！！！"), _T("警告"), MB_OKCANCEL | MB_ICONWARNING) == IDOK)
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
	case NM_DBLCLK://双击
	{
		switch (LPNMHDR(Account::ActInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{

		}
		break;
		}
	}
	break;
	case NM_RCLICK://右击
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
		if (actInfoSysLinkFlag == 1)_stprintf_s(tempTCHAR, _T("用户昵称："));
		else _stprintf_s(tempTCHAR, _T("用户昵称：%s"), MyWnds::currentAct.mName);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户名：%s"), MyWnds::currentAct.mID);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.3 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("密码："));
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户权限：%d"), MyWnds::currentAct.mPer.mAdmin);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.6 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户余额：%d"), MyWnds::currentAct.mCredit);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("用户注册时间：%s %s"), MyWnds::currentAct.mRegTime.mDate, MyWnds::currentAct.mRegTime.mMoment);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
	}
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, actInfoWndID), &ps);
	MyWnds::hDC = NULL;
}

void Account::ActInfoProc_WM_CREATE() {
	//初始化标记
	Account::actInfoSysLinkFlag = 0;
	//编辑用户昵称
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"编辑\">编辑</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.5 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(editActNameSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editActNameSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//更改密码
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"更改密码\">更改密码</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.49 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(editPasswdSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, editPasswdSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//充值/提现
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"充值\">充值</A>")\
		_T("|<A HREF=\"提现\"> 提现 </A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.48 * MyWnds::homePageWidth), int(0.75 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(creditSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, creditSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//注销用户
	CreateWindowEx(
		0, _T("SysLink"), _T("<A HREF=\"注销用户\">注销用户</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
		int(0.49 * MyWnds::homePageWidth), int(0.9 * MyWnds::homePageHeight), int(0.15 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
		Account::ActInfoProc_hwnd, HMENU(logoutSysLinkID), MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, logoutSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	//查看所有用户（需要权限）
	if (MyWnds::currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"查看所有用户\">查看所有用户</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT | WS_TABSTOP,
			int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.3 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			Account::ActInfoProc_hwnd, HMENU(browseActSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(Account::ActInfoProc_hwnd, browseActSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
}

void Account::ActInfo() {
	//创建窗口---用户信息
	HWND actInfoHwnd = CreateWindowEx(
		WS_EX_CONTROLPARENT, _T("actInfoClassName"), _T("用户信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
	);
	if (!actInfoHwnd) {
		//实例化窗口类对象---用户信息
		WNDCLASSEX actInfoClass = { 0 };
		actInfoClass.cbSize = sizeof(WNDCLASSEX);
		actInfoClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		actInfoClass.lpfnWndProc = Account::ActInfoProc;//窗口过程
		actInfoClass.hInstance = MyWnds::hInstance;//程序实例
		actInfoClass.hbrBackground = HBRUSH(6);//类背景画刷
		actInfoClass.lpszClassName = _T("actInfoClassName");//窗口类名
		actInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---用户信息
		if (!RegisterClassEx(&actInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---用户信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}

		//创建窗口---用户信息
		actInfoHwnd = CreateWindowEx(
			WS_EX_CONTROLPARENT, _T("actInfoClassName"), _T("用户信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(actInfoWndID), MyWnds::hInstance, NULL
		);
		if (!actInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---用户信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}

//购票
void Account::BuyTicket(){}//仅留下接口，实际作为软件的话在通过机器刷卡时应调用此函数
//充值
void Account::Recharge(){}//为实际使用留下接口
//提现
void Account::Withdraw(){} //为实际使用留下接口
