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
	virtual void InitWindow();                                                                          // 窗口初始化函数

private:
	void InitControl();																				    // 初始化相关控件指针
	void OnClickProcess(TNotifyUI& msg);															    // 点击事件处理函数
	void OnTextChanged(TNotifyUI& msg);																	// 文本改变时间处理函数
	void OnKillFocus(TNotifyUI& msg);																	// 控件失去焦点处理函数
	void OnSetFocus(TNotifyUI& msg);																	// 控件获得焦点处理函数
	void InitWindowShadow();																			// 初始化窗体阴影
	void AutoCopyToClipboard(const std::string& copy_content);											// 自动将内容拷贝到剪切板

private:
	CWndShadow m_WndShadow;

	CRichEditUI* m_pRichEdit_Input;
	CRichEditUI* m_pRichEdit_Output;
};


#endif // !MAIN_WND_H
