#pragma once
#include"Time.h"
#include"User.h"
#include"Device.h"

class Trade {
	friend class Menu;
	friend class File;
private:
	//交易金额
	int m_money;
	//交易时间
	Time m_time;
	//进行消费的用户ID
	char user_id[User_Id];
	//获得收入的设备编号
	char device_id[Device_Id];
	//构造函数
public:
	//无参默认构造
	Trade();
	//有参构造
	Trade(int money, Time time, char u_id[], char d_id[]);
};

