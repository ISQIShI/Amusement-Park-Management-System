#pragma once
#include"Time.h"

class Notification {
private:
	//�����ID
	TCHAR mID[notID];
	//����ı���
	TCHAR mTitle[notTitle];
	//���������
	TCHAR mContent[notContent];
	//����ķ���ʱ��
	Time mPostTime;
public:
	//������ܸ���
	static UINT mCount;
};