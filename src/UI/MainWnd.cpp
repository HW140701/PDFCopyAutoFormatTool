#include "MainWnd.h"

/*----- 按钮Button的名称 -----*/
const TCHAR* const MainWnd_Btn_Setting_Name = _T("Btn_Setting");
const TCHAR* const MainWnd_Btn_Min_Name = _T("Btn_Min");
const TCHAR* const MainWnd_Btn_Max_Name = _T("Btn_Max");
const TCHAR* const MainWnd_Btn_Close_Name = _T("Btn_Close");
const TCHAR* const MainWnd_Btn_AutoCopyResultToClipboard_Name = _T("Btn_AutoCopyResultToClipboard");
const TCHAR* const MainWnd_Btn_FrontWnd_Name = _T("Btn_FrontWnd");
const TCHAR* const MainWnd_Btn_Expand_Name = _T("Btn_Expand");
const TCHAR* const MainWnd_Btn_Shrink_Name = _T("Btn_Shrink");

/*----- 富文本编辑框RichEdit的名称 -----*/
const TCHAR* const MainWnd_RichEdit_Input_Name = _T("RichEdit_Input");
const TCHAR* const MainWnd_RichEdit_Output_Name = _T("RichEdit_Output");

/*----- VerticalLayout布局的名称 -----*/
const TCHAR* const MainWnd_VerticalLayout_Setting_Name = _T("VerticalLayout_Setting");
const TCHAR* const MainWnd_VerticalLayout_Expand_Name = _T("VerticalLayout_Expand");
const TCHAR* const MainWnd_VerticalLayout_Shrink_Name = _T("VerticalLayout_Shrink");

MainWnd::MainWnd()
	:m_pRichEdit_Input(nullptr),
	m_pRichEdit_Output(nullptr),
	m_pVerticalLayout_Setting(nullptr),
	m_bAutoCopyResultToClipboard(false),
	m_pButton_AutoCopyResultToClipboard(nullptr),
	m_bFrontWnd(false),
	m_pButton_FrontWnd(nullptr),
	m_pVerticalLayout_Expand(nullptr),
	m_pVerticalLayout_Shrink(nullptr)
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
	else if (_tcsicmp(msg.sType, _T("killfocus")) == 0)
	{
		OnKillFocus(msg);
	}
	else if (_tcsicmp(msg.sType, _T("setfocus")) == 0)
	{
		OnSetFocus(msg);
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
	// 设置
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Setting_Name) == 0)
	{
		//ResizeClient(800, 600);

		if (m_pVerticalLayout_Setting != nullptr)
		{
			// 如果设置面板可见
			if (m_pVerticalLayout_Setting->IsVisible())
			{
				m_pVerticalLayout_Setting->SetVisible(false);

				// 显示扩展按钮
				if (m_pVerticalLayout_Expand != nullptr)
				{
					if (!m_pVerticalLayout_Expand->IsVisible())
					{
						m_pVerticalLayout_Expand->SetVisible(true);
					}
				}

				// 隐藏缩放按钮
				if (m_pVerticalLayout_Shrink != nullptr)
				{
					if (m_pVerticalLayout_Shrink->IsVisible())
					{
						m_pVerticalLayout_Shrink->SetVisible(false);
					}
				}

			}
			// 如果设置面板不可见
			else
			{
				m_pVerticalLayout_Setting->SetVisible(true);

				// 隐藏扩展按钮
				if (m_pVerticalLayout_Expand != nullptr)
				{
					if (m_pVerticalLayout_Expand->IsVisible())
					{
						m_pVerticalLayout_Expand->SetVisible(false);
					}
				}

				// 显示缩放按钮
				if (m_pVerticalLayout_Shrink != nullptr)
				{
					if (!m_pVerticalLayout_Shrink->IsVisible())
					{
						m_pVerticalLayout_Shrink->SetVisible(true);
					}
				}


			}
			
		}
	}
	// 最小化
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Min_Name) == 0)
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
	// 自动复制到剪切板
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_AutoCopyResultToClipboard_Name) == 0)
	{
		if (!m_bAutoCopyResultToClipboard)
		{
			if (m_pButton_AutoCopyResultToClipboard != nullptr)
			{
				m_pButton_AutoCopyResultToClipboard->SetNormalImage("开关-开.png");
				m_pButton_AutoCopyResultToClipboard->SetHotImage("开关-开悬停.png");
				m_bAutoCopyResultToClipboard = true;
			}
		}
		else
		{
			if (m_pButton_AutoCopyResultToClipboard != nullptr)
			{
				m_pButton_AutoCopyResultToClipboard->SetNormalImage("开关-关.png");
				m_pButton_AutoCopyResultToClipboard->SetHotImage("开关-关悬停.png");
				m_bAutoCopyResultToClipboard = false;
			}
		}
	}
	// 软件置顶
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_FrontWnd_Name) == 0)
	{
		// 如果置顶选项为false，则置顶软件
		if (!m_bFrontWnd)
		{
			if (m_pButton_FrontWnd != nullptr)
			{
				m_pButton_FrontWnd->SetNormalImage("开关-开.png");
				m_pButton_FrontWnd->SetHotImage("开关-开悬停.png");
				// 窗口置顶
				::SetWindowPos(this->GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				m_bFrontWnd = true;
			}
		}
		// 如果置顶选项为true，则不置顶软件
		else
		{
			if (m_pButton_FrontWnd != nullptr)
			{
				m_pButton_FrontWnd->SetNormalImage("开关-关.png");
				m_pButton_FrontWnd->SetHotImage("开关-关悬停.png");
				// 窗口不置顶
				::SetWindowPos(this->GetHWND(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
				m_bFrontWnd = false;
			}
		}
	}
	// 扩展面板按钮
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Expand_Name) == 0)
	{
		if (m_pVerticalLayout_Setting != nullptr)
		{
			if (!m_pVerticalLayout_Setting->IsVisible())
			{
				m_pVerticalLayout_Setting->SetVisible(true);
			}
		}

		// 隐藏扩展按钮
		if (m_pVerticalLayout_Expand != nullptr)
		{
			if (m_pVerticalLayout_Expand->IsVisible())
			{
				m_pVerticalLayout_Expand->SetVisible(false);
			}
		}

		// 显示缩放按钮
		if (m_pVerticalLayout_Shrink != nullptr)
		{
			if (!m_pVerticalLayout_Shrink->IsVisible())
			{
				m_pVerticalLayout_Shrink->SetVisible(true);
			}
		}
	}
	// 缩放面板按钮
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Shrink_Name) == 0)
	{
		if (m_pVerticalLayout_Setting != nullptr)
		{
			if (m_pVerticalLayout_Setting->IsVisible())
			{
				m_pVerticalLayout_Setting->SetVisible(false);
			}
		}

		// 显示扩展按钮
		if (m_pVerticalLayout_Expand != nullptr)
		{
			if (!m_pVerticalLayout_Expand->IsVisible())
			{
				m_pVerticalLayout_Expand->SetVisible(true);
			}
		}

		// 隐藏缩放按钮
		if (m_pVerticalLayout_Shrink != nullptr)
		{
			if (m_pVerticalLayout_Shrink->IsVisible())
			{
				m_pVerticalLayout_Shrink->SetVisible(false);
			}
		}
	}
}

