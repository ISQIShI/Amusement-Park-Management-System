#include"File.h"

//数据读取

void File::File_Read_binary_Trade() {
	ifstream ifs("Trade.dat", ios::in | ios::binary);
	if (!ifs.is_open()) {  return; }
	for (Trade trade; ifs.read((char*)&trade, sizeof(trade));) {
		Menu::Menu_Trade_Data.push_back(trade);
	}
	ifs.close();
}

void File::File_Read_binary_User() {
	ifstream ifs("User.dat", ios::in | ios::binary);
	if (!ifs.is_open()) { return; }
	for (User user; ifs.read((char*)&user, sizeof(user));) {
		Menu::Menu_User_Data.push_back(user);
	}
	ifs.close();
}

void File::File_Read_binary_Device() {
	ifstream ifs("Device.dat", ios::in | ios::binary);
	if (!ifs.is_open()) { return; }
	for (Device device; ifs.read((char*)&device, sizeof(device));) {
		Menu::Menu_Device_Data.push_back(device);
	}
	ifs.close();
}

//数据写入

void File::File_Write_binary_Trade() {
	ofstream ofs("Trade.dat", ios::out | ios::trunc | ios::binary);
	for (int i = 0; i < Menu::Menu_Trade_Data.size(); ++i) {
		ofs.write((const char*)&Menu::Menu_Trade_Data[i], sizeof(Menu::Menu_Trade_Data[i]));
	}
	ofs.close();
}

void File::File_Write_binary_User() {
	ofstream ofs("User.dat", ios::out | ios::trunc | ios::binary);
	for (int i = 0; i < Menu::Menu_User_Data.size(); ++i) {
		ofs.write((const char*)&Menu::Menu_User_Data[i], sizeof(Menu::Menu_User_Data[i]));
	}
	ofs.close();
}

void File::File_Write_binary_Device() {
	ofstream ofs("Device.dat", ios::out | ios::trunc | ios::binary);
	for (int i = 0; i < Menu::Menu_Device_Data.size(); ++i) {
		ofs.write((const char*)&Menu::Menu_Device_Data[i], sizeof(Menu::Menu_Device_Data[i]));
	}
	ofs.close();
}
