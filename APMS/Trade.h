#pragma once
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
public:
	//���׼�¼�ܸ���
	static UINT mCount;
	//���ӽ��׼�¼
	void TradeAdd();
	//�޸Ľ��׼�¼
	void TradeModify();
	//ɾ�����׼�¼
	void TradeDelete();
};

