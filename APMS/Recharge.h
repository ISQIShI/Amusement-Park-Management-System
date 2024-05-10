#pragma once
#include"Time.h"

class Recharge {
private:
	//充值ID
	TCHAR mID[rechargeID];
	//充值的用户名
	TCHAR mUserName[actUserName];
	//充值金额
	UINT mMoney;
	//充值时间
	Time mTime;
public:
	//充值记录总个数
	static UINT mCount;
};