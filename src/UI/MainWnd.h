#ifndef MAIN_WND_H
#define MAIN_WND_H

#include "ProjectHeader.h"

class MainWnd :public WindowImplBase
{
public:
	MainWnd();
	virtual~MainWnd();

public:
	virtual LPCTSTR GetWindowClassName() const;															// 设置程序类名称
	virtual DuiLib::CDuiString GetSkinFile();															// 设置皮肤文件
	virtual CDuiString GetSkinFolder();																    // 设置皮肤文件路径
	virtual void Notify(TNotifyUI& msg);															    // 响应duilib的各种消息

private:
	void OnClickProcess(TNotifyUI& msg);															    // 点击事件处理函数

};


#endif // !MAIN_WND_H
