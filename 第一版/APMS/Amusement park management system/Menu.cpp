#include"Menu.h"

//静态成员函数的定义
vector<Trade> Menu::Menu_Trade_Data;
vector<User> Menu::Menu_User_Data;
vector<Device> Menu::Menu_Device_Data;
short Menu::Menu_Choice = 0;
short Menu::Menu_Flag = 0;
short Menu::Menu_Confirm = 0;
bool Menu::Menu_Consume_Is_Sync = 1;
bool Menu::Menu_User_Is_Sync = 1;
bool Menu::Menu_Device_Is_Sync = 1;

//各级菜单界面
void Menu::Menu_Main() {
	Menu_Flag = 0;
	system("cls");
	cout << "*************************" << endl;
	cout << "*     游乐园管理系统\t*" << endl;
	cout << "*\t1.消费记录\t*" << endl;
	cout << "*\t2.收入情况\t*" << endl;
	cout << "*\t3.用户信息\t*" << endl;
	cout << "*\t4.设备信息\t*" << endl;
	cout << "*\t0.退出系统\t*" << endl;
	cout << "*************************" << endl<<endl;
	cout << "请输入功能前的数字以进行下一步操作" << endl;
	//留下goto标记用于输入错误返回
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:Menu::Menu_Exit(); break;
	case 1:thread(Menu::Menu_Consume).detach(); break;
	case 2:thread(Menu::Menu_Income).detach(); break;
	case 3:thread(Menu::Menu_User).detach(); break;
	case 4:thread(Menu::Menu_Device).detach(); break;
	default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_Consume() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      消费记录\t\t*" << endl;
	cout << "*\t1.显示\t\t*" << endl;
	cout << "*\t2.增加\t\t*" << endl;
	cout << "*\t3.修改\t\t*" << endl;
	cout << "*\t4.保存\t\t*" << endl;
	cout << "*\t0.返回\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "请输入功能前的数字以进行下一步操作" << endl;
	//留下goto标记用于输入错误返回
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_Consume_Display).detach(); break;
	case 2:thread(Menu::Menu_Consume_Add).detach(); break;
	case 3:thread(Menu::Menu_Consume_Modify).detach(); break;
	case 4:thread(Menu::Menu_Consume_Save).detach(); break;
	default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_Income() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      收入情况\t\t*" << endl;
	cout << "*\t1.显示\t\t*" << endl;
	cout << "*\t2.查询\t\t*" << endl;
	cout << "*\t3.排序\t\t*" << endl;
	cout << "*\t0.返回\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "请输入功能前的数字以进行下一步操作" << endl;
	//留下goto标记用于输入错误返回
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_Income_Display).detach(); break;
	case 2:thread(Menu::Menu_Income_Search).detach(); break;
	case 3:thread(Menu::Menu_Income_Sort).detach(); break;
	default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_User() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      用户信息\t\t*" << endl;
	cout << "*\t1.显示\t\t*" << endl;
	cout << "*\t2.增加\t\t*" << endl;
	cout << "*\t3.修改\t\t*" << endl;
	cout << "*\t4.保存\t\t*" << endl;
	cout << "*\t0.返回\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "请输入功能前的数字以进行下一步操作" << endl;
	//留下goto标记用于输入错误返回
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_User_Display).detach(); break;
	case 2:thread(Menu::Menu_User_Add).detach(); break;
	case 3:thread(Menu::Menu_User_Modify).detach(); break;
	case 4:thread(Menu::Menu_User_Save).detach(); break;
	default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_Device() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      设备信息\t\t*" << endl;
	cout << "*\t1.显示\t\t*" << endl;
	cout << "*\t2.增加\t\t*" << endl;
	cout << "*\t3.修改\t\t*" << endl;
	cout << "*\t4.保存\t\t*" << endl;
	cout << "*\t0.返回\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "请输入功能前的数字以进行下一步操作" << endl;
	//留下goto标记用于输入错误返回
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_Device_Display).detach(); break;
	case 2:thread(Menu::Menu_Device_Add).detach(); break;
	case 3:thread(Menu::Menu_Device_Modify).detach(); break;
	case 4:thread(Menu::Menu_Device_Save).detach(); break;
	default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
	}
}

