#pragma once
#include<Windows.h>
#include<windowsx.h>
#include<tchar.h>
#include<CommCtrl.h>
#include<iostream>
#include<thread>
using namespace std; 

//用户操作权限
#define normalPer 0//普通用户
#define superPer 255//最高权限

//各字符串变量的长度
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
//Notification
#define notTitle 21
#define notID 11
#define notContent 201

//打开我的github项目页面
void OpenMyGitHubProjectPage();