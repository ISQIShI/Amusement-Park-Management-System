#include"Menu.h"

//��̬��Ա�����Ķ���
vector<Trade> Menu::Menu_Trade_Data;
vector<User> Menu::Menu_User_Data;
vector<Device> Menu::Menu_Device_Data;
short Menu::Menu_Choice = 0;
short Menu::Menu_Flag = 0;
short Menu::Menu_Confirm = 0;
bool Menu::Menu_Consume_Is_Sync = 1;
bool Menu::Menu_User_Is_Sync = 1;
bool Menu::Menu_Device_Is_Sync = 1;

//�����˵�����
void Menu::Menu_Main() {
	Menu_Flag = 0;
	system("cls");
	cout << "*************************" << endl;
	cout << "*     ����԰����ϵͳ\t*" << endl;
	cout << "*\t1.���Ѽ�¼\t*" << endl;
	cout << "*\t2.�������\t*" << endl;
	cout << "*\t3.�û���Ϣ\t*" << endl;
	cout << "*\t4.�豸��Ϣ\t*" << endl;
	cout << "*\t0.�˳�ϵͳ\t*" << endl;
	cout << "*************************" << endl<<endl;
	cout << "�����빦��ǰ�������Խ�����һ������" << endl;
	//����goto�������������󷵻�
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:Menu::Menu_Exit(); break;
	case 1:thread(Menu::Menu_Consume).detach(); break;
	case 2:thread(Menu::Menu_Income).detach(); break;
	case 3:thread(Menu::Menu_User).detach(); break;
	case 4:thread(Menu::Menu_Device).detach(); break;
	default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_Consume() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      ���Ѽ�¼\t\t*" << endl;
	cout << "*\t1.��ʾ\t\t*" << endl;
	cout << "*\t2.����\t\t*" << endl;
	cout << "*\t3.�޸�\t\t*" << endl;
	cout << "*\t4.����\t\t*" << endl;
	cout << "*\t0.����\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "�����빦��ǰ�������Խ�����һ������" << endl;
	//����goto�������������󷵻�
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_Consume_Display).detach(); break;
	case 2:thread(Menu::Menu_Consume_Add).detach(); break;
	case 3:thread(Menu::Menu_Consume_Modify).detach(); break;
	case 4:thread(Menu::Menu_Consume_Save).detach(); break;
	default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_Income() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      �������\t\t*" << endl;
	cout << "*\t1.��ʾ\t\t*" << endl;
	cout << "*\t2.��ѯ\t\t*" << endl;
	cout << "*\t3.����\t\t*" << endl;
	cout << "*\t0.����\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "�����빦��ǰ�������Խ�����һ������" << endl;
	//����goto�������������󷵻�
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_Income_Display).detach(); break;
	case 2:thread(Menu::Menu_Income_Search).detach(); break;
	case 3:thread(Menu::Menu_Income_Sort).detach(); break;
	default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_User() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      �û���Ϣ\t\t*" << endl;
	cout << "*\t1.��ʾ\t\t*" << endl;
	cout << "*\t2.����\t\t*" << endl;
	cout << "*\t3.�޸�\t\t*" << endl;
	cout << "*\t4.����\t\t*" << endl;
	cout << "*\t0.����\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "�����빦��ǰ�������Խ�����һ������" << endl;
	//����goto�������������󷵻�
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_User_Display).detach(); break;
	case 2:thread(Menu::Menu_User_Add).detach(); break;
	case 3:thread(Menu::Menu_User_Modify).detach(); break;
	case 4:thread(Menu::Menu_User_Save).detach(); break;
	default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
	}
}

void Menu::Menu_Device() {
	Menu_Flag = 1;
	system("cls");
	cout << "*************************" << endl;
	cout << "*      �豸��Ϣ\t\t*" << endl;
	cout << "*\t1.��ʾ\t\t*" << endl;
	cout << "*\t2.����\t\t*" << endl;
	cout << "*\t3.�޸�\t\t*" << endl;
	cout << "*\t4.����\t\t*" << endl;
	cout << "*\t0.����\t\t*" << endl;
	cout << "*************************" << endl << endl;
	cout << "�����빦��ǰ�������Խ�����һ������" << endl;
	//����goto�������������󷵻�
	KeyboardInput_MenuChoice:
	cin >> Menu_Choice;
	switch (Menu_Choice) {
	case 0:thread(Menu::Menu_Return).detach(); break;
	case 1:thread(Menu::Menu_Device_Display).detach(); break;
	case 2:thread(Menu::Menu_Device_Add).detach(); break;
	case 3:thread(Menu::Menu_Device_Modify).detach(); break;
	case 4:thread(Menu::Menu_Device_Save).detach(); break;
	default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
	}
}

