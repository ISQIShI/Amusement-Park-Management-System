#pragma once
#include"general.h"
#include"Time.h"

class Recharge {
private:
	//��ֵ���û���
	TCHAR mUserName[actUserName];
	//��ֵ���
	UINT mMoney;
	//��ֵʱ��
	Time mTime;
	//��ֵ��¼�ܸ���
	static UINT mCount;
public:
	void RechargeAdd();
	void RechargeModify();
	void RechargeDelete();
};