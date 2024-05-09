#pragma once
#include"Permission.h"
#include"Time.h"

class Account {
public:
	//用户昵称
	TCHAR mName[actName];
	//用户名
	TCHAR mUserName[actUserName];
	//用户密码
	TCHAR mPasswd[actPasswd];
	//用户权限
	Permission mPer;
	//用户余额
	UINT mCredit;
	//用户注册时间
	Time mRegTime;
	//用户总个数
	static UINT mCount;
public:
	//查找用户
	static bool ActSearch(LPCTSTR userName, Account * const act = NULL);
	//增加用户
	static bool ActAdd(const Account & act);
	//修改用户
	static bool ActModify(const Account& act);
	//删除用户
	static bool ActDelete(LPCTSTR userName);
	//购票
	void BuyTicket();
	//充值
	void Recharge();
	//提现
	void Withdraw();
};

