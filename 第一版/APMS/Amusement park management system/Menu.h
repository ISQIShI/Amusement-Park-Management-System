#pragma once
#include<iostream>
#include<vector>
#include<thread>
#include<algorithm>
#include<iomanip>
#include"File.h"
using namespace std;

class Menu {
	friend class File;
private:
	//记录交易数据
	static vector<Trade> Menu_Trade_Data;
	//记录用户数据
	static vector<User> Menu_User_Data;
	//记录设备数据
	static vector<Device> Menu_Device_Data;
	//作为选择的标记
	static short Menu_Choice;
	//作为菜单级数的标记 Menu_Flag相同的菜单具有相同的父级菜单
	static short Menu_Flag;
	//作为是否确认的标记
	static short Menu_Confirm;
	//记录消费记录是否与文件同步
	static bool Menu_Consume_Is_Sync;
	//记录用户信息是否与文件同步
	static bool Menu_User_Is_Sync;
	//记录设备信息是否与文件同步
	static bool Menu_Device_Is_Sync;
public:
	//显示各级菜单界面

	//主菜单
	static void Menu_Main();
	//主菜单-消费记录
	static void Menu_Consume();
	//主菜单-收入情况
	static void Menu_Income();
	//主菜单-用户信息
	static void Menu_User();
	//主菜单-设备信息
	static void Menu_Device();

	//消费记录---功能
	static void Menu_Consume_Display();//显示
	static void Menu_Consume_Add();//增加
	static void Menu_Consume_Modify();//修改
	static void Menu_Consume_Save();//保存

	//收入情况---功能
	static void Menu_Income_Display();//显示
	static void Menu_Income_Search();//查询
	static bool Menu_Income_Compare(Device device_1, Device device_2);
	static void Menu_Income_Sort();//排序

	//用户信息---功能
	static void Menu_User_Display();//显示
	static void Menu_User_Add();//增加
	static void Menu_User_Modify();//修改
	static void Menu_User_Save();//保存

	//设备信息---功能
	static void Menu_Device_Display();//显示
	static void Menu_Device_Add();//增加
	static void Menu_Device_Modify();//修改
	static void Menu_Device_Save();//保存

	//退出系统
	static void Menu_Exit();

	//返回父级菜单
	static void Menu_Return();
};

