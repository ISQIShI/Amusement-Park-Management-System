#pragma once
#include"Permission.h"
#include"Time.h"

class Account {
public:
	//�û���
	TCHAR mUserName[actUserName];
	//�û�����
	TCHAR mPasswd[actPasswd];
	//�û��ǳ�
	TCHAR mName[actName];
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
	void ActAdd();
	//�޸��û�
	void ActModify();
	//ɾ���û�
	void ActDelete();
	//��Ʊ
	void BuyTicket();
	//��ֵ
	void Recharge();
	//����
	void Withdraw();
};

