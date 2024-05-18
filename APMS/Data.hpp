#pragma once
#include<Windows.h>

template<class T>
class Data {
public:
	//��������
	static bool DataSearch(LPCTSTR fillname,LPCTSTR id, T* const data = NULL);
	//��������
	static bool DataAdd(LPCTSTR fillname,const T& data);
	//�޸�����
	static bool DataModify(LPCTSTR fillname, const T& data);
	//ɾ������
	static bool DataDelete(LPCTSTR fillname, LPCTSTR id);
};

//��������
template<class T>
bool Data<T>::DataSearch(LPCTSTR fillname, LPCTSTR id, T* const data) {
	bool tempflag = 0;//��Ϊ�Ƿ��ҵ��û��ı��
	T tempData = { 0 };//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	//���ļ�
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempData, sizeof(T), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempData.mID, id)) {
			tempflag = 1;//�ҵ�����
			break;
		}
	} while (tempDWORD);
	//�ر��ļ�
	CloseHandle(tempHANDLE);
	//����ҵ�T�����ҵ��ú���ʱ�����˽���T�Ĳ���data����ô����ҵ���T��Ϣ
	if (tempflag && data != NULL) *data = tempData;
	return tempflag;
}

//��������
template<class T>
bool Data<T>::DataAdd(LPCTSTR fillname, const T& data) {
	//���ļ�
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//�趨�ļ�ָ��--�ļ�ĩβ
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//д���ļ�
	DWORD written;
	WriteFile(tempHANDLE, &data, sizeof(T), &written, NULL);
	//�ر��ļ�
	CloseHandle(tempHANDLE);
	++T::mCount;
	return 1;
}

//�޸�����
template<class T>
bool Data<T>::DataModify(LPCTSTR fillname, const T& data) {
	bool tempflag = 0;//��Ϊ�Ƿ��ҵ����ݵı��
	T tempData = { 0 };//��Ž�Ҫ��ȡ������
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	DWORD written = 0;//���ʵ��д����ֽ���
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempData, sizeof(T), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempData.mID, data.mID)) {
			tempflag = 1;//�ҵ�����
			break;
		}
	} while (tempDWORD);
	if (tempflag) {
		//�ļ�ָ��ǰ��һ����T����
		LARGE_INTEGER tempL_I;
		tempL_I.QuadPart = -(long long)(sizeof(T));
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//����д������
		WriteFile(tempHANDLE, &data, sizeof(T), &written, NULL);
	}
	CloseHandle(tempHANDLE);
	return 1;
}

//ɾ������
template<class T>
bool Data<T>::DataDelete(LPCTSTR fillname, LPCTSTR id) {
	bool tempflag = 0;//��Ϊ�Ƿ��ҵ����ݵı��
	T tempData = { 0 }, endData = { 0 };//��Ž�Ҫ��ȡ������
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	DWORD written = 0;//���ʵ��д����ֽ���
	LARGE_INTEGER tempL_I;
	//���ļ�
	HANDLE tempHANDLE = CreateFile(fillname, GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//�ƶ��ļ�ָ�뵽���һ������֮ǰ
	tempL_I.QuadPart = -(long long)(sizeof(T));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//��ȡ���һ������
	ReadFile(tempHANDLE, &endData, sizeof(T), &tempDWORD, NULL);
	//�����һ�����ݼ�ΪҪɾ��������ʱ,ֱ�ӽض��ļ�
	if (!_tcscmp(endData.mID, id)) {
		//�ļ�ָ��ǰ��һ����T����
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//�ض��ļ�
		SetEndOfFile(tempHANDLE);
		CloseHandle(tempHANDLE);
		--T::mCount;
		return 1;
	}
	//�ƶ��ļ�ָ�뵽�ļ���ͷ
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	//Ѱ��Ҫɾ��������
	do {
		ReadFile(tempHANDLE, &tempData, sizeof(T), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempData.mID, id)) {
			tempflag = 1;//�ҵ�����
			break;
		}
	} while (tempDWORD);
	if (tempflag) {
		//�ļ�ָ��ǰ��һ����T����
		tempL_I.QuadPart = -(long long)(sizeof(T));
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//�����һ�����ݸ���Ҫɾ��������
		WriteFile(tempHANDLE, &endData, sizeof(T), &written, NULL);
		//�ƶ��ļ�ָ�뵽���һ������֮ǰ
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
		//�ض��ļ�
		SetEndOfFile(tempHANDLE);
	}
	CloseHandle(tempHANDLE);
	--T::mCount;
	return 1;

}