//退出系统
void Menu::Menu_Exit() {
	//退出程序前自动保存交易数据
	//这里有个小BUG，如果使用者不按要求正常退出，而是直接点×关闭程序，就不会自动保存文件，至少在第一版使用控制台的情况下没有很好的解决办法
	if (!Menu_Consume_Is_Sync)File::File_Write_binary_Trade();
	if (!Menu_User_Is_Sync)File::File_Write_binary_User();
	if (!Menu_Device_Is_Sync)File::File_Write_binary_Device();
	exit(0);
}

//返回父级菜单
void Menu::Menu_Return() {
	switch (Menu_Flag) {
	case 1:thread(Menu::Menu_Main).detach(); break;
	case 2:thread(Menu::Menu_Consume).detach(); break;
	case 3:thread(Menu::Menu_Income).detach(); break;
	case 4:thread(Menu::Menu_User).detach(); break;
	case 5:thread(Menu::Menu_Device).detach(); break;
	}
}

//消费记录---功能

void Menu::Menu_Consume_Display(){
	Menu_Flag = 2;
	system("cls");
	cout << left << setfill(' ') << setw(14) <<"记录编号：" 
		 << setw(14) << "消费金额："
		 << setw(Time_Date + 4) << "消费日期：" 
		 << setw(Time_Moment + 4) <<"消费时刻："
		 << setw(User_Id + 4) << "消费者ID："
		 << "设备编号：" << endl;
	for (int i = 0; i < Menu_Trade_Data.size(); ++i) {
		cout << right << setfill('0') << setw(8) << i + 1 << "      " << left <<setfill(' ')
			 << setw(14) << Menu_Trade_Data[i].m_money 
			 << setw(Time_Date+4) << Menu_Trade_Data[i].m_time.m_date 
			 << setw(Time_Moment+4) << Menu_Trade_Data[i].m_time.m_moment 
			 << setw(User_Id+4) << Menu_Trade_Data[i].user_id 
			 << Menu_Trade_Data[i].device_id << endl;
	}
	cout << endl;
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Consume_Add(){
	Menu_Flag = 2;
	system("cls");
	int money;
	char u_id[User_Id], d_id[Device_Id];
	Time time;
	cout << "请输入消费金额" << endl;
	cin >> money;
	cout << "请输入消费日期(格式为 year-month-day 例：2023-08-23)" << endl;
	cin >> time.m_date;
	cout << "请输入消费时刻(格式为 year-month-day 例：15:30:00)" << endl;
	cin >> time.m_moment;
	cout << "请输入消费者ID(" << User_Id - 1 << "位字符)" <<endl;
	cin >> u_id;
	cout << "请输入游乐设备编号(" << Device_Id - 1 << "位字符)" << endl;
	cin >> d_id;
	cout << "请确认是否增加消费记录？(1为确认，0为取消)" << endl;
	cin >> Menu_Confirm;
	if (Menu_Confirm) {
		Trade trade(money, time, u_id, d_id);
		Menu_Trade_Data.push_back(trade);
		Menu::Menu_Consume_Is_Sync = 0;
	}
	cout << endl;
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Consume_Modify(){
	Menu_Flag = 2;
	system("cls");
	if (Menu_Trade_Data.size() == 0) {
		cout << "当前消费记录为空，请先增加一个消费记录" << endl;
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
	else {
		int record_id;
		//先将消费记录全部输出
		cout << left << setfill(' ') << setw(14) << "记录编号："
			<< setw(14) << "消费金额："
			<< setw(Time_Date + 4) << "消费日期："
			<< setw(Time_Moment + 4) << "消费时刻："
			<< setw(User_Id + 4) << "消费者ID："
		    << "设备编号：" << endl;
		for (int i = 0; i < Menu_Trade_Data.size(); ++i) {
			cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
				 << setw(14) << Menu_Trade_Data[i].m_money
				 << setw(Time_Date + 4) << Menu_Trade_Data[i].m_time.m_date
				 << setw(Time_Moment + 4) << Menu_Trade_Data[i].m_time.m_moment
				 << setw(User_Id + 4) << Menu_Trade_Data[i].user_id
			     << Menu_Trade_Data[i].device_id << endl;
		}
		cout << "\n请输入您要修改的消费记录的编号\n";
		cin >> record_id;
		while (record_id<1 || record_id>Menu_Trade_Data.size()) {
			cout << "您输入的编号不存在，请重新输入\n";
			cin >> record_id;
		}
		cout << "请选择要修改的选项\n" << "1.消费金额 2.消费日期 3.消费时刻 4.消费者ID 5.设备编号 6.删除该记录 0.放弃修改" << endl;
	KeyboardInput_MenuChoice:
		cin >> Menu_Choice;
		switch (Menu_Choice) {
		case 0:break;
		case 1:cout << "请输入修改后的消费金额" << endl; cin >> Menu_Trade_Data[record_id - 1].m_money; Menu::Menu_Consume_Is_Sync = 0; break;
		case 2:cout << "请输入修改后的消费日期" << endl; cin >> Menu_Trade_Data[record_id - 1].m_time.m_date; Menu::Menu_Consume_Is_Sync = 0; break;
		case 3:cout << "请输入修改后的消费时刻" << endl; cin >> Menu_Trade_Data[record_id - 1].m_time.m_moment; Menu::Menu_Consume_Is_Sync = 0; break;
		case 4:cout << "请输入修改后的消费者ID" << endl; cin >> Menu_Trade_Data[record_id - 1].user_id; Menu::Menu_Consume_Is_Sync = 0; break;
		case 5:cout << "请输入修改后的设备编号" << endl; cin >> Menu_Trade_Data[record_id - 1].device_id; Menu::Menu_Consume_Is_Sync = 0; break;
		case 6:Menu_Trade_Data.erase(Menu_Trade_Data.begin() + record_id - 1); cout << "该记录已删除" << endl; Menu::Menu_Consume_Is_Sync = 0; break;
		default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
		}
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
}

void Menu::Menu_Consume_Save() {
	Menu_Flag = 2;
	system("cls");
	if (Menu::Menu_Consume_Is_Sync) {
		cout << "您尚未修改消费记录，无需保存" << endl;
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
	else {
		cout << "请确认是否保存您对消费记录的修改？(1为确认，0为取消)" << endl;
		cin >> Menu_Confirm;
		if (Menu_Confirm) {
			File::File_Write_binary_Trade();
			Menu_Consume_Is_Sync = 1;
			cout << "已成功保存" <<endl;
		}
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
}

//收入情况---功能
//写这些功能时已决定放弃第一版，故不考虑优化，以暴力方式实现功能，节省时间
void Menu::Menu_Income_Display(){
	Menu_Flag = 3;
	system("cls");
	char date[Time_Date];
	cout << "请输入您要查看的日期(格式为 year-month-day 例：2023-08-23)" << endl;
	cin >> date;
	//先把临时值全部置为0
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		Menu_Device_Data[i].m_income = 0;
	}
	//查找与输入日期相同的记录
	for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
		if (!strcmp(Menu_Trade_Data[x].m_time.m_date, date)) {
			//查找与记录的编号相同的设备
			for (int y = 0; y < Menu_Device_Data.size(); ++y) {
				if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
					//增加临时值
					Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
					break;
				}
			}
		}
	}
	cout << date << " 的各设备收入情况为：\n";
	cout << left << setfill(' ') << setw(14) << "设备编号：" << setw(31) << "设备名称：" << "设备收入：" << endl;
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		cout << left << setfill(' ') << setw(14) << Menu_Device_Data[i].m_id << setw(31)<< Menu_Device_Data[i].m_name << Menu_Device_Data[i].m_income << endl;
	}
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Income_Search(){
	Menu_Flag = 3;
	system("cls");
	cout << "请选择您要查询的范围(1.某个设备 2.游乐园)\n";
	cin >> Menu_Choice;
	while(Menu_Choice != 1 && Menu_Choice != 2) {
			cout << "您的输入有误，请重新输入" << endl;
			cin >> Menu_Choice;
	}
	char date[Time_Date];
	cout << "请输入您要查看的日期(格式为 year-month-day 例：2023-08-23)" << endl;
	cin >> date;
	//先把临时值全部置为0
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		Menu_Device_Data[i].m_income = 0;
	}
	//查找与输入日期相同的记录
	for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
		if (!strcmp(Menu_Trade_Data[x].m_time.m_date, date)) {
			//查找与记录的编号相同的设备
			for (int y = 0; y < Menu_Device_Data.size(); ++y) {
				if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
					//增加临时值
					Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
					break;
				}
			}
		}
	}

	if (Menu_Choice == 1) {
		char device_id[Device_Id];
		cout << "请输入您要查询的设备编号" << endl;
		cin >> device_id;
		for (int y = 0; y < Menu_Device_Data.size(); ++y) {
			if (!strcmp(device_id, Menu_Device_Data[y].m_id)) {
				cout << "该设备在" << date << "的收入为：" << Menu_Device_Data[y].m_income << endl;
				break;
			}
		}
	}
	else if (Menu_Choice == 2) {
		int all_income=0;
		for (int y = 0; y < Menu_Device_Data.size(); ++y) {
			all_income += Menu_Device_Data[y].m_income;
		}
		cout << "游乐园在" << date << "的总收入为：" << all_income << endl;
	}
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}