void MainWnd::OnTextChanged(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_RichEdit_Input_Name) == 0)
	{
		if (m_pRichEdit_Input != nullptr)
		{
			std::string richEdit_Input_str = CDuiStringToString(m_pRichEdit_Input->GetText());

			// 正则表达式去掉换行符以及符号-
			std::regex pattern("\\r\\n|\\n|\\r|-");
			richEdit_Input_str = std::regex_replace(richEdit_Input_str, pattern, "");

			if (m_pRichEdit_Output != nullptr)
			{
				m_pRichEdit_Output->SetText(richEdit_Input_str.c_str());

				int inputPos = m_pRichEdit_Input->GetVerticalScrollBar()->GetScrollPos();

				m_pRichEdit_Output->GetVerticalScrollBar()->SetScrollPos(inputPos);
				m_pRichEdit_Output->GetVerticalScrollBar()->NeedUpdate();
				m_pRichEdit_Output->GetVerticalScrollBar()->Invalidate();

				m_pRichEdit_Input->SetFocus();

				// 自动复制格式化结果到剪切板
				if (m_bAutoCopyResultToClipboard)
				{
					AutoCopyToClipboard(richEdit_Input_str);
				}
				
			}
		}
	}
}

void MainWnd::OnKillFocus(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_RichEdit_Input_Name) == 0)
	{
		if (m_pRichEdit_Input != nullptr)
		{
			if (!m_pRichEdit_Input->IsFocused())
			{
				//m_pRichEdit_Output->SetFocus();

				m_PaintManager.SetFocus(m_pRichEdit_Input, true);
				m_PaintManager.Invalidate();
			}
		}
	}
}

void MainWnd::OnSetFocus(TNotifyUI& msg)
{
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_RichEdit_Input_Name) == 0)
	{
		if (m_pRichEdit_Input != nullptr)
		{
			m_pRichEdit_Input->SetFocusBorderColor(0xFF6d9eeb);
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

void MainWnd::AutoCopyToClipboard(const std::string& copy_content)
{
	DWORD copy_content_length = copy_content.length();
	// 分配内存
	HANDLE hGlobalMemory = GlobalAlloc(GMEM_MOVEABLE, copy_content_length + 1);

	// 锁定内存
	LPBYTE lpGlobalMemory = (LPBYTE)GlobalLock(hGlobalMemory); 

	// 将字符串复制到全局内存块
	memcpy(lpGlobalMemory, copy_content.c_str(), copy_content_length);

	// 锁定内存块解锁
	GlobalUnlock(hGlobalMemory); 

	// 获取安全窗口句柄
	HWND hWnd = this->GetHWND(); 

	// 打开剪贴板
	::OpenClipboard(hWnd); 

	// 清空剪贴板
	::EmptyClipboard(); 

	// 将内存中的数据放置到剪贴板
	::SetClipboardData(CF_TEXT, hGlobalMemory); 

	// 关闭剪贴板
	::CloseClipboard(); 
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
			m_pRichEdit_Input->SetFocus();
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

	if (m_pVerticalLayout_Setting == nullptr)
	{
		m_pVerticalLayout_Setting = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(MainWnd_VerticalLayout_Setting_Name));
	}

	if (m_pVerticalLayout_Expand == nullptr)
	{
		m_pVerticalLayout_Expand = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(MainWnd_VerticalLayout_Expand_Name));
	}

	if (m_pVerticalLayout_Shrink == nullptr)
	{
		m_pVerticalLayout_Shrink = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(MainWnd_VerticalLayout_Shrink_Name));
	}

	if (m_pButton_AutoCopyResultToClipboard == nullptr)
	{
		m_pButton_AutoCopyResultToClipboard = static_cast<CButtonUI*>(m_PaintManager.FindControl(MainWnd_Btn_AutoCopyResultToClipboard_Name));
	}

	if (m_pButton_FrontWnd == nullptr)
	{
		m_pButton_FrontWnd = static_cast<CButtonUI*>(m_PaintManager.FindControl(MainWnd_Btn_FrontWnd_Name));
	}
}
