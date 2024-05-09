#include"Account.h"

//初始化总个数为0
UINT Account::mCount = 0;

//查找用户
bool Account::ActSearch(LPCTSTR userName, Account * const act) {
	bool tempflag = 0;//作为是否找到用户的标记
	Account tempAct = {0};//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	//打开文件
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
		if (!_tcscmp(tempAct.mUserName, userName)) {
			tempflag = 1;//找到用户
			break;
		}
	} while (tempDWORD);
	//关闭文件
	CloseHandle(tempHANDLE);
	//如果找到用户且调用函数时传入了接收Account的参数act，那么输出找到的Account信息
	if (tempflag && act != NULL) *act = tempAct;
	return tempflag;
}

//增加用户
bool Account::ActAdd(const Account& act) {
	//打开文件
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//设定文件指针--文件末尾
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//写入文件
	DWORD written;
	WriteFile(tempHANDLE, &act, sizeof(Account), &written, NULL);
	//关闭文件
	CloseHandle(tempHANDLE);
	++Account::mCount;
	return 1;
}

//修改用户
bool Account::ActModify(const Account& act) {
	bool tempflag = 0;//作为是否找到用户的标记
	Account tempAct = {0};//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	DWORD written = 0;//存放实际写入的字节数
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
		if (!_tcscmp(tempAct.mUserName, act.mUserName)) {
			tempflag = 1;
			break;
		}
	} while (tempDWORD);
	if (tempflag) {
		//文件指针前移一整个Account数据
		LARGE_INTEGER tempL_I;
		tempL_I.QuadPart = -long long(sizeof(Account));
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//写入文件
		WriteFile(tempHANDLE, &act, sizeof(Account), &written, NULL);
	}
	CloseHandle(tempHANDLE);
	return 1;
}


//删除用户
bool Account::ActDelete(LPCTSTR userName) {
	bool tempflag = 0;//作为是否找到用户的标记
	Account tempAct = { 0 }, endAct = { 0 };//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	DWORD written = 0;//存放实际写入的字节数
	LARGE_INTEGER tempL_I;
	//打开文件
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//移动文件指针到最后一个数据
	tempL_I.QuadPart = -long long(sizeof(Account));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//读取最后一个数据
	ReadFile(tempHANDLE, &endAct, sizeof(Account), &tempDWORD, NULL);
	if (!_tcscmp(endAct.mUserName, userName)) {
		//文件指针前移一整个Account数据
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//截断文件
		SetEndOfFile(tempHANDLE);
		CloseHandle(tempHANDLE);
		--Account::mCount;
		return 1;
	}
	//移动文件指针到文件开头
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	//寻找要删除的用户
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//读取文件
		if (!_tcscmp(tempAct.mUserName, userName)) {
			tempflag = 1;//找到用户
			break;
		}
	} while (tempDWORD);
	//文件指针前移一整个Account数据
	tempL_I.QuadPart = -long long(sizeof(Account));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
	//用最后一个数据覆盖要删除的数据
	WriteFile(tempHANDLE, &endAct, sizeof(Account), &written, NULL);
	//移动文件指针到最后一个数据
	tempL_I.QuadPart = -long long(sizeof(Account));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//截断文件
	SetEndOfFile(tempHANDLE);
	CloseHandle(tempHANDLE);
	--Account::mCount;
	return 1;
}
