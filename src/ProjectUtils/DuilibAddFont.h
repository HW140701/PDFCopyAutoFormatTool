#ifndef DUILIB_ADD_FONT_H
#define DUILIB_ADD_FONT_H

#include "UIlib.h"

#include <vector>
#include <string>


class DuilibAddFont
{
public:
	DuilibAddFont();
	virtual~DuilibAddFont();

public:
	bool AddFont(LPCTSTR lpszFontFile);

private:
	std::vector<std::string> m_LoadedFont;
};

#endif // !DUILIB_ADD_FONT_H
