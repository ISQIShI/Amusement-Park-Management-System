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
	//��¼��������
	static vector<Trade> Menu_Trade_Data;
	//��¼�û�����
	static vector<User> Menu_User_Data;
	//��¼�豸����
	static vector<Device> Menu_Device_Data;
	//��Ϊѡ��ı��
	static short Menu_Choice;
	//��Ϊ�˵������ı�� Menu_Flag��ͬ�Ĳ˵�������ͬ�ĸ����˵�
	static short Menu_Flag;
	//��Ϊ�Ƿ�ȷ�ϵı��
	static short Menu_Confirm;
	//��¼���Ѽ�¼�Ƿ����ļ�ͬ��
	static bool Menu_Consume_Is_Sync;
	//��¼�û���Ϣ�Ƿ����ļ�ͬ��
	static bool Menu_User_Is_Sync;
	//��¼�豸��Ϣ�Ƿ����ļ�ͬ��
	static bool Menu_Device_Is_Sync;
public:
	//��ʾ�����˵�����

	//���˵�
	static void Menu_Main();
	//���˵�-���Ѽ�¼
	static void Menu_Consume();
	//���˵�-�������
	static void Menu_Income();
	//���˵�-�û���Ϣ
	static void Menu_User();
	//���˵�-�豸��Ϣ
	static void Menu_Device();

	//���Ѽ�¼---����
	static void Menu_Consume_Display();//��ʾ
	static void Menu_Consume_Add();//����
	static void Menu_Consume_Modify();//�޸�
	static void Menu_Consume_Save();//����

	//�������---����
	static void Menu_Income_Display();//��ʾ
	static void Menu_Income_Search();//��ѯ
	static bool Menu_Income_Compare(Device device_1, Device device_2);
	static void Menu_Income_Sort();//����

	//�û���Ϣ---����
	static void Menu_User_Display();//��ʾ
	static void Menu_User_Add();//����
	static void Menu_User_Modify();//�޸�
	static void Menu_User_Save();//����

	//�豸��Ϣ---����
	static void Menu_Device_Display();//��ʾ
	static void Menu_Device_Add();//����
	static void Menu_Device_Modify();//�޸�
	static void Menu_Device_Save();//����

	//�˳�ϵͳ
	static void Menu_Exit();

	//���ظ����˵�
	static void Menu_Return();
};

