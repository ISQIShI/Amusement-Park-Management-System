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
public:
	//��ֵ��¼�ܸ���
	static UINT mCount;
	void RechargeAdd();
	void RechargeModify();
	void RechargeDelete();
};