//�˳�ϵͳ
void Menu::Menu_Exit() {
	//�˳�����ǰ�Զ����潻������
	//�����и�СBUG�����ʹ���߲���Ҫ�������˳�������ֱ�ӵ���رճ��򣬾Ͳ����Զ������ļ��������ڵ�һ��ʹ�ÿ���̨�������û�кܺõĽ���취
	if (!Menu_Consume_Is_Sync)File::File_Write_binary_Trade();
	if (!Menu_User_Is_Sync)File::File_Write_binary_User();
	if (!Menu_Device_Is_Sync)File::File_Write_binary_Device();
	exit(0);
}

//���ظ����˵�
void Menu::Menu_Return() {
	switch (Menu_Flag) {
	case 1:thread(Menu::Menu_Main).detach(); break;
	case 2:thread(Menu::Menu_Consume).detach(); break;
	case 3:thread(Menu::Menu_Income).detach(); break;
	case 4:thread(Menu::Menu_User).detach(); break;
	case 5:thread(Menu::Menu_Device).detach(); break;
	}
}

//���Ѽ�¼---����

void Menu::Menu_Consume_Display(){
	Menu_Flag = 2;
	system("cls");
	cout << left << setfill(' ') << setw(14) <<"��¼��ţ�" 
		 << setw(14) << "���ѽ�"
		 << setw(Time_Date + 4) << "�������ڣ�" 
		 << setw(Time_Moment + 4) <<"����ʱ�̣�"
		 << setw(User_Id + 4) << "������ID��"
		 << "�豸��ţ�" << endl;
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
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Consume_Add(){
	Menu_Flag = 2;
	system("cls");
	int money;
	char u_id[User_Id], d_id[Device_Id];
	Time time;
	cout << "���������ѽ��" << endl;
	cin >> money;
	cout << "��������������(��ʽΪ year-month-day ����2023-08-23)" << endl;
	cin >> time.m_date;
	cout << "����������ʱ��(��ʽΪ year-month-day ����15:30:00)" << endl;
	cin >> time.m_moment;
	cout << "������������ID(" << User_Id - 1 << "λ�ַ�)" <<endl;
	cin >> u_id;
	cout << "�����������豸���(" << Device_Id - 1 << "λ�ַ�)" << endl;
	cin >> d_id;
	cout << "��ȷ���Ƿ��������Ѽ�¼��(1Ϊȷ�ϣ�0Ϊȡ��)" << endl;
	cin >> Menu_Confirm;
	if (Menu_Confirm) {
		Trade trade(money, time, u_id, d_id);
		Menu_Trade_Data.push_back(trade);
		Menu::Menu_Consume_Is_Sync = 0;
	}
	cout << endl;
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Consume_Modify(){
	Menu_Flag = 2;
	system("cls");
	if (Menu_Trade_Data.size() == 0) {
		cout << "��ǰ���Ѽ�¼Ϊ�գ���������һ�����Ѽ�¼" << endl;
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
	else {
		int record_id;
		//�Ƚ����Ѽ�¼ȫ�����
		cout << left << setfill(' ') << setw(14) << "��¼��ţ�"
			<< setw(14) << "���ѽ�"
			<< setw(Time_Date + 4) << "�������ڣ�"
			<< setw(Time_Moment + 4) << "����ʱ�̣�"
			<< setw(User_Id + 4) << "������ID��"
		    << "�豸��ţ�" << endl;
		for (int i = 0; i < Menu_Trade_Data.size(); ++i) {
			cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
				 << setw(14) << Menu_Trade_Data[i].m_money
				 << setw(Time_Date + 4) << Menu_Trade_Data[i].m_time.m_date
				 << setw(Time_Moment + 4) << Menu_Trade_Data[i].m_time.m_moment
				 << setw(User_Id + 4) << Menu_Trade_Data[i].user_id
			     << Menu_Trade_Data[i].device_id << endl;
		}
		cout << "\n��������Ҫ�޸ĵ����Ѽ�¼�ı��\n";
		cin >> record_id;
		while (record_id<1 || record_id>Menu_Trade_Data.size()) {
			cout << "������ı�Ų����ڣ�����������\n";
			cin >> record_id;
		}
		cout << "��ѡ��Ҫ�޸ĵ�ѡ��\n" << "1.���ѽ�� 2.�������� 3.����ʱ�� 4.������ID 5.�豸��� 6.ɾ���ü�¼ 0.�����޸�" << endl;
	KeyboardInput_MenuChoice:
		cin >> Menu_Choice;
		switch (Menu_Choice) {
		case 0:break;
		case 1:cout << "�������޸ĺ�����ѽ��" << endl; cin >> Menu_Trade_Data[record_id - 1].m_money; Menu::Menu_Consume_Is_Sync = 0; break;
		case 2:cout << "�������޸ĺ����������" << endl; cin >> Menu_Trade_Data[record_id - 1].m_time.m_date; Menu::Menu_Consume_Is_Sync = 0; break;
		case 3:cout << "�������޸ĺ������ʱ��" << endl; cin >> Menu_Trade_Data[record_id - 1].m_time.m_moment; Menu::Menu_Consume_Is_Sync = 0; break;
		case 4:cout << "�������޸ĺ��������ID" << endl; cin >> Menu_Trade_Data[record_id - 1].user_id; Menu::Menu_Consume_Is_Sync = 0; break;
		case 5:cout << "�������޸ĺ���豸���" << endl; cin >> Menu_Trade_Data[record_id - 1].device_id; Menu::Menu_Consume_Is_Sync = 0; break;
		case 6:Menu_Trade_Data.erase(Menu_Trade_Data.begin() + record_id - 1); cout << "�ü�¼��ɾ��" << endl; Menu::Menu_Consume_Is_Sync = 0; break;
		default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
		}
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
}

void Menu::Menu_Consume_Save() {
	Menu_Flag = 2;
	system("cls");
	if (Menu::Menu_Consume_Is_Sync) {
		cout << "����δ�޸����Ѽ�¼�����豣��" << endl;
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
	else {
		cout << "��ȷ���Ƿ񱣴��������Ѽ�¼���޸ģ�(1Ϊȷ�ϣ�0Ϊȡ��)" << endl;
		cin >> Menu_Confirm;
		if (Menu_Confirm) {
			File::File_Write_binary_Trade();
			Menu_Consume_Is_Sync = 1;
			cout << "�ѳɹ�����" <<endl;
		}
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
}

//�������---����
//д��Щ����ʱ�Ѿ���������һ�棬�ʲ������Ż����Ա�����ʽʵ�ֹ��ܣ���ʡʱ��
void Menu::Menu_Income_Display(){
	Menu_Flag = 3;
	system("cls");
	char date[Time_Date];
	cout << "��������Ҫ�鿴������(��ʽΪ year-month-day ����2023-08-23)" << endl;
	cin >> date;
	//�Ȱ���ʱֵȫ����Ϊ0
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		Menu_Device_Data[i].m_income = 0;
	}
	//����������������ͬ�ļ�¼
	for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
		if (!strcmp(Menu_Trade_Data[x].m_time.m_date, date)) {
			//�������¼�ı����ͬ���豸
			for (int y = 0; y < Menu_Device_Data.size(); ++y) {
				if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
					//������ʱֵ
					Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
					break;
				}
			}
		}
	}
	cout << date << " �ĸ��豸�������Ϊ��\n";
	cout << left << setfill(' ') << setw(14) << "�豸��ţ�" << setw(31) << "�豸���ƣ�" << "�豸���룺" << endl;
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		cout << left << setfill(' ') << setw(14) << Menu_Device_Data[i].m_id << setw(31)<< Menu_Device_Data[i].m_name << Menu_Device_Data[i].m_income << endl;
	}
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Income_Search(){
	Menu_Flag = 3;
	system("cls");
	cout << "��ѡ����Ҫ��ѯ�ķ�Χ(1.ĳ���豸 2.����԰)\n";
	cin >> Menu_Choice;
	while(Menu_Choice != 1 && Menu_Choice != 2) {
			cout << "����������������������" << endl;
			cin >> Menu_Choice;
	}
	char date[Time_Date];
	cout << "��������Ҫ�鿴������(��ʽΪ year-month-day ����2023-08-23)" << endl;
	cin >> date;
	//�Ȱ���ʱֵȫ����Ϊ0
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		Menu_Device_Data[i].m_income = 0;
	}
	//����������������ͬ�ļ�¼
	for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
		if (!strcmp(Menu_Trade_Data[x].m_time.m_date, date)) {
			//�������¼�ı����ͬ���豸
			for (int y = 0; y < Menu_Device_Data.size(); ++y) {
				if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
					//������ʱֵ
					Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
					break;
				}
			}
		}
	}

	if (Menu_Choice == 1) {
		char device_id[Device_Id];
		cout << "��������Ҫ��ѯ���豸���" << endl;
		cin >> device_id;
		for (int y = 0; y < Menu_Device_Data.size(); ++y) {
			if (!strcmp(device_id, Menu_Device_Data[y].m_id)) {
				cout << "���豸��" << date << "������Ϊ��" << Menu_Device_Data[y].m_income << endl;
				break;
			}
		}
	}
	else if (Menu_Choice == 2) {
		int all_income=0;
		for (int y = 0; y < Menu_Device_Data.size(); ++y) {
			all_income += Menu_Device_Data[y].m_income;
		}
		cout << "����԰��" << date << "��������Ϊ��" << all_income << endl;
	}
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}


