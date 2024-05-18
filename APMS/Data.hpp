#pragma once
#include<Windows.h>

template<class T>
class Data {
public:
	//查找数据
	static bool DataSearch(LPCTSTR fillname,LPCTSTR id, T* const data = NULL);
	//增加数据
	static bool DataAdd(LPCTSTR fillname,const T& data);
	//修改数据
	static bool DataModify(LPCTSTR fillname, const T& data);
	//删除数据
	static bool DataDelete(LPCTSTR fillname, LPCTSTR id);
};

//查找数据
template<class T>
bool Data<T>::DataSearch(LPCTSTR fillname, LPCTSTR id, T* const data) {
	bool tempflag = 0;//作为是否找到用户的标记
	T tempData = { 0 };//存放将要读取的用户数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	//打开文件
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempData, sizeof(T), &tempDWORD, NULL);//读取文件
		if (!_tcscmp(tempData.mID, id)) {
			tempflag = 1;//找到数据
			break;
		}
	} while (tempDWORD);
	//关闭文件
	CloseHandle(tempHANDLE);
	//如果找到T数据且调用函数时传入了接收T的参数data，那么输出找到的T信息
	if (tempflag && data != NULL) *data = tempData;
	return tempflag;
}

//增加数据
template<class T>
bool Data<T>::DataAdd(LPCTSTR fillname, const T& data) {
	//打开文件
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//设定文件指针--文件末尾
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//写入文件
	DWORD written;
	WriteFile(tempHANDLE, &data, sizeof(T), &written, NULL);
	//关闭文件
	CloseHandle(tempHANDLE);
	++T::mCount;
	return 1;
}

//修改数据
template<class T>
bool Data<T>::DataModify(LPCTSTR fillname, const T& data) {
	bool tempflag = 0;//作为是否找到数据的标记
	T tempData = { 0 };//存放将要读取的数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	DWORD written = 0;//存放实际写入的字节数
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempData, sizeof(T), &tempDWORD, NULL);//读取文件
		if (!_tcscmp(tempData.mID, data.mID)) {
			tempflag = 1;//找到数据
			break;
		}
	} while (tempDWORD);
	if (tempflag) {
		//文件指针前移一整个T数据
		LARGE_INTEGER tempL_I;
		tempL_I.QuadPart = -(long long)(sizeof(T));
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//覆盖写入数据
		WriteFile(tempHANDLE, &data, sizeof(T), &written, NULL);
	}
	CloseHandle(tempHANDLE);
	return 1;
}

//删除数据
template<class T>
bool Data<T>::DataDelete(LPCTSTR fillname, LPCTSTR id) {
	bool tempflag = 0;//作为是否找到数据的标记
	T tempData = { 0 }, endData = { 0 };//存放将要读取的数据
	DWORD tempDWORD = 0;//存放实际读取的字节数
	DWORD written = 0;//存放实际写入的字节数
	LARGE_INTEGER tempL_I;
	//打开文件
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//移动文件指针到最后一个数据之前
	tempL_I.QuadPart = -(long long)(sizeof(T));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//读取最后一个数据
	ReadFile(tempHANDLE, &endData, sizeof(T), &tempDWORD, NULL);
	//当最后一个数据即为要删除的数据时,直接截断文件
	if (!_tcscmp(endData.mID, id)) {
		//文件指针前移一整个T数据
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//截断文件
		SetEndOfFile(tempHANDLE);
		CloseHandle(tempHANDLE);
		--T::mCount;
		return 1;
	}
	//移动文件指针到文件开头
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	//寻找要删除的数据
	do {
		ReadFile(tempHANDLE, &tempData, sizeof(T), &tempDWORD, NULL);//读取文件
		if (!_tcscmp(tempData.mID, id)) {
			tempflag = 1;//找到数据
			break;
		}
	} while (tempDWORD);
	if (tempflag) {
		//文件指针前移一整个T数据
		tempL_I.QuadPart = -(long long)(sizeof(T));
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//用最后一个数据覆盖要删除的数据
		WriteFile(tempHANDLE, &endData, sizeof(T), &written, NULL);
		//移动文件指针到最后一个数据之前
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
		//截断文件
		SetEndOfFile(tempHANDLE);
	}
	CloseHandle(tempHANDLE);
	--T::mCount;
	return 1;

}
