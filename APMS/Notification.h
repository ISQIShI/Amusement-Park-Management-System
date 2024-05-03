#pragma once
#include"general.h"
#include"Time.h"

class Notification {
private:
	//公告的ID
	TCHAR mID[notID];
	//公告的标题
	TCHAR mTitle[notTitle];
	//公告的内容
	TCHAR mContent[notContent];
	//公告的发布时间
	Time mPostTime;
	//公告的总个数
	static UINT mCount;
public:
	//增加公告
	void NotAdd();
	//修改公告
	void NotModify();
	//删除公告
	void NotDelete();
};