#pragma once
#include"Time.h"

//����Ϊδ������չԤ���ӿڣ�����ʵ��������

class Recharge {
private:
	//��ֵID
	TCHAR mID[rechargeID];
	//��ֵ���û���
	TCHAR mUserName[actUserName];
	//��ֵ���
	UINT mMoney;
	//��ֵʱ��
	Time mTime;
public:
	//��ֵ��¼�ܸ���
	static UINT mCount;
};