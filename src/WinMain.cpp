#include "ProjectHeader.h"
#include "UI/MainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
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