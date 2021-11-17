#include "ProjectHeader.h"
#include "UI/MainWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	// 第一步： 实例句柄与渲染类关联
	CPaintManagerUI::SetInstance(hInstance);

	CWndShadow::Initialize(hInstance);//窗体阴影初始化

	// 第二步：初始化COM库, 为加载COM库提供支持
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
	{
		return 0;
	}

	// 第三步：创建窗口类
	MainWnd pMainWnd;
	pMainWnd.Create(NULL, _T("PDFCopyAutoFormatTool"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);

	pMainWnd.CenterWindow();
	::ShowWindow(pMainWnd, SW_SHOW);

	// 第六步：处理消息循环
	CPaintManagerUI::MessageLoop();

	// 第七步：退出程序并释放COM库
	::CoUninitialize();

	return 0;
}