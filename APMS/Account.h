#pragma once
#include"Permission.h"
#include"Time.h"

class Account {
public:
	//�û��ǳ�
	TCHAR mName[actName];
	//�û���
	TCHAR mID[actUserName];
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
	//��Ʊ
	void BuyTicket();
	//��ֵ
	void Recharge();
	//����
	void Withdraw();
};

