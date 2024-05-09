#include"Account.h"

//��ʼ���ܸ���Ϊ0
UINT Account::mCount = 0;

//�����û�
bool Account::ActSearch(LPCTSTR userName, Account * const act) {
	bool tempflag = 0;//��Ϊ�Ƿ��ҵ��û��ı��
	Account tempAct = {0};//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	//���ļ�
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempAct.mUserName, userName)) {
			tempflag = 1;//�ҵ��û�
			break;
		}
	} while (tempDWORD);
	//�ر��ļ�
	CloseHandle(tempHANDLE);
	//����ҵ��û��ҵ��ú���ʱ�����˽���Account�Ĳ���act����ô����ҵ���Account��Ϣ
	if (tempflag && act != NULL) *act = tempAct;
	return tempflag;
}

//�����û�
bool Account::ActAdd(const Account& act) {
	//���ļ�
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//�趨�ļ�ָ��--�ļ�ĩβ
	LARGE_INTEGER tempL_I;
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//д���ļ�
	DWORD written;
	WriteFile(tempHANDLE, &act, sizeof(Account), &written, NULL);
	//�ر��ļ�
	CloseHandle(tempHANDLE);
	++Account::mCount;
	return 1;
}

//�޸��û�
bool Account::ActModify(const Account& act) {
	bool tempflag = 0;//��Ϊ�Ƿ��ҵ��û��ı��
	Account tempAct = {0};//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	DWORD written = 0;//���ʵ��д����ֽ���
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempAct.mUserName, act.mUserName)) {
			tempflag = 1;
			break;
		}
	} while (tempDWORD);
	if (tempflag) {
		//�ļ�ָ��ǰ��һ����Account����
		LARGE_INTEGER tempL_I;
		tempL_I.QuadPart = -long long(sizeof(Account));
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//д���ļ�
		WriteFile(tempHANDLE, &act, sizeof(Account), &written, NULL);
	}
	CloseHandle(tempHANDLE);
	return 1;
}


//ɾ���û�
bool Account::ActDelete(LPCTSTR userName) {
	bool tempflag = 0;//��Ϊ�Ƿ��ҵ��û��ı��
	Account tempAct = { 0 }, endAct = { 0 };//��Ž�Ҫ��ȡ���û�����
	DWORD tempDWORD = 0;//���ʵ�ʶ�ȡ���ֽ���
	DWORD written = 0;//���ʵ��д����ֽ���
	LARGE_INTEGER tempL_I;
	//���ļ�
	HANDLE tempHANDLE = CreateFile(_T("Account.dat"), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	//�ƶ��ļ�ָ�뵽���һ������
	tempL_I.QuadPart = -long long(sizeof(Account));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//��ȡ���һ������
	ReadFile(tempHANDLE, &endAct, sizeof(Account), &tempDWORD, NULL);
	if (!_tcscmp(endAct.mUserName, userName)) {
		//�ļ�ָ��ǰ��һ����Account����
		SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
		//�ض��ļ�
		SetEndOfFile(tempHANDLE);
		CloseHandle(tempHANDLE);
		--Account::mCount;
		return 1;
	}
	//�ƶ��ļ�ָ�뵽�ļ���ͷ
	tempL_I.QuadPart = 0;
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_BEGIN);
	//Ѱ��Ҫɾ�����û�
	do {
		ReadFile(tempHANDLE, &tempAct, sizeof(Account), &tempDWORD, NULL);//��ȡ�ļ�
		if (!_tcscmp(tempAct.mUserName, userName)) {
			tempflag = 1;//�ҵ��û�
			break;
		}
	} while (tempDWORD);
	//�ļ�ָ��ǰ��һ����Account����
	tempL_I.QuadPart = -long long(sizeof(Account));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_CURRENT);
	//�����һ�����ݸ���Ҫɾ��������
	WriteFile(tempHANDLE, &endAct, sizeof(Account), &written, NULL);
	//�ƶ��ļ�ָ�뵽���һ������
	tempL_I.QuadPart = -long long(sizeof(Account));
	SetFilePointerEx(tempHANDLE, tempL_I, NULL, FILE_END);
	//�ض��ļ�
	SetEndOfFile(tempHANDLE);
	CloseHandle(tempHANDLE);
	--Account::mCount;
	return 1;
}
