#include"Device.h"
#include "MyWnds.h"
#include <CommCtrl.h>
#include "Data.hpp"
#include <windowsx.h>

//初始化总个数为0
UINT Device::mCount = 0;

HWND Device::DevInfoProc_hwnd;
UINT Device::DevInfoProc_uMsg;
WPARAM Device::DevInfoProc_wParam;
LPARAM Device::DevInfoProc_lParam;

BYTE Device::devInfoFlag;

Device Device::currentDev = { 0 };

//设备信息
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
	default://未自定义的其他消息
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//默认窗口过程
	}
	return 0;
}

void Device::DevInfoProc_WM_NOTIFY() {
	switch (((LPNMHDR)Device::DevInfoProc_lParam)->code) 
	{
	case NM_CLICK:case NM_RETURN://单击
	{
		switch (LPNMHDR(Device::DevInfoProc_lParam)->idFrom) {
		case devSaveSysLinkID:
		{
			TCHAR tempTCHAR[devIntro];
			Edit_GetText(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), tempTCHAR, devIntro);//获取介绍
			if (*tempTCHAR) {
				//修改设备介绍
				_stprintf_s(Device::currentDev.mIntro, tempTCHAR);
				Data<Device>::DataModify(_T("Device.dat"), Device::currentDev);
				//销毁控件
				DestroyWindow(GetDlgItem(Device::DevInfoProc_hwnd, devSaveSysLinkID));
				Edit_SetReadOnly(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), TRUE);//设置只读状态
				//显示“编辑”控件
				SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
				MoveWindow(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), true);
				ShowWindow(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), SW_SHOW);
				//重绘整个窗口
				InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
				SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);
			}
			else {
				MessageBox(Device::DevInfoProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
			}
			break;
		}
		case editDevIntroSysLinkID:
		{
			//隐藏“编辑”控件
			ShowWindow(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), SW_HIDE);
			//保存
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"保存\">保存</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Device::DevInfoProc_hwnd, HMENU(devSaveSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, devSaveSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);

			Edit_SetReadOnly(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), FALSE);//设置只读状态

			//重绘整个窗口
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);

			break;
		}
		case returnSysLinkID:
		{
			//销毁控件
			MyWnds::DestroyControl(Device::DevInfoProc_hwnd, { returnSysLinkID, devIntroEditID , editDevIntroSysLinkID ,devSaveSysLinkID});
			//创建控件
			SendMessage(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), WM_CREATE, NULL, NULL);
			//更新标记
			Device::devInfoFlag = 0;
			//重绘整个窗口
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}
		case dataInfoListID:
		{
			//更新点击的列表坐标
			MyWnds::x_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iItem;
			break;
		}
		case dataInfoSysLinkID:
		{
			if (PNMLINK(Device::DevInfoProc_lParam)->item.iLink == 0)//增加
			{
				MyWnds::dialogFlag = dialogDevAdd;
				MyWnds::Dialog();

			}
			else if (PNMLINK(Device::DevInfoProc_lParam)->item.iLink == 1)//修改
			{
				if ((MyWnds::x_Listview == -1 && MyWnds::y_Listview == 0) || MyWnds::y_Listview >= ListView_GetItemCount(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID))) {
					MessageBox(Device::DevInfoProc_hwnd, _T("请选择要修改的设备"), _T("提示"), MB_ICONINFORMATION);
				}
				else {
					MyWnds::dialogFlag = dialogDevModify;
					MyWnds::Dialog();
				}
			}
			else if (PNMLINK(Device::DevInfoProc_lParam)->item.iLink == 2)//删除
			{
				TCHAR tempTCHAR[21] = {};
				if (MessageBox(Device::DevInfoProc_hwnd, _T("确定要删除这些设备吗？"), _T("提示"), MB_OKCANCEL | MB_ICONINFORMATION) == IDOK) {
					for (int y = ListView_GetItemCount(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID)) - 1; y >= 0; --y) {
						if (ListView_GetCheckState(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), y)) {
							ListView_GetItemText(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), y, 2, tempTCHAR, devID * 2);
							Data<Device>::DataDelete(_T("Device.dat"), tempTCHAR);
						}
					}
				}
			}
			//准备刷新列表数据
			//删除所有行
			ListView_DeleteAllItems(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID));
			//插入行
			Device tempDev;//存放将要读取的设备数据
			DWORD tempDWORD = 0;//存放实际读取的字节数
			TCHAR tempTCHAR[30];
			LVITEM tempINSERT = { 0 };
			HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
			for (int x = 0; true; ++x) {
				ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//读取文件
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
			CloseHandle(tempHANDLE);//关闭文件
			//重绘整个窗口
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);
			break;
		}

		}
		break;
	}

	case NM_DBLCLK://双击
	{
		switch (LPNMHDR(Device::DevInfoProc_lParam)->idFrom) {
		case dataInfoListID:
		{
			//更新当前查看的设备
			DWORD tempDWORD = 0;//存放实际读取的字节数
			//获取点击位置的设备信息
			HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
			//文件指针移动到该设备数据之前
			LARGE_INTEGER tempL_I;
			tempL_I.QuadPart = (long long)(sizeof(Device)) * MyWnds::y_Listview;
			SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
			ReadFile(tempHANDLE, &Device::currentDev, sizeof(Device), &tempDWORD, NULL);//读取文件
			CloseHandle(tempHANDLE);//关闭文件

			//更新标记
			Device::devInfoFlag = 1;
			//更新点击的列表坐标
			MyWnds::x_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iSubItem;
			MyWnds::y_Listview = LPNMITEMACTIVATE(Device::DevInfoProc_lParam)->iItem;
			//销毁控件
			MyWnds::DestroyControl(Device::DevInfoProc_hwnd, { dataInfoListID,dataInfoSysLinkID });
			//返回
			CreateWindowEx(
				0, _T("SysLink"), _T("<A HREF=\"返回\">返回</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
				int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
				Device::DevInfoProc_hwnd, HMENU(returnSysLinkID), MyWnds::hInstance, NULL
			);
			SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, returnSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			//编辑框--介绍
			CreateWindowEx(
				WS_EX_CLIENTEDGE, WC_EDIT, Device::currentDev.mIntro, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE | ES_WANTRETURN |ES_READONLY,
				int(0.1 * MyWnds::homePageWidth), int(0.45 * MyWnds::homePageHeight), int(0.65 * MyWnds::homePageWidth), int(0.5 * MyWnds::homePageHeight),
				Device::DevInfoProc_hwnd, HMENU(devIntroEditID), MyWnds::hInstance, NULL
			);
			Edit_SetCueBannerText(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), _T("请输入设备介绍"));//设置编辑控件中的文本提示
			Edit_LimitText(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), devIntro - 1); //限制可在编辑控件中输入的介绍的长度
			SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, devIntroEditID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			if (MyWnds::currentAct.mPer.mAdmin) {
				//编辑介绍内容
				CreateWindowEx(
					0, _T("SysLink"), _T("<A HREF=\"编辑\">编辑</A>"), WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
					int(0.7 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), int(0.1 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
					Device::DevInfoProc_hwnd, HMENU(editDevIntroSysLinkID), MyWnds::hInstance, NULL
				);
				SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, editDevIntroSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
			}
			//重绘整个窗口
			InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
			SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);

		}
		break;
		}
		break;
	}

	case NM_RCLICK://右击
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
	//设定字体
	SelectObject(MyWnds::hDC, MyWnds::currentHFONT);
	if (devInfoFlag == 1) {
		_stprintf_s(tempTCHAR, _T("设备名称：%s"), Device::currentDev.mName);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.15 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("设备ID：%s"), Device::currentDev.mID);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.2 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("价格：%d"), Device::currentDev.mPrice);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.25 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("收费：%d"), Device::currentDev.mCharge);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.3 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("设备录入时间：%s %s"), Device::currentDev.mAddTime.mDate, Device::currentDev.mAddTime.mMoment);
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.35 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
		_stprintf_s(tempTCHAR, _T("介绍："));
		TextOut(MyWnds::hDC, int(0.1 * MyWnds::homePageWidth), int(0.4 * MyWnds::homePageHeight), tempTCHAR, wcslen(tempTCHAR));
	}
	EndPaint(GetDlgItem(MyWnds::MainWndProc_hwnd, devInfoWndID), &ps);
	MyWnds::hDC = NULL;
}

