#pragma once
#include"Time.h"

class Trade {
public:
	//交易ID
	TCHAR mID[tradeID];
	//交易金额
	UINT mMoney;
	//进行交易的用户名
	TCHAR mUserName[actUserName];
	//获取收入的设备ID
	TCHAR mDevID[devID];
	//交易时间
	Time mTime;

	//交易记录总个数
	static UINT mCount;
	//增加交易记录
};

