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
	//���ݶ�ȡ
	
	//�Զ�������ʽ��ȡ��������
	static void File_Read_binary_Trade();
	//�Զ�������ʽ��ȡ�û�����
	static void File_Read_binary_User();
	//�Զ�������ʽ��ȡ�豸����
	static void File_Read_binary_Device();

	//����д��
	
	//�Զ�������ʽ����д�뽻������
	static void File_Write_binary_Trade();
	//�Զ�������ʽ����д���û�����
	static void File_Write_binary_User();
	//�Զ�������ʽ����д���豸����
	static void File_Write_binary_Device();
	
};