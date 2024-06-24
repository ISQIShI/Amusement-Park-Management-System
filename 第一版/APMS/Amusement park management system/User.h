#pragma once
#include<iostream>
using namespace std;

#define User_Id 11
#define User_Name 31

class User {
	friend class Menu;
private:
	//用户ID
	char m_id[User_Id];
	//用户名称
	char m_name[User_Name];
	//用户权限
public:
	User();
	User(char id[],char name[]);
};