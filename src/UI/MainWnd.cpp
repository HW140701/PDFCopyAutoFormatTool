#include "MainWnd.h"

/*----- ��ťButton������ -----*/
const TCHAR* const MainWnd_Btn_Setting_Name = _T("Btn_Setting");
const TCHAR* const MainWnd_Btn_Min_Name = _T("Btn_Min");
const TCHAR* const MainWnd_Btn_Max_Name = _T("Btn_Max");
const TCHAR* const MainWnd_Btn_Close_Name = _T("Btn_Close");
const TCHAR* const MainWnd_Btn_AutoCopyResultToClipboard_Name = _T("Btn_AutoCopyResultToClipboard");

/*----- ���ı��༭��RichEdit������ -----*/
const TCHAR* const MainWnd_RichEdit_Input_Name = _T("RichEdit_Input");
const TCHAR* const MainWnd_RichEdit_Output_Name = _T("RichEdit_Output");

/*----- VerticalLayout���ֵ����� -----*/
const TCHAR* const MainWnd_VerticalLayout_Setting_Name = _T("VerticalLayout_Setting");

MainWnd::MainWnd()
	:m_pRichEdit_Input(nullptr),
	m_pRichEdit_Output(nullptr),
	m_pVerticalLayout_Setting(nullptr),
	m_bAutoCopyResultToClipboard(false),
	m_pButton_AutoCopyResultToClipboard(nullptr)
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
	// ����
	if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Setting_Name) == 0)
	{
		//ResizeClient(800, 600);

		if (m_pVerticalLayout_Setting != nullptr)
		{
			if (m_pVerticalLayout_Setting->IsVisible())
			{
				m_pVerticalLayout_Setting->SetVisible(false);
			}
			else
			{
				m_pVerticalLayout_Setting->SetVisible(true);
			}
			
		}
	}
	// ��С��
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Min_Name) == 0)
	{
#if defined(UNDER_CE)
		::ShowWindow(m_hWnd, SW_MINIMIZE);
#else
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
#endif
	}
	// ���
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Max_Name) == 0)
	{

	}
	// �رճ���
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_Close_Name) == 0)
	{
		::SendMessage(this->GetHWND(), WM_CLOSE, NULL, NULL);
		PostQuitMessage(0);
	}
	// �Զ����Ƶ����а�
	else if (_tcsicmp(msg.pSender->GetName(), MainWnd_Btn_AutoCopyResultToClipboard_Name) == 0)
	{
		if (!m_bAutoCopyResultToClipboard)
		{
			if (m_pButton_AutoCopyResultToClipboard != nullptr)
			{
				m_pButton_AutoCopyResultToClipboard->SetNormalImage("����-��.png");
				m_pButton_AutoCopyResultToClipboard->SetHotImage("����-����ͣ.png");
				m_bAutoCopyResultToClipboard = true;
			}
		}
		else
		{
			if (m_pButton_AutoCopyResultToClipboard != nullptr)
			{
				m_pButton_AutoCopyResultToClipboard->SetNormalImage("����-��.png");
				m_pButton_AutoCopyResultToClipboard->SetHotImage("����-����ͣ.png");
				m_bAutoCopyResultToClipboard = false;
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

			// ������ʽȥ�����з��Լ�����-
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

				// �Զ����Ƹ�ʽ����������а�
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
	// �����ڴ�
	HANDLE hGlobalMemory = GlobalAlloc(GMEM_MOVEABLE, copy_content_length + 1);

	// �����ڴ�
	LPBYTE lpGlobalMemory = (LPBYTE)GlobalLock(hGlobalMemory); 

	// ���ַ������Ƶ�ȫ���ڴ��
	memcpy(lpGlobalMemory, copy_content.c_str(), copy_content_length);

	// �����ڴ�����
	GlobalUnlock(hGlobalMemory); 

	// ��ȡ��ȫ���ھ��
	HWND hWnd = this->GetHWND(); 

	// �򿪼�����
	::OpenClipboard(hWnd); 

	// ��ռ�����
	::EmptyClipboard(); 

	// ���ڴ��е����ݷ��õ�������
	::SetClipboardData(CF_TEXT, hGlobalMemory); 

	// �رռ�����
	::CloseClipboard(); 
}

void MainWnd::InitControl()
{
	if (m_pRichEdit_Input == nullptr)
	{
		m_pRichEdit_Input = static_cast<CRichEditUI*>(m_PaintManager.FindControl(MainWnd_RichEdit_Input_Name));
		if (m_pRichEdit_Input != nullptr)
		{
			// �����Ա�RichEdit�ؼ����յ�textchanged��Ϣ
			m_pRichEdit_Input->SetEventMask(ENM_CHANGE);
			m_pRichEdit_Input->SetFocus();
		}
	}

	if (m_pRichEdit_Output == nullptr)
	{
		m_pRichEdit_Output = static_cast<CRichEditUI*>(m_PaintManager.FindControl(MainWnd_RichEdit_Output_Name));
		if (m_pRichEdit_Output != nullptr)
		{
			// �����Ա�RichEdit�ؼ����յ�textchanged��Ϣ
			m_pRichEdit_Output->SetEventMask(ENM_CHANGE);
		}
	}

	if (m_pVerticalLayout_Setting == nullptr)
	{
		m_pVerticalLayout_Setting = static_cast<CVerticalLayoutUI*>(m_PaintManager.FindControl(MainWnd_VerticalLayout_Setting_Name));
	}

	if (m_pButton_AutoCopyResultToClipboard == nullptr)
	{
		m_pButton_AutoCopyResultToClipboard = static_cast<CButtonUI*>(m_PaintManager.FindControl(MainWnd_Btn_AutoCopyResultToClipboard_Name));
	}
}
