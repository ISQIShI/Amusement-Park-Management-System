#pragma once
#include<iostream>
using namespace std;

#define User_Id 11
#define User_Name 31

class User {
	friend class Menu;
private:
	//�û�ID
	char m_id[User_Id];
	//�û�����
	char m_name[User_Name];
	//�û�Ȩ��
public:
	User();
	User(char id[],char name[]);
};