bool Menu::Menu_Income_Compare(Device device_1,Device device_2) {
	return device_1.m_income > device_2.m_income;
}

void Menu::Menu_Income_Sort() {
	Menu_Flag = 3;
	system("cls");
	cout << "��ѡ�������ʱ�����(1.��ʱ�� 2.������)\n";
	cin >> Menu_Choice;
	while (Menu_Choice != 1 && Menu_Choice != 2) {
		cout << "����������������������" << endl;
		cin >> Menu_Choice;
	}
	if (Menu_Choice == 1) {
		char date_begin[Time_Date];
		char date_end[Time_Date];
		cout << "��������ʼ����(��ʽΪ year-month-day ����2023-08-23)" << endl;
		cin >> date_begin;
		cout << "��������ֹ����(��ʽΪ year-month-day ����2023-08-23)" << endl;
		cin >> date_end;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			Menu_Device_Data[i].m_income = 0;
		}
		//����������������ͬ�ļ�¼
		for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
			if (strcmp(Menu_Trade_Data[x].m_time.m_date, date_begin)>=0&& strcmp(Menu_Trade_Data[x].m_time.m_date, date_end) <= 0) {
				//�������¼�ı����ͬ���豸
				for (int y = 0; y < Menu_Device_Data.size(); ++y) {
					if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
						//������ʱֵ
						Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
						break;
					}
				}
			}
		}
		sort(Menu_Device_Data.begin(), Menu_Device_Data.end(), Menu_Income_Compare);
		cout << "�� "<<date_begin << " �� " << date_end <<" �ĸ��豸�������Ϊ��\n";
		cout << left << setfill(' ') << setw(14) << "�豸��ţ�" << setw(31) << "�豸���ƣ�" << "�豸���룺" << endl;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			cout << left << setfill(' ') << setw(14) << Menu_Device_Data[i].m_id << setw(31) << Menu_Device_Data[i].m_name << Menu_Device_Data[i].m_income << endl;
		}
	}
	else if (Menu_Choice == 2) {
		char date[Time_Date];
		cout << "����������(��ʽΪ year-month-day ����2023-08-23)" << endl;
		cin >> date;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			Menu_Device_Data[i].m_income = 0;
		}
		//����������������ͬ�ļ�¼
		for (int x = 0; x < Menu_Trade_Data.size(); ++x) {
			if (!strcmp(Menu_Trade_Data[x].m_time.m_date, date)) {
				//�������¼�ı����ͬ���豸
				for (int y = 0; y < Menu_Device_Data.size(); ++y) {
					if (!strcmp(Menu_Trade_Data[x].device_id, Menu_Device_Data[y].m_id)) {
						//������ʱֵ
						Menu_Device_Data[y].m_income += Menu_Trade_Data[x].m_money;
						break;
					}
				}
			}
		}
		sort(Menu_Device_Data.begin(), Menu_Device_Data.end(), Menu_Income_Compare);
		cout << date << " �ĸ��豸�������Ϊ��\n";
		cout << left << setfill(' ') << setw(14) << "�豸��ţ�" << setw(31) << "�豸���ƣ�" << "�豸���룺" << endl;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			cout << left << setfill(' ') << setw(14) << Menu_Device_Data[i].m_id << setw(31) << Menu_Device_Data[i].m_name << Menu_Device_Data[i].m_income << endl;
		}
	}
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}


