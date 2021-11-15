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
	virtual CDuiString GetSkinFolder();																    // 设置皮肤文件路
};


#endif // !MAIN_WND_H
