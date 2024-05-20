#pragma once
#include"Time.h"

//本类为未来的拓展预留接口，不再实际做功能

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