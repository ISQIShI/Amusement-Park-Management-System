#include"Trade.h"

Trade::Trade(){}
Trade::Trade(int money,Time time,char u_id[], char d_id[]) :m_money(money), m_time(time) {
	strcpy_s(user_id, u_id);
	strcpy_s(device_id, d_id);
}