bool Menu::Menu_Income_Compare(Device device_1,Device device_2) {
	return device_1.m_income > device_2.m_income;
}

void Menu::Menu_Income_Sort() {
	Menu_Flag = 3;
	system("cls");
	cout << "请选择排序的时间规则(1.按时段 2.按日期)\n";
	cin >> Menu_Choice;
	while (Menu_Choice != 1 && Menu_Choice != 2) {
		cout << "您的输入有误，请重新输入" << endl;
		cin >> Menu_Choice;
	}
	if (Menu_Choice == 1) {
		char date_begin[Time_Date];
		char date_end[Time_Date];
		cout << "请输入起始日期(格式为 year-month-day 例：2023-08-23)" << endl;
		cin >> date_begin;
		cout << "请输入终止日期(格式为 year-month-day 例：2023-08-23)" << endl;
		cin >> date_end;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			Menu_Device_Data[i].m_income = 0;
		}
		//查找与输入日期相同的记录
		for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
			if (strcmp(Menu_Trade_Data[x].m_time.m_date, date_begin)>=0&& strcmp(Menu_Trade_Data[x].m_time.m_date, date_end) <= 0) {
				//查找与记录的编号相同的设备
				for (int y = 0; y < Menu_Device_Data.size(); ++y) {
					if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
						//增加临时值
						Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
						break;
					}
				}
			}
		}
		sort(Menu_Device_Data.begin(), Menu_Device_Data.end(), Menu_Income_Compare);
		cout << "从 "<<date_begin << " 到 " << date_end <<" 的各设备收入情况为：\n";
		cout << left << setfill(' ') << setw(14) << "设备编号：" << setw(31) << "设备名称：" << "设备收入：" << endl;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			cout << left << setfill(' ') << setw(14) << Menu_Device_Data[i].m_id << setw(31) << Menu_Device_Data[i].m_name << Menu_Device_Data[i].m_income << endl;
		}
	}
	else if (Menu_Choice == 2) {
		char date[Time_Date];
		cout << "请输入日期(格式为 year-month-day 例：2023-08-23)" << endl;
		cin >> date;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			Menu_Device_Data[i].m_income = 0;
		}
		//查找与输入日期相同的记录
		for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
			if (!strcmp(Menu_Trade_Data[x].m_time.m_date, date)) {
				//查找与记录的编号相同的设备
				for (int y = 0; y < Menu_Device_Data.size(); ++y) {
					if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
						//增加临时值
						Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
						break;
					}
				}
			}
		}
		sort(Menu_Device_Data.begin(), Menu_Device_Data.end(), Menu_Income_Compare);
		cout << date << " 的各设备收入情况为：\n";
		cout << left << setfill(' ') << setw(14) << "设备编号：" << setw(31) << "设备名称：" << "设备收入：" << endl;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			cout << left << setfill(' ') << setw(14) << Menu_Device_Data[i].m_id << setw(31) << Menu_Device_Data[i].m_name << Menu_Device_Data[i].m_income << endl;
		}
	}
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}


