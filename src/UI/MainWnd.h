#ifndef MAIN_WND_H
#define MAIN_WND_H

#include "ProjectHeader.h"

class MainWnd :public WindowImplBase
{
public:
	MainWnd();
	virtual~MainWnd();

public:
	virtual LPCTSTR GetWindowClassName() const;															// ���ó���������
	virtual DuiLib::CDuiString GetSkinFile();															// ����Ƥ���ļ�
	virtual CDuiString GetSkinFolder();																    // ����Ƥ���ļ�·��
	virtual void Notify(TNotifyUI& msg);															    // ��Ӧduilib�ĸ�����Ϣ

private:
	void OnClickProcess(TNotifyUI& msg);															    // ����¼�������

};


#endif // !MAIN_WND_H
