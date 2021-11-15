#include "MainWnd.h"

/*----- 按钮Button的名称 -----*/
const TCHAR* const Str_Btn_Min = _T("Btn_Min");
const TCHAR* const Str_Btn_Max = _T("Btn_Max");
const TCHAR* const Str_Btn_Close = _T("Btn_Close");

MainWnd::MainWnd()
{
}

MainWnd::~MainWnd()
{
}

LPCTSTR MainWnd::GetWindowClassName() const
{
	return _T("MainWnd");
}

DuiLib::CDuiString MainWnd::GetSkinFile()
{
	return _T("MainWnd.xml");
}

CDuiString MainWnd::GetSkinFolder()
{
	return PathUtils::GetSkinDirectory().c_str();
}

void MainWnd::Notify(TNotifyUI& msg)
{
	// 点击事件消息响应
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClickProcess(msg);
	}

	WindowImplBase::Notify(msg);
}

void MainWnd::OnClickProcess(TNotifyUI& msg)
{
	// 最小化
	if (_tcsicmp(msg.pSender->GetName(), Str_Btn_Min) == 0)
	{
#if defined(UNDER_CE)
		::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
	}
	// 最大化
	else if (_tcsicmp(msg.pSender->GetName(), Str_Btn_Max) == 0)
	{

	}
	// 关闭程序
	else if (_tcsicmp(msg.pSender->GetName(), Str_Btn_Close) == 0)
	{
		::SendMessage(this->GetHWND(), WM_CLOSE, NULL, NULL);
		PostQuitMessage(0);
	}
}
