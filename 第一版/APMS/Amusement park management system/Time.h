#pragma once
#include<string>
using namespace std;

#define Time_Date 11
#define Time_Moment 9

class Time {
	friend class Menu;
	friend class File;
private:
	//���ڣ������գ�
	char m_date[Time_Date];
	//ʱ�̣�ʱ���룩
	char m_moment[Time_Moment];
};
