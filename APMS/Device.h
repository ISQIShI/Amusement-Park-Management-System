#pragma once
#include"general.h"

#define devName 10;
#define devID 10;

class Device {
private:
	TCHAR mName[devName];
	TCHAR mID[devID];
	Time mAddTime;
	TCHAR mIntro;
	UINT mCharge;
	static UINT mCount;
};