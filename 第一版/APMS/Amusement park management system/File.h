#pragma once
#include<iostream>
#include<fstream>
#include<vector>
#include"Trade.h"
#include"Menu.h"
using namespace std;

class File {
	friend class Menu;
public:
	//数据读取
	
	//以二进制形式读取交易数据
	static void File_Read_binary_Trade();
	//以二进制形式读取用户数据
	static void File_Read_binary_User();
	//以二进制形式读取设备数据
	static void File_Read_binary_Device();

	//数据写入
	
	//以二进制形式覆盖写入交易数据
	static void File_Write_binary_Trade();
	//以二进制形式覆盖写入用户数据
	static void File_Write_binary_User();
	//以二进制形式覆盖写入设备数据
	static void File_Write_binary_Device();
	
};