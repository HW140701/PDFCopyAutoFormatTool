#include "MainWnd.h"

/*----- 按钮Button的名称 -----*/
const TCHAR* const MainWnd_Btn_Min_Name = _T("Btn_Min");
const TCHAR* const MainWnd_Btn_Max_Name = _T("Btn_Max");
const TCHAR* const MainWnd_Btn_Close_Name = _T("Btn_Close");

/*----- 富文本编辑框RichEdit的名称 -----*/
const TCHAR* const MainWnd_RichEdit_Input_Name = _T("RichEdit_Input");
const TCHAR* const MainWnd_RichEdit_Output_Name = _T("RichEdit_Output");

MainWnd::MainWnd()
	:m_pRichEdit_Input(nullptr),
	m_pRichEdit_Output(nullptr)
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
	else if (_tcsicmp(msg.sType, _T("textchanged")) == 0)
	{
		OnTextChanged(msg);
	}

	WindowImplBase::Notify(msg);
}

void MainWnd::InitWindow()
{
	InitControl();

	InitWindowShadow();
}

void MainWnd::OnClickProcess(TNotifyUI& msg)
{
	// 最小化
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Min_Name) == 0)
	{
#if defined(UNDER_CE)
		::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
	}
	// 最大化
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Max_Name) == 0)
	{

	}
	// 关闭程序
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Close_Name) == 0)
	{
		::SendMessage(this->GetHWND(), WM_CLOSE, NULL, NULL);
		PostQuitMessage(0);
	}
}

void MainWnd::OnTextChanged(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_RichEdit_Input_Name) == 0)
	{
		if (m_pRichEdit_Input != nullptr)
		{
			std::string richEdit_Input_str = CDuiStringToString(m_pRichEdit_Input->GetText());

			// 清除换行符
			int r = richEdit_Input_str.find('\r\n');
			while (r != string::npos)
			{
				if (r != string::npos)
				{
					richEdit_Input_str.replace(r, 1, "");
					r = richEdit_Input_str.find('\r\n');
				}
			}

			/*std::regex pattern(".\r");
			std::regex_replace(richEdit_Input_str, pattern, "");*/

			if (m_pRichEdit_Output != nullptr)
			{
				m_pRichEdit_Output->SetText(richEdit_Input_str.c_str());
			}
		}
	}
}

void MainWnd::InitWindowShadow()
{
	m_WndShadow.Create(m_hWnd);
	m_WndShadow.SetSize(10);
	m_WndShadow.SetSharpness(15);
	m_WndShadow.SetDarkness(70);
	m_WndShadow.SetPosition(0, 0);
}

void MainWnd::InitControl()
{
	if (m_pRichEdit_Input == nullptr)
	{
		m_pRichEdit_Input = static_cast<CRichEditUI*>(m_PaintManager.FindControl(MainWnd_RichEdit_Input_Name));
		if (m_pRichEdit_Input != nullptr)
		{
			// 设置以便RichEdit控件接收到textchanged消息
			m_pRichEdit_Input->SetEventMask(ENM_CHANGE);
		}
	}

	if (m_pRichEdit_Output == nullptr)
	{
		m_pRichEdit_Output = static_cast<CRichEditUI*>(m_PaintManager.FindControl(MainWnd_RichEdit_Output_Name));
		if (m_pRichEdit_Output != nullptr)
		{
			// 设置以便RichEdit控件接收到textchanged消息
			m_pRichEdit_Output->SetEventMask(ENM_CHANGE);
		}
	}
}
