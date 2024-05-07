#pragma once
#include"Permission.h"
#include"Time.h"

class Account {
public:
	//用户名
	TCHAR mUserName[actUserName];
	//用户密码
	TCHAR mPasswd[actPasswd];
	//用户昵称
	TCHAR mName[actName];
	//用户权限
	Permission mPer;
	//用户余额
	UINT mCredit;
	//用户注册时间
	Time mRegTime;
	//用户总个数
	static UINT mCount;
public:
	//增加用户
	void ActAdd();
	//修改用户
	void ActModify();
	//删除用户
	void ActDelete();
	//购票
	void BuyTicket();
	//充值
	void Recharge();
	//提现
	void Withdraw();
};

