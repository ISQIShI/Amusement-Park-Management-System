#pragma once
#include<string>
using namespace std;

#define Time_Date 11
#define Time_Moment 9

class Time {
	friend class Menu;
	friend class File;
private:
	//日期（年月日）
	char m_date[Time_Date];
	//时刻（时分秒）
	char m_moment[Time_Moment];
};
