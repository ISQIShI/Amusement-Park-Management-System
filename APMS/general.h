#pragma once
//#include<Windows.h>
//#include<windowsx.h>
//#include<tchar.h>
//#include<CommCtrl.h>

//WindowsAPI中的数据类型
typedef unsigned int UINT;
typedef unsigned char BYTE;

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
//Trade
#define tradeID 11
//Notification
#define notTitle 21
#define notID 11
#define notContent 201
//Recharge
#define rechargeID 11


//子窗口标识符
#define homePageWndID 1//主页
#define actInfoWndID 2//用户信息
#define devInfoWndID 3//设备信息
#define tradeInfoWndID 4//交易记录（需要权限）

//按钮
#define loginButtonID 101//登录
#define loginConfirmButtonID 102//确认登录
#define registerButtonID 103//注册
#define registerConfirmButtonID 104//确认注册
#define homePageButtonID 105//主页按钮
#define actInfoButtonID 106//用户信息按钮
#define devInfoButtonID 107//设备信息按钮
#define tradeInfoButtonID 108//交易记录按钮
#define exitButtonID 109//退出系统
#define confirmButtonID 110//确认
#define cancelButtonID 111//取消

//编辑框
#define userNameEditID 201//用户名
#define passwdEditID 202//密码
#define actNameEditID 203//用户昵称
#define editActInfoEditID 204//编辑用户信息
#define actPerEditID 205//权限
#define actCreditEditID 206//余额
#define devNameEditID 207//设备名称
#define devIDEditID 208//设备ID
#define devPriceEditID 209//价格
#define devChargeEditID 210//收费
#define devIntroEditID 211//设备介绍
#define tradeIDEditID 212//交易ID
#define tradeMoneyEditID 213//交易金额

//静态文本
#define userNameStaticID 301//用户名
#define passwdStaticID 302//密码
#define actNameStaticID 303//昵称
#define actPerStaticID 304//权限
#define actCreditStaticID 305//余额
#define devNameStaticID 306//设备名称
#define devIDStaticID 307//设备ID
#define devPriceStaticID 308//价格
#define devChargeStaticID 309//收费
#define tradeIDStaticID 310//交易ID
#define tradeMoneyStaticID 311//交易金额
#define tradeTimeAStaticID 312//交易时间A
#define tradeTimeBStaticID 313//交易时间B

//SysLink
#define editActNameSysLinkID 401//编辑用户昵称
#define editPasswdSysLinkID 402//修改密码
#define creditSysLinkID 403//充值/提现
#define logoutSysLinkID 404//注销用户
#define actSaveSysLinkID 405//保存(用户信息)
#define browseActSysLinkID 406//查看所有用户（需要权限）
#define returnSysLinkID 407//返回
#define dataInfoSysLinkID 408//更改数据信息(增加/修改/删除)
#define editDevIntroSysLinkID 409//编辑设备介绍
#define devSaveSysLinkID 410//保存(设备信息)
#define tradeSelectSysLinkID 411//筛选交易记录

//ListView
#define dataInfoListID 501//数据信息列表
#define selectListID 502
#define userNameSelectListID 503
#define devIDSelectListID 504

//组合框
#define userNameComboBoxID 601//用户名
#define devIDComboBoxID 602//设备ID

//时间
#define tradeDateATimeID 701//交易日期A
#define tradeMomentATimeID 702//交易时刻A
#define tradeDateBTimeID 703//交易日期B
#define tradeMomentBTimeID 704//交易时刻B

//UI界面
#define LoginUI 1
#define RegisterUI 2
#define HomeUI 3
#define ActInfoUI 4
#define DevInfoUI 5
#define TradeInfoUI 6

//对话框
#define dialogActAdd 1
#define dialogActModify 2
#define dialogDevAdd 3
#define dialogDevModify 4
#define dialogTradeAdd 5
#define dialogTradeModify 6
#define dialogTradeSelect 7

//字体
#define defSmallFont 1
#define defMidFont 2
#define defLargeFont 3

//各控件坐标
#define homePageButtonCoord_X 0.05
#define homePageButtonCoord_Y 0.125
#define homePageButtonWidth 0.1
#define homePageButtonHeight 0.1


//打开我的github项目页面
void OpenMyGitHubProjectPage();