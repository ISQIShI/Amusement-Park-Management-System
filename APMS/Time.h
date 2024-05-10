#pragma once
#include"general.h"
#include <tchar.h>

class Time {
public:
	//日期（年月日）
	TCHAR mDate[timeDate];
	//时刻（时分秒）
	TCHAR mMoment[timeMoment];
};