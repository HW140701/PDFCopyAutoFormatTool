#include "MainWnd.h"

/*----- ��ťButton������ -----*/
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
	// ����¼���Ϣ��Ӧ
	if (_tcsicmp(msg.sType, _T("click")) == 0)
	{
		OnClickProcess(msg);
	}

	WindowImplBase::Notify(msg);
}

void MainWnd::OnClickProcess(TNotifyUI& msg)
{
	// ��С��
	if (_tcsicmp(msg.pSender->GetName(), Str_Btn_Min) == 0)
	{
#if defined(UNDER_CE)
		::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
	}
	// ���
	else if (_tcsicmp(msg.pSender->GetName(), Str_Btn_Max) == 0)
	{

	}
	// �رճ���
	else if (_tcsicmp(msg.pSender->GetName(), Str_Btn_Close) == 0)
	{
		::SendMessage(this->GetHWND(), WM_CLOSE, NULL, NULL);
		PostQuitMessage(0);
	}
}
