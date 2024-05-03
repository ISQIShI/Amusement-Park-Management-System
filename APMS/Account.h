#pragma once
#include"general.h"
//账户名称的长度
#define actName 10
//用户名的长度
#define actUserName 10
//密码的长度
#define actPasswd 10

class Account {
private:
	TCHAR mName[actName];
	TCHAR mUserName[actUserName];
	TCHAR mPasswd[actPasswd];
	Permission mPer;
	Time mRegTime;
	UINT mCredit;
	static UINT mCount;
public:
	void ActAdd();
	void ActModify();
	void ActDelete();
};

