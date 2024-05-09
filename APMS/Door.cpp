#include"Door.h"
#include"Account.h"
#include"MyWnds.h"


void Door::Login() {
	MyWnds::createLoginConfirmButton();
	MyWnds::createRegisterButton();
	MyWnds::createUserNameEdit_Static();
	MyWnds::createPasswdEdit_Static();
	//更改窗口风格与标记
	MyWnds::mainWndStyle = LoginUI;
	MyWnds::mainWndFlag = LoginUI;
	//重绘整个窗口
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::LoginConfirm() {
	bool tempFlag = 0;//设定临时标记
	Account tempAct = {0};//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	TCHAR tempUserName[actUserName] = _T(""), tempPasswd[actPasswd] = _T("");//接收用户输入的用户名和密码
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), tempUserName, actUserName);//获取用户输入的用户名
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), tempPasswd, actPasswd);//获取用户输入的密码
	if (!*tempUserName || !*tempPasswd ) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	//检查用户名与密码
	if (Account::ActSearch(tempUserName, &tempAct)) {
		if (!_tcscmp(tempAct.mPasswd, tempPasswd)) {
			tempFlag = 1;//匹配成功
			MyWnds::currentAct = tempAct;
		}
	}
	if (!tempFlag) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("您输入的用户名或密码错误，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	//销毁控件
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
	//创建主页
	MyWnds::HomePage();
	MyWnds::createHomePageButton();
	MyWnds::createActInfoButton();
	MyWnds::createDevInfoButton();
	MyWnds::createTradeInfoButton();
	MyWnds::createExitButton();
	//更改窗口风格与标记
	MyWnds::mainWndStyle = HomeUI;
	MyWnds::mainWndFlag = HomeUI;
	//重绘整个窗口
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::Register() {
	MyWnds::createLoginButton();
	MyWnds::createRegisterConfirmButton();
	MyWnds::createActNameEdit_Static();
	MyWnds::createUserNameEdit_Static();
	MyWnds::createPasswdEdit_Static();
	//更改窗口风格与标记
	MyWnds::mainWndStyle = RegisterUI;
	MyWnds::mainWndFlag = RegisterUI;
	//重绘整个窗口
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}

void Door::RegisterConfirm() {
	Account tempAct;//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID), MyWnds::currentAct.mName, actName);//获取用户输入的昵称
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID), MyWnds::currentAct.mUserName, actUserName);//获取用户输入的用户名
	Edit_GetText(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID), MyWnds::currentAct.mPasswd, actPasswd);//获取用户输入的密码
	if (!*MyWnds::currentAct.mUserName|| !*MyWnds::currentAct.mPasswd|| !*MyWnds::currentAct.mName) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("您的输入无效，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	//检查输入的用户名是否已存在
	if (Account::ActSearch(MyWnds::currentAct.mUserName)) {
		MessageBox(MyWnds::MainWndProc_hwnd, _T("您输入的用户名已存在，请重新输入"), _T("错误"), MB_OK | MB_ICONERROR);
		return;
	}
	//设定普通权限
	MyWnds::currentAct.mPer.mAdmin = normalPer;
	//设定初始余额为0
	MyWnds::currentAct.mCredit = 0;
	//获取系统时间&设定注册时间
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	_stprintf_s(MyWnds::currentAct.mRegTime.mDate, _T("%04d-%02d-%02d"), sysTime.wYear, sysTime.wMonth, sysTime.wDay);
	_stprintf_s(MyWnds::currentAct.mRegTime.mMoment, _T("%02d:%02d:%02d"), sysTime.wHour, sysTime.wMinute, sysTime.wSecond);
	//调用函数创建用户
	Account::ActAdd(MyWnds::currentAct);
	//销毁控件
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, loginButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, registerConfirmButtonID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, actNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, userNameEditID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdStaticID));
	DestroyWindow(GetDlgItem(MyWnds::MainWndProc_hwnd, passwdEditID));
	//创建主页
	MyWnds::HomePage();
	MyWnds::createHomePageButton();
	MyWnds::createActInfoButton();
	MyWnds::createDevInfoButton();
	MyWnds::createTradeInfoButton();
	MyWnds::createExitButton();
	//更改窗口风格与标记
	MyWnds::mainWndStyle = HomeUI;
	MyWnds::mainWndFlag = HomeUI;
	//重绘整个窗口
	InvalidateRect(MyWnds::MainWndProc_hwnd, NULL, TRUE);
	SendMessage(MyWnds::MainWndProc_hwnd, WM_PAINT, NULL, NULL);
}