#pragma once
//#include<Windows.h>
//#include<windowsx.h>
//#include<tchar.h>
//#include<CommCtrl.h>

//WindowsAPI�е���������
typedef unsigned int UINT;
typedef unsigned char BYTE;

//�û�����Ȩ��
#define normalPer 0//��ͨ�û�
#define superPer 255//���Ȩ��

//���ַ��������ĳ���
//Time
#define timeDate 11
#define timeMoment 9
//Account
#define actName 11
#define actUserName 16
#define actPasswd 16
//Device
#define devName 11
#define devID 11
#define devIntro 101
//Trade
#define tradeID 11
//Notification
#define notTitle 21
#define notID 11
#define notContent 201
//Recharge
#define rechargeID 11

//���ҵ�github��Ŀҳ��
void OpenMyGitHubProjectPage();