#pragma once
#include"general.h"
//�˻����Ƶĳ���
#define actName 10
//�û����ĳ���
#define actUserName 10
//����ĳ���
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

