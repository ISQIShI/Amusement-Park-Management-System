#pragma once
#include"Time.h"

class Trade {
public:
	//����ID
	TCHAR mID[tradeID];
	//���׽��
	UINT mMoney;
	//���н��׵��û���
	TCHAR mUserName[actUserName];
	//��ȡ������豸ID
	TCHAR mDevID[devID];
	//����ʱ��
	Time mTime;

	//���׼�¼�ܸ���
	static UINT mCount;
	//���ӽ��׼�¼
};