//�û���Ϣ---����
void Menu::Menu_User_Display() {
	Menu_Flag = 4;
	system("cls");
	cout << left << setfill(' ') << setw(14) << "��¼��ţ�"
		 << setw(User_Id + 4) << "�û�ID��"
		 << "�û����ƣ�" << endl;
	for (int i = 0; i < Menu_User_Data.size(); ++i) {
		cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
			 << setw(User_Id + 4) << Menu_User_Data[i].m_id 
			 << Menu_User_Data[i].m_name << endl;
	}
	cout << endl;
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_User_Add() {
	Menu_Flag = 4;
	system("cls");
	char id[User_Id],name[User_Name];
	cout << "�������û�ID(" << User_Id - 1 << "λ�ַ�)" << endl;
	cin >> id;
	cout << "�������û�����(������" << User_Name - 1 << "λ�ַ�)" << endl;
	cin >> name;
	cout << "��ȷ���Ƿ��������û���(1Ϊȷ�ϣ�0Ϊȡ��)" << endl;
	cin >> Menu_Confirm;
	if (Menu_Confirm) {
		User user(id, name);
		Menu_User_Data.push_back(user);
		Menu::Menu_User_Is_Sync = 0;
	}
	cout << endl;
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_User_Modify() {
	Menu_Flag = 4;
	system("cls");
	if (Menu_User_Data.size() == 0) {
		cout << "��ǰ�û���ϢΪ�գ���������һ���û�" << endl;
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
	else {
		int record_id;
		//�Ƚ��û���Ϣȫ�����
		cout << left << setfill(' ') << setw(14) << "��¼��ţ�"
			 << setw(User_Id + 4) << "�û�ID��"
			 << "�û����ƣ�" << endl;
		for (int i = 0; i < Menu_User_Data.size(); ++i) {
			cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
				 << setw(User_Id + 4) << Menu_User_Data[i].m_id
				 << Menu_User_Data[i].m_name << endl;
		}
		cout << "\n��������Ҫ�޸ĵ��û���Ϣ�ı��\n";
		cin >> record_id;
		while (record_id<1 || record_id>Menu_User_Data.size()) {
			cout << "������ı�Ų����ڣ�����������\n";
			cin >> record_id;
		}
		cout << "��ѡ��Ҫ�޸ĵ�ѡ��\n" << "1.�û�ID 2.�û����� 3.ɾ�����û� 0.�����޸�" << endl;
	KeyboardInput_MenuChoice:
		cin >> Menu_Choice;
		switch (Menu_Choice) {
		case 0:break;
		case 1:cout << "�������޸ĺ���û�ID" << endl; cin >> Menu_User_Data[record_id - 1].m_id; Menu::Menu_User_Is_Sync = 0; break;
		case 2:cout << "�������޸ĺ���û�����" << endl; cin >> Menu_User_Data[record_id - 1].m_name; Menu::Menu_User_Is_Sync = 0; break;
		case 3:Menu_User_Data.erase(Menu_User_Data.begin() + record_id - 1); cout << "���û���ɾ��" << endl; Menu::Menu_User_Is_Sync = 0; break;
		default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
		}
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
}

void Menu::Menu_User_Save() {
	Menu_Flag = 4;
	system("cls");
	if (Menu::Menu_User_Is_Sync) {
		cout << "����δ�޸��û���Ϣ�����豣��" << endl;
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
	else {
		cout << "��ȷ���Ƿ񱣴������û���Ϣ���޸ģ�(1Ϊȷ�ϣ�0Ϊȡ��)" << endl;
		cin >> Menu_Confirm;
		if (Menu_Confirm) {
			File::File_Write_binary_User();
			Menu_User_Is_Sync = 1;
			cout << "�ѳɹ�����" << endl;
		}
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
}


//�豸��Ϣ---����
void Menu::Menu_Device_Display() {
	Menu_Flag = 5;
	system("cls");
	cout << left << setfill(' ') << setw(14) << "��¼��ţ�"
		 << setw(Device_Id + 4) << "�豸��ţ�"
		 << setw(Device_Name + 4) << "�豸���ƣ�"
		 << "������Ա��"  << endl;
	for (int i = 0; i < Menu_Device_Data.size(); ++i) {
		cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
			 << setw(Device_Id + 4) << Menu_Device_Data[i].m_id
			 << setw(Device_Name + 4) << Menu_Device_Data[i].m_name
			 << Menu_Device_Data[i].m_admin << endl;
	}
	cout << endl;
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Device_Add() {
	Menu_Flag = 5;
	system("cls");
	char id[Device_Id], name[Device_Name],admin[Device_Admin];
	cout << "�������豸���(" << Device_Id - 1 << "λ�ַ�)" << endl;
	cin >> id;
	cout << "�������豸����(������" << Device_Name - 1 << "λ�ַ�)" << endl;
	cin >> name;
	cout << "�����������Ա(������" << Device_Admin - 1 << "λ�ַ�)" << endl;
	cin >> admin;
	cout << "��ȷ���Ƿ��������豸��(1Ϊȷ�ϣ�0Ϊȡ��)" << endl;
	cin >> Menu_Confirm;
	if (Menu_Confirm) {
		Device device(id, name, admin);
		Menu_Device_Data.push_back(device);
		Menu::Menu_Device_Is_Sync = 0;
	}
	cout << endl;
	system("pause");
	//����ִ����Ϸ��ظ����˵�
	thread(Menu::Menu_Return).detach();
}

void Menu::Menu_Device_Modify() {
	Menu_Flag = 5;
	system("cls");
	if (Menu_Device_Data.size() == 0) {
		cout << "��ǰ�豸��ϢΪ�գ���������һ���豸" << endl;
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
	else {
		int record_id;
		//�Ƚ��豸��Ϣȫ�����
		cout << left << setfill(' ') << setw(14) << "��¼��ţ�"
			 << setw(Device_Id + 4) << "�豸��ţ�"
			 << setw(Device_Name + 4) << "�豸���ƣ�"
			 << "������Ա��" << endl;
		for (int i = 0; i < Menu_Device_Data.size(); ++i) {
			cout << right << setfill('0') << setw(8) << i + 1 << "      " << left << setfill(' ')
				 << setw(Device_Id + 4) << Menu_Device_Data[i].m_id
				 << setw(Device_Name + 4) << Menu_Device_Data[i].m_name
				 << Menu_Device_Data[i].m_admin << endl;
		}
		cout << "\n��������Ҫ�޸ĵ��豸��Ϣ�ı��\n";
		cin >> record_id;
		while (record_id<1 || record_id>Menu_Device_Data.size()) {
			cout << "������ı�Ų����ڣ�����������\n";
			cin >> record_id;
		}
		cout << "��ѡ��Ҫ�޸ĵ�ѡ��\n" << "1.�豸��� 2.�豸���� 3.������Ա 4.ɾ���ü�¼ 0.�����޸�" << endl;
	KeyboardInput_MenuChoice:
		cin >> Menu_Choice;
		switch (Menu_Choice) {
		case 0:break;
		case 1:cout << "�������޸ĺ���豸���" << endl; cin >> Menu_Device_Data[record_id - 1].m_id; Menu::Menu_Device_Is_Sync = 0; break;
		case 2:cout << "�������޸ĺ���豸����" << endl; cin >> Menu_Device_Data[record_id - 1].m_name; Menu::Menu_Device_Is_Sync = 0; break;
		case 3:cout << "�������޸ĺ�Ĺ�����Ա" << endl; cin >> Menu_Device_Data[record_id - 1].m_admin; Menu::Menu_Device_Is_Sync = 0; break;
		case 4:Menu_Device_Data.erase(Menu_Device_Data.begin() + record_id - 1); cout << "���豸��ɾ��" << endl; Menu::Menu_Device_Is_Sync = 0; break;
		default:cout << "����������������������" << endl; goto KeyboardInput_MenuChoice;
		}
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
}

void Menu::Menu_Device_Save() {
	Menu_Flag = 5;
	system("cls");
	if (Menu::Menu_Device_Is_Sync) {
		cout << "����δ�޸��豸��Ϣ�����豣��" << endl;
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
	else {
		cout << "��ȷ���Ƿ񱣴������豸��Ϣ���޸ģ�(1Ϊȷ�ϣ�0Ϊȡ��)" << endl;
		cin >> Menu_Confirm;
		if (Menu_Confirm) {
			File::File_Write_binary_Device();
			Menu_Device_Is_Sync = 1;
			cout << "�ѳɹ�����" << endl;
		}
		cout << endl;
		system("pause");
		//����ִ����Ϸ��ظ����˵�
		thread(Menu::Menu_Return).detach();
	}
}