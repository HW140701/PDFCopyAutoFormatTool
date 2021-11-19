#include "ProjectHeader.h"
#include "UI/MainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// ���ص���������
	//std::string fontDir = PathUtils::GetFontDirectory();
	//std::string huaweixinwei_fontFile = fontDir + "������κ.ttf";
	//std::string robot_fontFile = fontDir + "Roboto-Black-1.ttf";
	//DuilibAddFont addFont;
	//if (!addFont.AddFont(huaweixinwei_fontFile.c_str()))
	//{
	//	return 0;
	//}

	//if (!addFont.AddFont(robot_fontFile.c_str()))
	//{
	//	return 0;
	//}


	// ��һ���� ʵ���������Ⱦ�����
	CPaintManagerUI::SetInstance(hInstance);

	CWndShadow::Initialize(hInstance);//������Ӱ��ʼ��

	// �ڶ�������ʼ��COM��, Ϊ����COM���ṩ֧��
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return 0;
	}

	// ������������������
	MainWnd pMainWnd;
	pMainWnd.Create(NULL, _T("PDFCopyAutoFormatTool"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	pMainWnd.CenterWindow();
	::ShowWindow(pMainWnd, SW_SHOW);

	// ��������������Ϣѭ��
	CPaintManagerUI::MessageLoop();

	// ���߲����˳������ͷ�COM��
	::CoUninitialize();

	return 0;
}