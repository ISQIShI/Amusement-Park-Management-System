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


//�Ӵ��ڱ�ʶ��
#define homePageWndID 1//��ҳ
#define actInfoWndID 2//�û���Ϣ
#define devInfoWndID 3//�豸��Ϣ
#define tradeInfoWndID 4//���׼�¼����ҪȨ�ޣ�

//��ť
#define loginButtonID 101//��¼
#define loginConfirmButtonID 102//ȷ�ϵ�¼
#define registerButtonID 103//ע��
#define registerConfirmButtonID 104//ȷ��ע��
#define homePageButtonID 105//��ҳ��ť
#define actInfoButtonID 106//�û���Ϣ��ť
#define devInfoButtonID 107//�豸��Ϣ��ť
#define tradeInfoButtonID 108//���׼�¼��ť
#define exitButtonID 109//�˳�ϵͳ
#define confirmButtonID 110//ȷ��
#define cancelButtonID 111//ȡ��

//�༭��
#define userNameEditID 201//�û���
#define passwdEditID 202//����
#define actNameEditID 203//�û��ǳ�
#define editActInfoEditID 204//�༭�û���Ϣ
#define actPerEditID 205//Ȩ��
#define actCreditEditID 206//���
#define devNameEditID 207//�豸����
#define devIDEditID 208//�豸ID
#define devPriceEditID 209//�۸�
#define devChargeEditID 210//�շ�
#define devIntroEditID 211//�豸����
#define tradeIDEditID 212//����ID
#define tradeMoneyEditID 213//���׽��

//��̬�ı�
#define userNameStaticID 301//�û���
#define passwdStaticID 302//����
#define actNameStaticID 303//�ǳ�
#define actPerStaticID 304//Ȩ��
#define actCreditStaticID 305//���
#define devNameStaticID 306//�豸����
#define devIDStaticID 307//�豸ID
#define devPriceStaticID 308//�۸�
#define devChargeStaticID 309//�շ�
#define tradeIDStaticID 310//����ID
#define tradeMoneyStaticID 311//���׽��
#define tradeTimeAStaticID 312//����ʱ��A
#define tradeTimeBStaticID 313//����ʱ��B

//SysLink
#define editActNameSysLinkID 401//�༭�û��ǳ�
#define editPasswdSysLinkID 402//�޸�����
#define creditSysLinkID 403//��ֵ/����
#define logoutSysLinkID 404//ע���û�
#define actSaveSysLinkID 405//����(�û���Ϣ)
#define browseActSysLinkID 406//�鿴�����û�����ҪȨ�ޣ�
#define returnSysLinkID 407//����
#define dataInfoSysLinkID 408//����������Ϣ(����/�޸�/ɾ��)
#define editDevIntroSysLinkID 409//�༭�豸����
#define devSaveSysLinkID 410//����(�豸��Ϣ)
#define tradeSelectSysLinkID 411//ɸѡ���׼�¼

//ListView
#define dataInfoListID 501//������Ϣ�б�
#define selectListID 502
#define userNameSelectListID 503
#define devIDSelectListID 504

//��Ͽ�
#define userNameComboBoxID 601//�û���
#define devIDComboBoxID 602//�豸ID

//ʱ��
#define tradeDateATimeID 701//��������A
#define tradeMomentATimeID 702//����ʱ��A
#define tradeDateBTimeID 703//��������B
#define tradeMomentBTimeID 704//����ʱ��B

//UI����
#define LoginUI 1
#define RegisterUI 2
#define HomeUI 3
#define ActInfoUI 4
#define DevInfoUI 5
#define TradeInfoUI 6

//�Ի���
#define dialogActAdd 1
#define dialogActModify 2
#define dialogDevAdd 3
#define dialogDevModify 4
#define dialogTradeAdd 5
#define dialogTradeModify 6
#define dialogTradeSelect 7

//����
#define defSmallFont 1
#define defMidFont 2
#define defLargeFont 3

//���ؼ�����
#define homePageButtonCoord_X 0.05
#define homePageButtonCoord_Y 0.125
#define homePageButtonWidth 0.1
#define homePageButtonHeight 0.1


//���ҵ�github��Ŀҳ��
void OpenMyGitHubProjectPage();