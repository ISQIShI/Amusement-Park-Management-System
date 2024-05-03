#pragma once
#include"general.h"
//日期的长度
#define timeDate 11
//时刻的长度
#define timeMoment 9

class Time {
	TCHAR mDate[timeDate];
	TCHAR mMoment[timeMoment];
};