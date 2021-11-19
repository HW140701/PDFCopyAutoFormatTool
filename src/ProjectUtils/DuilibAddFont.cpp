#include "DuilibAddFont.h"
 #include "Windows.h"
 #include "string"
 #include "tchar.h"


DuilibAddFont::DuilibAddFont()
{
}

DuilibAddFont::~DuilibAddFont()
{
	for (int i = 0; i < m_LoadedFont.size(); ++i)
	{
		DeleteFile(m_LoadedFont[i].c_str());
	}
}

bool DuilibAddFont::AddFont(LPCTSTR lpszFontFile)
{
	int nResult = AddFontResource(lpszFontFile);
	if (nResult == 0)
	{
		MessageBox(NULL, "Ìí¼Ó×ÖÌåÊ§°Ü", NULL, 0);
		return false;
	}

	::SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);

	m_LoadedFont.emplace_back(lpszFontFile);

	return true;
}
