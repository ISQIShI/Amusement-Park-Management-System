#pragma once
#include"Permission.h"
#include"Time.h"

class Account {
public:
	//�û��ǳ�
	TCHAR mName[actName];
	//�û���
	TCHAR mUserName[actUserName];
	//�û�����
	TCHAR mPasswd[actPasswd];
	//�û�Ȩ��
	Permission mPer;
	//�û����
	UINT mCredit;
	//�û�ע��ʱ��
	Time mRegTime;
	//�û��ܸ���
	static UINT mCount;
public:
	//�����û�
	static bool ActSearch(LPCTSTR userName, Account * const act = NULL);
	//�����û�
	static bool ActAdd(const Account & act);
	//�޸��û�
	static bool ActModify(const Account& act);
	//ɾ���û�
	static bool ActDelete(LPCTSTR userName);
	//��Ʊ
	void BuyTicket();
	//��ֵ
	void Recharge();
	//����
	void Withdraw();
};

