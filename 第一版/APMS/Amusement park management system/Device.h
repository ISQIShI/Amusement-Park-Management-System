#pragma once
#include<iostream>
using namespace std;

#define Device_Id 11
#define Device_Name 31//因为一个中文字符占2字节，故空间设大点
#define Device_Admin 31

class Device {
	friend class Menu;
private:
	//设备编号
	char m_id[Device_Id];
	//设备名称
	char m_name[Device_Name];
	//设备的管理人员
	char m_admin[Device_Admin];
	//临时储存该设备的收入，只为服务“收入情况”下的功能而定义，因为放弃第一版了，不考虑后续扩展性了
	int m_income;
public:
	Device();
	Device(char id[], char name[],char admin[]);
};