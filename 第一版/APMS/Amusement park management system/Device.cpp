#include"Device.h"

Device::Device() {}
Device::Device(char id[], char name[],char admin[]):m_income(0) {
	strcpy_s(m_id, id);
	strcpy_s(m_name, name);
	strcpy_s(m_admin, admin);
}