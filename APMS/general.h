#pragma once
#include<Windows.h>
#include<tchar.h>
#include<CommCtrl.h>
#include<iostream>
#include<thread>
using namespace std; 

//Time
#define timeDate 11
#define timeMoment 9
//Account
#define actName 11
#define actUserName 11
#define actPasswd 11
//Device
#define devName 11
#define devID 11
#define devIntro 101
//Notification
#define notTitle 21
#define notID 11
#define notContent 201

//����ȫ�ֱ���������Ӧ�ó���ĵ�ǰʵ���ľ��
extern _In_ HINSTANCE hInstance;
//��Ļ�����
extern int defScreenWidth;
//��Ļ���߶�
extern int defScreenHeight;
//������Ĭ�Ͽ��
extern int defMainWndWidth;
//������Ĭ�ϸ߶�
extern int defMainWndHeight;


//���ҵ�github��Ŀҳ��
void OpenMyGitHubProjectPage();