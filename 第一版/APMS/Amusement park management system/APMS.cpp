#include<iostream>
#include<fstream>
#include<windows.h>
#include<vector>
#include<algorithm>
#include<thread>
#include"Menu.h"
using namespace std;


int main() {
	//��ȡ��������
	File::File_Read_binary_Trade();
	//��ȡ�û�����
	File::File_Read_binary_User();
	//��ȡ�豸����
	File::File_Read_binary_Device();
	//�����˵�
	thread(Menu::Menu_Main).detach();
	//�������ߺ����������̣߳���ֹ���߳���ֹ������������ֹ���Ӷ����³�����ֹ
	while (true) {
		this_thread::sleep_for(std::chrono::seconds(60));
	}
	return 0;
	
}