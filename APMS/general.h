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

//设置全局变量，接受应用程序的当前实例的句柄
extern _In_ HINSTANCE hInstance;
//屏幕最大宽度
extern int defScreenWidth;
//屏幕最大高度
extern int defScreenHeight;
//主窗口默认宽度
extern int defMainWndWidth;
//主窗口默认高度
extern int defMainWndHeight;


//打开我的github项目页面
void OpenMyGitHubProjectPage();