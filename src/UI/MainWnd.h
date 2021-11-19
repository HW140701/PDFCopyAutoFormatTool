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
	virtual void InitWindow();                                                                          // ���ڳ�ʼ������

private:
	void InitControl();																				    // ��ʼ����ؿؼ�ָ��
	void OnClickProcess(TNotifyUI& msg);															    // ����¼�������
	void OnTextChanged(TNotifyUI& msg);																	// �ı��ı�ʱ�䴦����
	void OnKillFocus(TNotifyUI& msg);																	// �ؼ�ʧȥ���㴦����
	void OnSetFocus(TNotifyUI& msg);																	// �ؼ���ý��㴦����
	void InitWindowShadow();																			// ��ʼ��������Ӱ
	void AutoCopyToClipboard(const std::string& copy_content);											// �Զ������ݿ��������а�

private:
	CWndShadow m_WndShadow;

	CRichEditUI* m_pRichEdit_Input;
	CRichEditUI* m_pRichEdit_Output;
};


#endif // !MAIN_WND_H