//用户信息---功能
void Menu::Menu_User_Display() {
	Menu_Flag = 4;
	system("cls");
	cout << left << setfill(' ') << setw(14) << "记录编号："
		 << setw(User_Id + 4) << "用户ID："
		 << "用户名称：" << endl;
	for (int i = 0; i < Menu_User_Data.size(); ++i) {
		cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
			 << setw(User_Id + 4) << Menu_User_Data[i].m_id 
			 << Menu_User_Data[i].m_name << endl;
	}
	cout << endl;
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_User_Add() {
	Menu_Flag = 4;
	system("cls");
	char id[User_Id],name[User_Name];
	cout << "请输入用户ID(" << User_Id - 1 << "位字符)" << endl;
	cin >> id;
	cout << "请输入用户名称(不超过" << User_Name - 1 << "位字符)" << endl;
	cin >> name;
	cout << "请确认是否增加新用户？(1为确认，0为取消)" << endl;
	cin >> Menu_Confirm;
	if (Menu_Confirm) {
		User user(id, name);
		Menu_User_Data.push_back(user);
		Menu::Menu_User_Is_Sync = 0;
	}
	cout << endl;
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_User_Modify() {
	Menu_Flag = 4;
	system("cls");
	if (Menu_User_Data.size() == 0) {
		cout << "当前用户信息为空，请先增加一个用户" << endl;
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
	else {
		int record_id;
		//先将用户信息全部输出
		cout << left << setfill(' ') << setw(14) << "记录编号："
			 << setw(User_Id + 4) << "用户ID："
			 << "用户名称：" << endl;
		for (int i = 0; i < Menu_User_Data.size(); ++i) {
			cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
				 << setw(User_Id + 4) << Menu_User_Data[i].m_id
				 << Menu_User_Data[i].m_name << endl;
		}
		cout << "\n请输入您要修改的用户信息的编号\n";
		cin >> record_id;
		while (record_id<1 || record_id>Menu_User_Data.size()) {
			cout << "您输入的编号不存在，请重新输入\n";
			cin >> record_id;
		}
		cout << "请选择要修改的选项\n" << "1.用户ID 2.用户名称 3.删除该用户 0.放弃修改" << endl;
	KeyboardInput_MenuChoice:
		cin >> Menu_Choice;
		switch (Menu_Choice) {
		case 0:break;
		case 1:cout << "请输入修改后的用户ID" << endl; cin >> Menu_User_Data[record_id - 1].m_id; Menu::Menu_User_Is_Sync = 0; break;
		case 2:cout << "请输入修改后的用户名称" << endl; cin >> Menu_User_Data[record_id - 1].m_name; Menu::Menu_User_Is_Sync = 0; break;
		case 3:Menu_User_Data.erase(Menu_User_Data.begin() + record_id - 1); cout << "该用户已删除" << endl; Menu::Menu_User_Is_Sync = 0; break;
		default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
		}
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
}

void Menu::Menu_User_Save() {
	Menu_Flag = 4;
	system("cls");
	if (Menu::Menu_User_Is_Sync) {
		cout << "您尚未修改用户信息，无需保存" << endl;
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
	else {
		cout << "请确认是否保存您对用户信息的修改？(1为确认，0为取消)" << endl;
		cin >> Menu_Confirm;
		if (Menu_Confirm) {
			File::File_Write_binary_User();
			Menu_User_Is_Sync = 1;
			cout << "已成功保存" << endl;
		}
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
}


//设备信息---功能
void Menu::Menu_Device_Display() {
	Menu_Flag = 5;
	system("cls");
	cout << left << setfill(' ') << setw(14) << "记录编号："
		 << setw(Device_Id + 4) << "设备编号："
		 << setw(Device_Name + 4) << "设备名称："
		 << "管理人员："  << endl;
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
			 << setw(Device_Id + 4) << Menu_Device_Data[i].m_id
			 << setw(Device_Name + 4) << Menu_Device_Data[i].m_name
			 << Menu_Device_Data[i].m_admin << endl;
	}
	cout << endl;
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Device_Add() {
	Menu_Flag = 5;
	system("cls");
	char id[Device_Id], name[Device_Name],admin[Device_Admin];
	cout << "请输入设备编号(" << Device_Id - 1 << "位字符)" << endl;
	cin >> id;
	cout << "请输入设备名称(不超过" << Device_Name - 1 << "位字符)" << endl;
	cin >> name;
	cout << "请输入管理人员(不超过" << Device_Admin - 1 << "位字符)" << endl;
	cin >> admin;
	cout << "请确认是否增加新设备？(1为确认，0为取消)" << endl;
	cin >> Menu_Confirm;
	if (Menu_Confirm) {
		Device device(id, name, admin);
		Menu_Device_Data.push_back(device);
		Menu::Menu_Device_Is_Sync = 0;
	}
	cout << endl;
	system("pause");
	//功能执行完毕返回父级菜单
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Device_Modify() {
	Menu_Flag = 5;
	system("cls");
	if (Menu_Device_Data.size() == 0) {
		cout << "当前设备信息为空，请先增加一个设备" << endl;
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
	else {
		int record_id;
		//先将设备信息全部输出
		cout << left << setfill(' ') << setw(14) << "记录编号："
			 << setw(Device_Id + 4) << "设备编号："
			 << setw(Device_Name + 4) << "设备名称："
			 << "管理人员：" << endl;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
				 << setw(Device_Id + 4) << Menu_Device_Data[i].m_id
				 << setw(Device_Name + 4) << Menu_Device_Data[i].m_name
				 << Menu_Device_Data[i].m_admin << endl;
		}
		cout << "\n请输入您要修改的设备信息的编号\n";
		cin >> record_id;
		while (record_id<1 || record_id>Menu_Device_Data.size()) {
			cout << "您输入的编号不存在，请重新输入\n";
			cin >> record_id;
		}
		cout << "请选择要修改的选项\n" << "1.设备编号 2.设备名称 3.管理人员 4.删除该记录 0.放弃修改" << endl;
	KeyboardInput_MenuChoice:
		cin >> Menu_Choice;
		switch (Menu_Choice) {
		case 0:break;
		case 1:cout << "请输入修改后的设备编号" << endl; cin >> Menu_Device_Data[record_id - 1].m_id; Menu::Menu_Device_Is_Sync = 0; break;
		case 2:cout << "请输入修改后的设备名称" << endl; cin >> Menu_Device_Data[record_id - 1].m_name; Menu::Menu_Device_Is_Sync = 0; break;
		case 3:cout << "请输入修改后的管理人员" << endl; cin >> Menu_Device_Data[record_id - 1].m_admin; Menu::Menu_Device_Is_Sync = 0; break;
		case 4:Menu_Device_Data.erase(Menu_Device_Data.begin() + record_id - 1); cout << "该设备已删除" << endl; Menu::Menu_Device_Is_Sync = 0; break;
		default:cout << "您的输入有误，请重新输入" << endl; goto KeyboardInput_MenuChoice;
		}
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
}

void Menu::Menu_Device_Save() {
	Menu_Flag = 5;
	system("cls");
	if (Menu::Menu_Device_Is_Sync) {
		cout << "您尚未修改设备信息，无需保存" << endl;
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
	else {
		cout << "请确认是否保存您对设备信息的修改？(1为确认，0为取消)" << endl;
		cin >> Menu_Confirm;
		if (Menu_Confirm) {
			File::File_Write_binary_Device();
			Menu_Device_Is_Sync = 1;
			cout << "已成功保存" << endl;
		}
		cout << endl;
		system("pause");
		//功能执行完毕返回父级菜单
		thread(Menu::Menu_Return).detach();
	}
}