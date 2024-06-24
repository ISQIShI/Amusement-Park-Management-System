#pragma once
#include"Time.h"
#include"User.h"
#include"Device.h"

class Trade {
	friend class Menu;
	friend class File;
private:
	//���׽��
	int m_money;
	//����ʱ��
	Time m_time;
	//�������ѵ��û�ID
	char user_id[User_Id];
	//���������豸���
	char device_id[Device_Id];
	//���캯��
public:
	//�޲�Ĭ�Ϲ���
	Trade();
	//�вι���
	Trade(int money, Time time, char u_id[], char d_id[]);
};

