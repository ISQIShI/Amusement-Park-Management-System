#pragma once
#include"general.h"
#include"Time.h"

class Device {
private:
	//设备ID
	TCHAR mID[devID];
	//设备名称
	TCHAR mName[devName];
	//设备介绍
	TCHAR mIntro[devIntro];
	//设备收费
	UINT mCharge;
	//增加设备的时间
	Time mAddTime;
public:
	//设备的总个数
	static UINT mCount;
	//增加设备
	void DevAdd();
	//修改设备信息
	void DevModify();
	//删除设备
	void DevDelete();
};