void Device::DevInfoProc_WM_CREATE() {
	//标记初始化
	Device::devInfoFlag = 0;
	//列表坐标初始化
	MyWnds::x_Listview = -1;
	MyWnds::y_Listview = 0;
	//更改设备信息
	if (MyWnds::currentAct.mPer.mAdmin) {
		CreateWindowEx(
			0, _T("SysLink"), _T("<A HREF=\"添加\">添加</A>")\
			_T(" <A HREF=\"修改\">修改</A>")\
			_T(" <A HREF=\"删除\">删除</A>"),
			WS_CHILD | WS_VISIBLE | LWS_TRANSPARENT,
			int(0.8 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight), int(0.2 * MyWnds::homePageWidth), int(0.05 * MyWnds::homePageHeight),
			Device::DevInfoProc_hwnd, HMENU(dataInfoSysLinkID), MyWnds::hInstance, NULL
		);
		SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoSysLinkID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	}
	//设备信息列表
	CreateWindowEx(
		0, WC_LISTVIEW, _T(""), WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS,
		int(0.05 * MyWnds::homePageWidth), int(0.1 * MyWnds::homePageHeight), int(0.9 * MyWnds::homePageWidth), int(0.85 * MyWnds::homePageHeight),
		Device::DevInfoProc_hwnd, (HMENU)dataInfoListID, MyWnds::hInstance, NULL
	);
	SendMessage(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), WM_SETFONT, (WPARAM)MyWnds::currentHFONT, TRUE);
	ListView_SetExtendedListViewStyle(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), LVS_EX_COLUMNSNAPPOINTS | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//插入列
	LVCOLUMN temp = { 0 };
	temp.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH | LVCF_MINWIDTH | LVCF_SUBITEM;
	temp.fmt = LVCFMT_CENTER;
	temp.cx = int(0.07 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("序号");
	temp.iSubItem = 0;
	temp.cxMin = int(0.07 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 0, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("设备名称");
	temp.iSubItem = 1;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 1, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("设备ID");
	temp.iSubItem = 2;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 2, &temp);

	temp.cx = int(0.12 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("价格");
	temp.iSubItem = 3;
	temp.cxMin = int(0.12 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 3, &temp);

	temp.cx = int(0.11 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("收费");
	temp.iSubItem = 4;
	temp.cxMin = int(0.11 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 4, &temp);

	temp.cx = int(0.2 * MyWnds::homePageWidth);
	temp.pszText = (LPTSTR)_T("录入时间");
	temp.iSubItem = 5;
	temp.cxMin = int(0.2 * MyWnds::homePageWidth);
	ListView_InsertColumn(GetDlgItem(Device::DevInfoProc_hwnd, dataInfoListID), 5, &temp);
	//插入行
	Device tempDev;//存放将要读取的设备数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	TCHAR tempTCHAR[30];
	LVITEM tempINSERT = { 0 };
	HANDLE tempHANDLE = CreateFile(_T("Device.dat"), GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);//打开文件
	for (int x = 0; true; ++x) {
		ReadFile(tempHANDLE, &tempDev, sizeof(Device), &tempDWORD, NULL);//读取文件
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
	CloseHandle(tempHANDLE);//关闭文件

	//重绘整个窗口
	InvalidateRect(Device::DevInfoProc_hwnd, NULL, TRUE);
	SendMessage(Device::DevInfoProc_hwnd, WM_PAINT, NULL, NULL);

}



void Device::DevInfo() {
	//创建窗口---设备信息
	HWND devInfoHwnd = CreateWindowEx(
		0, _T("devInfoClassName"), _T("设备信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
		int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
		MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
	);
	if (!devInfoHwnd) {
		//实例化窗口类对象---设备信息
		WNDCLASSEX devInfoClass = { 0 };
		devInfoClass.cbSize = sizeof(WNDCLASSEX);
		devInfoClass.style = CS_HREDRAW | CS_VREDRAW;//类样式
		devInfoClass.lpfnWndProc = Device::DevInfoProc;//窗口过程
		devInfoClass.hInstance = MyWnds::hInstance;//程序实例
		devInfoClass.hbrBackground = HBRUSH(6);//类背景画刷
		devInfoClass.lpszClassName = _T("devInfoClassName");//窗口类名
		devInfoClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//窗口图标
		//注册窗口类---设备信息
		if (!RegisterClassEx(&devInfoClass)) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("注册窗口类---设备信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
		//创建窗口---设备信息
		devInfoHwnd = CreateWindowEx(
			0, _T("devInfoClassName"), _T("设备信息"), WS_TILED | WS_CHILD | WS_VISIBLE,
			int((homePageButtonWidth + homePageButtonCoord_X * 2) * MyWnds::defMainWndWidth), int(homePageButtonCoord_Y / 2.0 * MyWnds::defMainWndHeight), MyWnds::homePageWidth, MyWnds::homePageHeight,
			MyWnds::MainWndProc_hwnd, HMENU(devInfoWndID), MyWnds::hInstance, NULL
		);
		if (!devInfoHwnd) {
			MessageBox(MyWnds::MainWndProc_hwnd, _T("创建窗口---设备信息，失败"), _T("错误信息"), MB_OK | MB_ICONERROR | MB_APPLMODAL);
			exit(-1);
		}
	}
}
