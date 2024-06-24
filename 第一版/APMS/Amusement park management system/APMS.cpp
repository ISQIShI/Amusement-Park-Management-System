#include<iostream>
#include<fstream>
#include<windows.h>
#include<vector>
#include<algorithm>
#include<thread>
#include"Menu.h"
using namespace std;


int main() {
	//读取交易数据
	File::File_Read_binary_Trade();
	//读取用户数据
	File::File_Read_binary_User();
	//读取设备数据
	File::File_Read_binary_Device();
	//打开主菜单
	thread(Menu::Menu_Main).detach();
	//利用休眠函数保活主线程，防止主线程终止引起主进程终止，从而导致程序终止
	while (true) {
		this_thread::sleep_for(std::chrono::seconds(60));
	}
	return 0;
	
}