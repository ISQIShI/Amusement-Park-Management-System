#pragma once
#include"general.h"
#include"Time.h"

class Device {
private:
	//�豸ID
	TCHAR mID[devID];
	//�豸����
	TCHAR mName[devName];
	//�豸����
	TCHAR mIntro[devIntro];
	//�豸�շ�
	UINT mCharge;
	//�����豸��ʱ��
	Time mAddTime;
public:
	//�豸���ܸ���
	static UINT mCount;
	//�����豸
	void DevAdd();
	//�޸��豸��Ϣ
	void DevModify();
	//ɾ���豸
	void DevDelete();
};