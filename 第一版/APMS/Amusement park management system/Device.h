#pragma once
#include<iostream>
using namespace std;

#define Device_Id 11
#define Device_Name 31//��Ϊһ�������ַ�ռ2�ֽڣ��ʿռ�����
#define Device_Admin 31

class Device {
	friend class Menu;
private:
	//�豸���
	char m_id[Device_Id];
	//�豸����
	char m_name[Device_Name];
	//�豸�Ĺ�����Ա
	char m_admin[Device_Admin];
	//��ʱ������豸�����룬ֻΪ��������������µĹ��ܶ����壬��Ϊ������һ���ˣ������Ǻ�����չ����
	int m_income;
public:
	Device();
	Device(char id[], char name[],char admin[]);
};