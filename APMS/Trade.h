#pragma once
#include"general.h"
#include"Time.h"

class Trade {
private:
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
public:
	//���ӽ��׼�¼
	void TradeAdd();
	//�޸Ľ��׼�¼
	void TradeModify();
	//ɾ�����׼�¼
	void TradeDelete();
};

